#include "grafos3.h"

using namespace std;
using namespace grafos3;

//O(n+m) siendo n la cantidad de estaciones y m la cantidad de vías
ListAdy::ListAdy(int estaciones, int vias, vector<ABC> recorridos) {
	this->N = estaciones;
	this->M = vias;
	this->adyacencia.resize(estaciones); //O(n) siendo n la cantidad de estaciones

	//O(m) * O(1) = O(m)
	for (uint i = 0; i < recorridos.size(); ++i)
	{
		ABC recorrido = recorridos[i]; //O(1)
		int nroNodo = get<0>(recorrido) - 1; //nroNodo O(1)
		t_node vecino = { get<1>(recorrido) - 1, get<2>(recorrido) }; //nodo vecino, costo en llegar O(1)
		this->adyacencia[nroNodo].push_back(vecino); //O(1)
	}
}

//O((n+m) * log n) siendo n la cantidad de estaciones y m la cantidad de vías
salida ListAdy::dijkstra() {
	salida salida1;
    vector<int> distancias(this->N, INFINITO); //distancias[i] contiene la distancia mínima para llegar del nodo 0 al nodo i. Inicializados en INFINITO
    //O(n) siendo n la cantidad de estaciones

    vector<int> antecesores(this->N, INFINITO); //antecesores[i] contiene el nodo antecesor del nodo i. Inicializados en INFINITO
    //O(n) siendo n la cantidad de estaciones

    distancias[0] = 0; //inicializo la distancia del nodo inicial en 0,
    //O(1)

    set< pair<int,int>, Cmp > noVisitados; //lista de (distancia, nroNodo). La distancia es la prioridad (la lista se mantendrá ordenada por distancia de menor a mayor)
    //O(1)

    int distanciaVieja = 0;
    //O(1)
    int distanciaNueva = 0;
    //O(1)
    int nroNodoVecino = 0;
    //O(1)

    noVisitados.insert( {0, 0} ); //inserto nodo inicial (distancia, nroNodo)
    //O(log n) siendo n la cantidad de elementos de noVisitados
    
    //O(n) * O(log n) + O(m log n) = O((n+m) * log n) 
    //se suman porque el for interno en el peor caso se recorrerá m veces incluyendo todas las iteraciones del while
	while (!noVisitados.empty()) { //mientras hayan vértices no visitados

	    //obtengo el numero de nodo de mayor prioridad, y lo desencolo
	    int nroNodo = noVisitados.begin()->second;
	    //O(1)

	    noVisitados.erase(noVisitados.begin());
	    //O(log n) siendo n la cantidad de elementos de noVisitados

    	//O(m) * O(log n) = O(m log n)
	    for (t_node vecino : this->adyacencia[nroNodo]) { //para cada vecino = (nroNodo, peso)
	        nroNodoVecino = vecino.first; //O(1)
	        distanciaVieja = distancias[nroNodoVecino]; //O(1)
	        distanciaNueva = distancias[nroNodo] + vecino.second; //O(1)

	        if (distanciaNueva < distanciaVieja) { 
	        //peso de llegar al nodo actual + peso de llegar al vecino < peso de llegar al vecino (que ya tenia)
	        //recordar que las distancias se inicializan en INFINITO, así que las primeras veces se cumple esta condición

	        	//si ya existía el nodo vecino en noVisitados para ser recorrido posteriormente, lo borro
	    		t_node nodoAnterior = { distanciaVieja, nroNodoVecino }; //O(1)
	            noVisitados.erase(nodoAnterior); //O(log n) siendo n la cantidad de elementos de noVisitados

	            //creo el nodo vecino en noVisitados para ser recorrido posteriormente (con su nueva prioridad/distancia)
	            t_node nodoNuevo = { distanciaNueva, nroNodoVecino }; //O(1)
	            noVisitados.insert(nodoNuevo); //O(log n) siendo n la cantidad de elementos de noVisitados

	            //actualizo la distancia y el antecesor del nodo vecino
	            distancias[nroNodoVecino] = distanciaNueva; //O(1)
	            antecesores[nroNodoVecino] = nroNodo; //O(1)
	        }
	    }
	}

	//inicializo el tiempo mínimo para ir de la estación 1 a la estación N en -1 (por si no hay forma de llegar)
	salida1.T = -1; //O(1)
	int distanciaFinal = distancias[(this->N) - 1]; //O(1)
	if (distanciaFinal != INFINITO) {
		salida1.T = distanciaFinal; //O(1)

		int iNodo = this->N - 1; //O(1)
		salida1.S = 1; //O(1)
		
		//O(n) * O(1) = O(n)
		while (iNodo > 0) {
			salida1.escape.insert(salida1.escape.begin(), iNodo + 1); //O(1)
			iNodo = antecesores[iNodo]; //O(1)

			salida1.S++; //O(1)
        }
		salida1.escape.insert(salida1.escape.begin(), 1); //O(1)
    }

	return salida1;
}