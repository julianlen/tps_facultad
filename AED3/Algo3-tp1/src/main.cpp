#include <iostream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atol */
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <random>
#include "ejercicio1.h"
#include "ejercicio2.h"
#include "ejercicio3.h"

using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

void start_timer() {
	start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
	chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
	return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}


int main(int argc, char *argv[]) {
	int numeroDeEjercicio = 0;
	bool experimentos = false;
	if (argc == 2) {
		numeroDeEjercicio = atoi(argv[1]);
	}
	else if (argc == 3) {
		numeroDeEjercicio = atoi(argv[1]);
		string exp = argv[2];
		if (exp == "-exp") {
			experimentos = true;
		}
	}
	else {
		cout << "Modo de uso: \n tp1 numeroDeEjercicio \n Opcional luego del numero de ejercicio: " << endl;
		cout << "   -exp para experimentos" << endl;
		return -1;
	}


	if (!experimentos) 
		cout << "Corriendo ejercicio numero " << numeroDeEjercicio << endl;

	if (numeroDeEjercicio == 1) {
		if (!experimentos) {
			int cantidadArq, cantidadCanibales;

			cout << "Ingrese la cantidad de Arqueologos y luego la de Canibales: " << endl;
			cin >> cantidadArq >> cantidadCanibales;

			cout << "Ingrese las velocidades de los Arqueologos: " << endl;
			int velocidad;
			vector<int> velocidadesArq;
			while(cantidadArq > 0 && (cin >> velocidad)) {
				velocidadesArq.push_back(velocidad);
				cantidadArq--;
	  		}

			cout << "Ingrese las velocidades de los Canibales" << endl;
			vector<int> velocidadesCanibales;
			while(cantidadCanibales > 0 && (cin >> velocidad)){
				velocidadesCanibales.push_back(velocidad);
				cantidadCanibales--;
			}

			start_timer();
			int tiempo = cruzarPuente(velocidadesCanibales, velocidadesArq);
			cout << tiempo << endl;
			cout << "tiempo que tarda en microsegundos: " << stop_timer() << endl;

		}
		else {
			vector<int> canibales;
			vector<int> arqueologos;
			//Exp 2
			for (int i = 0; i < 7; ++i){
				canibales.push_back(i);
				for (int veces = 0; veces < 30; ++veces){
					start_timer();
					cruzarPuente(canibales, arqueologos);
					cout << stop_timer() << "    " << canibales.size() << endl;
				}
			}
			canibales.clear();
			//Exp 1
			for (int q = 0; q <= 6; ++q){
				for (int k = 0; k < q; ++k){
					canibales.push_back(k);
					for (int times = 0; times < 30; ++times){
						start_timer();
						cruzarPuente(canibales, arqueologos);
						cout << stop_timer() << "    " << arqueologos.size() << "    " << canibales.size() << endl;
					}
				}
				canibales.clear();
				arqueologos.push_back(q);
			}
			// Exp 3
			for (int w = 0; w < 6; w++){
				arqueologos.push_back(w);
			}
			for (int q = 6; q >= 0; q--){
				for (int times = 0; times < 30; ++times){
					start_timer();
					cruzarPuente(canibales, arqueologos);
					cout << stop_timer() << "    " << arqueologos.size() << "    " << canibales.size() << endl;
				}
				canibales.push_back(q);
				arqueologos.pop_back();
			}
		}
	}
	else if (numeroDeEjercicio == 2) {
		if (!experimentos) {
			long p;
			cout << "Ingresar P para ejercicio 2.  P: ";
			cin >> p;
			pair<list< long >, list< long > > balanza(arreglarBalanza(p));
			list<long> izquierdas = balanza.first;
			list<long> derechas = balanza.second;
			// Mostrar en pantalla los resultados
			cout << izquierdas.size() << " " << derechas.size() << endl;
			for (list<long>::iterator itIzq = izquierdas.begin(); itIzq != izquierdas.end(); itIzq++) {
				cout << *itIzq << " ";
			}
			cout << endl;
			for (list<long>::iterator itDer = derechas.begin(); itDer != derechas.end(); itDer++) {
				cout << *itDer << " ";
			}
			cout << endl;
		}
		else {
			for (int q = 0; q < 5000; ++q) {
				int p[q];
				for(int j= 0;j<q;j++){
				   p[q] = 1;
				}
				for (int i = 0; i < 1000; ++i){
					start_timer();
					arreglarBalanzaParaTest(p,q);
					cout << stop_timer() << "    " << q << endl;
				}
			}
		}
	}
	else if (numeroDeEjercicio == 3) {

		int cantMochilas;
		int tiposDeTesoros;
		vector<int> capacidades;
		vector<int> tesoroCant;
		vector<int> tesoroPeso;
		vector<int> tesoroValor;
		int cantTesoros = 0;

		if (!experimentos){

			cout << "Cantidad de mochilas y de tipos de tesoros:" << endl;
			cin >> cantMochilas >> tiposDeTesoros;
			int tamanoMochila;

			cout << "capacidades de las " << cantMochilas << " mochilas" << endl;
			while(cantMochilas > 0 && (cin >> tamanoMochila)) {
					capacidades.push_back(tamanoMochila);
					cantMochilas--;
		  }

		  int totalInfoTesoros = tiposDeTesoros*3;
		  int unaInfoTesoro;
		  cout << "ingresar C P V de cada tipo de tesoro" << endl;
		  while(totalInfoTesoros > 0 && (cin >> unaInfoTesoro)) {
					if (totalInfoTesoros % 3 == 0){
						tesoroCant.push_back(unaInfoTesoro);
					}
					else if (totalInfoTesoros % 3 == 1){
						tesoroPeso.push_back(unaInfoTesoro);
					}
					else if (totalInfoTesoros % 3 == 2){
						tesoroValor.push_back(unaInfoTesoro);
					}
					totalInfoTesoros--;
		  }

			for (uint i = 0; i < tesoroCant.size(); ++i)
			{
				cantTesoros += tesoroCant[i];
			}

			salida ej3 = Mochilero(cantMochilas, cantTesoros, capacidades, tesoroCant, tesoroValor, tesoroPeso);
			cout << "valorTotal = " << ej3.first << endl;
			for (unsigned int i = 0; i < ej3.second.size(); ++i)
			{
				cout << endl;
				cout << "mochila" << (i+1) << " capacidad = " << capacidades[i] << endl;
				cout << "cantTesoros = " << ej3.second[i][0] << " | ";
				for (unsigned int j = 1; j < ej3.second[i].size(); ++j)
				{
					cout << "tesoro nro " << ej3.second[i][j] << " (p,v) = (" << tesoroValor[ej3.second[i][j]-1] << "," << tesoroPeso[ej3.second[i][j]-1] << ")" << " | ";
				}
				cout << endl;
			}
		}else{
			for (int ks = 1; ks <= 50; ++ks){
				capacidades.clear();
				default_random_engine generator;
				uniform_int_distribution <int> dameRandom(0,ks);
				cantTesoros = ks;
				tesoroCant.push_back(1);
				int valorTesoroActual = dameRandom(generator); //NO IMPORTA
				tesoroValor.push_back(valorTesoroActual); //NO IMPORTA
				int pesoTesoroActual = dameRandom(generator); //NO IMPORTA
				tesoroPeso.push_back(pesoTesoroActual); //NO IMPORTA
				for (int mochilas = 1; mochilas <= 3; ++mochilas){
					capacidades.push_back(ks);
					for (int veces = 0; veces < 50; ++veces){
						start_timer();
						Mochilero(cantMochilas, cantTesoros, capacidades, tesoroCant, tesoroValor, tesoroPeso);
						cout << stop_timer() << "    " << ks << "    " << cantTesoros << "    " << mochilas << endl;
					}
				}
			}
		}
	}
	else {
		cout << "numero de ejercicio no valido" << endl;
		return -1;
	}
	return 0;
}




