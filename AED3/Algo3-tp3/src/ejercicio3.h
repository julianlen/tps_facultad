#include "ejercicio2.h"

using namespace std;


typedef tuple<double, int, vector<int> > solucion;
//tuple<double, int, vector<int> > 
solucion solverEj3(vector<Estacion> estaciones, vector<vector<double> > &distancias, int n, int m, int k, bool vecindario);
solucion solucionEj3(solucion& primerEstado, vector<Estacion> estaciones, vector<vector<double> > &distancias, int k, bool vecindario);
solucion busquedaLocal(vector<int> recorrido, const vector<Estacion> estaciones, vector<vector<double>> &distancias, double distancia, const int cantVertices, const int k, const bool swapDePotas);
void swap(vector<int> &estado, int i, int j);
vector<vector<int>> dameVecindario (const vector<Estacion> estaciones, const vector<int> estado);
double dameDistancia(const vector<int> recorrido, const vector<vector<double>> distancias);
void imprimirEstado(solucion primerEstado);
vector<vector<int>> dameVecindario2(const vector<Estacion> estaciones, const vector<int> recorrido, const vector<vector<double>> distancias, const int k);
bool recorridoValido(const vector<Estacion> estaciones, const vector<int> recorrido, const vector<vector<double>> distancias, const int k);