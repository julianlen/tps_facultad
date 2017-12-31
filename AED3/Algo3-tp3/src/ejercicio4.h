#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm> //Sort esta en O(n*Log n) y reverse en O(n)
#include "Estacion.h"
#include "ejercicio3.h"

using namespace std;

typedef tuple<double, int, vector<int> > solucion;


solucion solverEj4(vector<Estacion> estaciones, vector<vector<double> > &distancias, int n, int m, int k, int grasp, pair<int, bool> criterio, bool vecindarioBusqLocal);
solucion greedyRandomized(const vector<Estacion> estaciones, const vector<vector<double> > &distancias, const int n, const int m, const int k, const int grasp);
bool puedoMeter(const vector<Estacion>& estaciones, const vector<int>& recorrido, const Estacion& nuevaEstacion, const int k);
void ordenarPorCosto(vector<int>& lista, const vector<double> & distancias);
bool puedoMeter(const vector<Estacion>& estaciones, const vector<int>& recorrido, const Estacion& nuevaEstacion, const int k);
void ordenarPorCosto(vector<int>& lista, const vector<double>& distancias);
bool sonTodosPotas(const vector<Estacion> & estaciones);
int random(vector<int> list);
bool pairCompare(const pair<int, double>& firstElem, const pair<int, double>& secondElem);