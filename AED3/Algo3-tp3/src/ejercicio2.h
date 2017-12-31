#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm> //Sort esta en O(n*Log n) y reverse en O(n)
#include "Estacion.h"


std::tuple<double, int, std::vector<int> > solverEj2(std::vector<Estacion> &estaciones, std::vector<std::vector<double> > &distancias, int n, int m, int k);
void greedy_capturar_gimnasios(std::vector<Estacion> &estaciones, std::vector< std::vector<double> > &distancias, int n, int m, int k, std::vector<Estacion> &visitados, int potasActuales, int id_estacion_actual, std::tuple<double,int,std::vector<int> > &soluciones);
void ordenar(std::vector<Estacion> &estaciones, std::vector< std::vector<double > > distancias, int id_estacion_actual);
int id_mas_cercano_que_no_viste(std::vector<double> &distancias, std::vector<int> &vistos, std::vector<Estacion> &estaciones);
void swap(int id_mas_cercano, int i, std::vector<Estacion> &estaciones);
int indice_estacion_con_id(int id, std::vector<Estacion> &estaciones);
int donde_voy(std::vector<Estacion> estaciones, int potasActuales, int k);
bool esta(std::vector<int> &vistos, int j);
int id_del_max(std::vector<double> &distancias);