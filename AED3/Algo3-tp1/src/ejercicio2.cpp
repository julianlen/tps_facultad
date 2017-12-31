#include <list>
#include <utility>
#include <iostream>
#include <math.h>


using namespace std;

//
// void damePesos(int p){
// 	int[] base = decAter(p);
//
// 	int tam = sqrt(p);
// 	vector<int> izq (tam, 0);
// 	vector<int> der (tam, 0);
// 	int indIzq = 0;
// 	int indDer = 0;
//
// 	bool sumo = false;
// 	int t;
// 	for (int i = 0; i < tamano(base) || sumo; i++)
// 	{
// 		t = i < n ? base[i] : 0;
// 		if (sumo)
// 		{
// 			t++;
// 			if (t == 3)
// 			{
// 				t = 0;
// 			}
// 			else
// 			{
// 				sumo = false;
// 			}
// 		}
// 		if (t == 1) {
// 			izq[indIzq] = 3^i;
// 			indIzq++;
// 		} else if (t == 2) {
// 			der[indDer] = 3^i;
// 			indDer++;
// 			sumo = true;
// 		}
// 	}
// }


pair<list< long >, list< long > > arreglarBalanza(long p){
  bool izquierda = true;
	int divisiones = 0;
	list<long> izquierdas;
	list<long> derechas;
	while(p!=0){
		long cociente = p / 3 ;
		long resto = p - (cociente*3);
		if(resto == 0){
			if(!izquierda) izquierdas.push_back(pow(3,divisiones));
			izquierda = true;
		}
		else if(resto == 1) {
      		izquierda ? izquierdas.push_back(pow(3,divisiones)) : derechas.push_back(pow(3,divisiones));			
		}
		else {
			if(izquierda) derechas.push_back(pow(3,divisiones));
			izquierda = false;
		}
		p = cociente;
	  divisiones++;
	}
	if(!izquierda) izquierdas.push_back(pow(3,divisiones));

	pair<list< long >, list< long > > res (izquierdas, derechas);
	return res;
/*
  // Mostrar en pantalla los resultados
	Ahora se hace desde Main
*/
}

pair<list< long >, list< long > > arreglarBalanzaParaTest(int p[], int size){
    bool izquierda = true;
	int divisiones = 0;
	list<long> izquierdas;
	list<long> derechas;
	while(size!=0){
		if(p[size -1] == 0){
			if(!izquierda) izquierdas.push_back(pow(3,divisiones));
			izquierda = true;
		}
		else if(p[size -1] == 1) {
      		izquierda ? izquierdas.push_back(pow(3,divisiones)) : derechas.push_back(pow(3,divisiones));			
		}
		else {
			if(izquierda) derechas.push_back(pow(3,divisiones));
			izquierda = false;
		}
		size--;
	  	divisiones++;
	}
	if(!izquierda) izquierdas.push_back(pow(3,divisiones));

	pair<list< long >, list< long > > res (izquierdas, derechas);
	return res;
/*
  // Mostrar en pantalla los resultados
	Ahora se hace desde Main
*/
}
