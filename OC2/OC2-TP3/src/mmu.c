/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "screen.h"

//Macros
#define PDE_INDEX(virtual) virtual >> 22
#define PTE_INDEX(virtual) (virtual >> 12) & 0x3FF
#define ALIGN(dir)
#define PG_READ_WRITE 0x00000002
#define PG_USER 0x00000004
#define PG_PRESENT 0x00000001

void mmu_inicializar_dir_kernel(){
	int* page_directory = (int*) PAGE_DIRECTORY_KERNEL;
	page_directory[0] = PAGE_TABLE_KERNEL + 0x3;
	int i;
	for (i = 1; i < 1024; ++i) {
		page_directory[i]= 0x0;
	}

	int* page_table = (int*) PAGE_TABLE_KERNEL;
	for (i = 0; i < 1024; ++i) {
		page_table[i] = ((i << 12) | 3);
	}
}

unsigned int mmu_inicializar_dir_tarea(unsigned int* codigo, posicion pos) {
	pde_entry* page_directory_tareas = (pde_entry*) mmu_proxima_pagina_fisica_libre();

	int i;
	for (i = 0; i < 1024; i++) {
	    page_directory_tareas[i].present = 0;
	    page_directory_tareas[i].rw = 0;
	    page_directory_tareas[i].us = 0;
	    page_directory_tareas[i].pwt = 0;
	    page_directory_tareas[i].pcd = 0;
	    page_directory_tareas[i].a = 0;
	    page_directory_tareas[i].d = 0;
	    page_directory_tareas[i].pat = 0;        
	    page_directory_tareas[i].g = 0;
	    page_directory_tareas[i].disponible = 0;
	    page_directory_tareas[i].base = 0;
	}
	page_directory_tareas[0].present = 1;
	page_directory_tareas[0].rw = 1;
	
	pte_entry* page_table_tareas = (pte_entry*) mmu_proxima_pagina_fisica_libre();	
	for (i = 0; i < 1024; i++) {
	
		page_table_tareas[i].present = 1;
		page_table_tareas[i].rw = 1;
		page_table_tareas[i].us = 1;
		page_table_tareas[i].base = (unsigned int) i;
	}

	page_directory_tareas[0].base = (unsigned int) page_table_tareas >> 12;
	
	unsigned int* fisica =  (unsigned int*) game_dame_fisica_de_posicion(pos);

	mmu_mapear_pagina(DIR_VIRTUAL_TAREA, (unsigned int) page_directory_tareas, (unsigned int) fisica, 1);

	mmu_mapear_pagina((unsigned int) fisica, rcr3(), (unsigned int) fisica, 0);

	int j;
	for (j = 0; j < 1024; j++) {
		fisica[j] = codigo[j];
	}
	
	mmu_unmapear_pagina((unsigned int) fisica, rcr3());

	return (unsigned int)page_directory_tareas;
}



unsigned int game_dame_fisica_de_posicion(posicion pos) {
	return (0x400000 + (pos.y*80 + pos.x)*0x1000);
}

unsigned int proxima_pagina_libre;
void mmu_inicializar() {
	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	return pagina_libre;
}

/*Mapea la pagina fisica a la marco de pagina virtual en el esquema
de paginacion cr3.*/
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char us) {
	// Agarro los 1ros 20bits de la CR3 que corresponden a la direccion base del directorio de paginas
	
	pde_entry* CR3 = (pde_entry*)(cr3 & 0xFFFFF000);

	pde_entry* PDE = &(CR3[PDE_INDEX(virtual)]);

	// si PRESENT es 0
	if (!(PDE->present)) {
		// pongo la dir 0
		PDE->base = mmu_proxima_pagina_fisica_libre() >> 12;

		// la igualo con el resultado de la funcion (me da un numero de 32bits donde los primeros 12 son 0s asi que esta todo re piolanga)
		// le pongo en 1 el PRESENT y el RW como dice la diapo
		PDE->present = 1;
		PDE->rw = 1;
		PDE->us = us;
		// dejo el resto de la tabla en 0
		pte_entry* pte_indice = (pte_entry*) ((PDE->base) << 12);
		
		int i;
		for (i = 0; i < 1024; i++) {
			pte_indice[i].present = 0;
			pte_indice[i].us = 0;
		}
	}

	pte_entry* a = (pte_entry*) ((PDE->base) << 12);
	pte_entry* PTE = (pte_entry*) &(a[PTE_INDEX(virtual)]);

	PTE->base = fisica >> 12;
	PTE->present = 1;
	PTE->rw = 1;
	PTE->us = us;

	tlbflush();
}

/*Desmapea la pagina fisica en el esquema de paginacion cr3.*/
unsigned int mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3) {
	pde_entry* CR3 = (pde_entry*) (cr3 & 0xFFFFF000);
	pde_entry* PDE = &(CR3[PDE_INDEX(virtual)]);

	pte_entry* a = (pte_entry*) ((PDE->base)<<12);

	pte_entry* PTE = (pte_entry*) &(a[PTE_INDEX(virtual)]);
	pte_entry* pte_indice = (pte_entry*) ((PDE->base)<<12);

	PTE->present = 0;
	PTE->us = 0;

	int check_noHayNadie = 1;
	int i;
	for (i = 0; i < 1024 && check_noHayNadie; i++){
		if(pte_indice[i].present){
			check_noHayNadie = 0;
		} 
	}

	if (check_noHayNadie){
		PDE->present = 0;
	}

	tlbflush();
	return cr3;
}

