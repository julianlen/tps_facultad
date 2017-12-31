#include "ejercicio3.h"

solucion solverEj3(vector<Estacion> estaciones, vector<vector<double> > &distancias, int n, int m, int k, bool vecindario){
	
	vector<Estacion> estacionesAuxiliar = estaciones;
	tuple<double, int, vector<int> > primerEstado = solverEj2(estaciones, distancias, n, m, k); //Primer candidato a solucion
	
	return solucionEj3(primerEstado, estacionesAuxiliar, distancias, k, vecindario);
}

solucion solucionEj3(solucion& primerEstado, vector<Estacion> estaciones, vector<vector<double> > &distancias, int k, bool vecindario) {
	//imprimirEstado(primerEstado);

	double distanciaInicial = get<0>(primerEstado); //Copio la distancia

	if (distanciaInicial != -1) {
		
		vector<int> recorridoInicial = get<2>(primerEstado); //Copio el recorrido del candidato a solucion
		int cantVertices = get<1>(primerEstado);
		//True es paradas, False es Gym
		primerEstado = busquedaLocal(recorridoInicial, estaciones, distancias, distanciaInicial, cantVertices, k, vecindario);
	}

	//imprimirEstado(primerEstado);

	return primerEstado;
}

void imprimirEstado(solucion primerEstado)
{
	cout<< endl;
	cout << "Distancia: " << get<0>(primerEstado) << " CantVert:" << get<1>(primerEstado) << endl;
	cout << " recorrido ";
	for (int i = 0; i < get<1>(primerEstado); ++i){
		cout << get<2>(primerEstado)[i] + 1 << " ";
	}
	cout << endl; 
}

solucion busquedaLocal(vector<int> recorrido, const vector<Estacion> estaciones, vector<vector<double>> &distancias, double distancia, const int cantVertices, const int k, const bool swapDePotas){
	//swapDePOtas = True es paradas, False es Gym
	vector<vector<int>> vecindario;
	bool noHayMasSoluciones = false;
	double distanciaMinima;
	double distanciaAux;
	int proximoEstado;

	while (!noHayMasSoluciones) {
		if (swapDePotas)
			vecindario = dameVecindario(estaciones, recorrido);
		else
			vecindario = dameVecindario2(estaciones, recorrido, distancias, k);

		proximoEstado = -1;

    	if (vecindario.size() > 0) {
			
			distanciaMinima = distancia;
			
			//Busco algun vecino con distancia mas chica
			for (uint i = 0; i < vecindario.size(); ++i) {
				
				distanciaAux = dameDistancia(vecindario[i], distancias);
				if (distanciaAux < distanciaMinima) {
					distanciaMinima = distanciaAux;
					proximoEstado = i;
				}
			}
    	}
	
		if (proximoEstado > -1) {
			recorrido = vecindario[proximoEstado];
			distancia = distanciaMinima;
    	}
    	else {
    		noHayMasSoluciones = true;
    	}
	}

	return make_tuple(distancia, cantVertices, recorrido);
}


double dameDistancia(const vector<int> recorrido, const vector<vector<double>> distancias){
	double distancia = 0;
	for (uint i = 0; i < recorrido.size() - 1; i++) {
		distancia += distancias[recorrido[i]][recorrido[i + 1]];
	}
	return distancia;
}


vector<vector<int>> dameVecindario(const vector<Estacion> estaciones, const vector<int> recorrido){
	vector<vector<int>> vecindario;

	for (uint i = 0; i < recorrido.size() - 1; ++i) {
		if (!estaciones[recorrido[i]].esGimnasio) {
			for (uint j = i+1; j < recorrido.size(); j++) {
				if (!estaciones[recorrido[j]].esGimnasio) {
					vector<int> estadoAux = recorrido;
					swap(estadoAux, i, j);
					vecindario.push_back(estadoAux);
				}
			}
		}
	}

	return vecindario;
}

vector<vector<int>> dameVecindario2(const vector<Estacion> estaciones, const vector<int> recorrido, const vector<vector<double>> distancias, const int k) {
	vector<vector<int>> vecindario;

	for (uint i = 0; i < recorrido.size() - 1; ++i) {
		if (estaciones[recorrido[i]].esGimnasio) {
			for (uint j = i+1; j < recorrido.size(); j++) {
				if (estaciones[recorrido[j]].esGimnasio) {
					vector<int> estadoAux = recorrido;
					swap(estadoAux, i, j);
					
					if (recorridoValido(estaciones, estadoAux, distancias, k)) {
						vecindario.push_back(estadoAux);
					}
				}
			}
		}
	}
	return vecindario;
}

bool recorridoValido(const vector<Estacion> estaciones, const vector<int> recorrido, const vector<vector<double>> distancias, const int k) {
	int pociones = 0;

	for (int r : recorrido) {
		if (!estaciones[r].esGimnasio) {
			pociones = min(pociones + 3, k);
		}
		else {
			if ((-estaciones[r].potas) > pociones)
				return false;

			pociones -= estaciones[r].potas;
		}
	}
	return true;
}

void swap(vector<int> &estado, int i, int j) {
	int x = estado[j];
	estado[j] = estado[i];
	estado[i] = x;
}

