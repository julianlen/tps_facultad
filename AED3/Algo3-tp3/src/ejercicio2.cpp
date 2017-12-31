#include "ejercicio2.h"
#include "ejercicio1.h"

using namespace std;

tuple<double, int, vector<int> > solverEj2(vector<Estacion> &estaciones, vector<vector<double> > &distancias, int n, int m, int k){ // n == gimnasios, m == paradas, k == tam_mochila
  vector<int> camino_nulo;
  tuple<double, int, vector<int> > solucion = make_tuple(-1,-1,camino_nulo);
  int id = donde_voy(estaciones, 0, k);
  if(id != -1){   
    vector<Estacion> visitados;
    int index = indice_estacion_con_id(id, estaciones);
    visitados.push_back(estaciones[index]);
    int potasActuales = (estaciones[index].esGimnasio || k > 3) ? estaciones[index].potas : k;
    estaciones.erase(estaciones.begin() + index);
    greedy_capturar_gimnasios(estaciones,distancias,n,m,k,visitados,potasActuales,id,solucion);
  }
  return solucion;
}

void greedy_capturar_gimnasios(vector<Estacion> &estaciones, vector< vector<double> > &distancias, int n, int m, int k, std::vector<Estacion> &visitados, int potasActuales, int id_estacion_actual, tuple<double,int,vector<int> > &soluciones){
  int i = 0; 
  while(i< (n+m) && !es_solucion(estaciones)) {
    ordenar(estaciones, distancias, id_estacion_actual);
    int id = donde_voy(estaciones, potasActuales, k);
    if(id == -1){
      i = n + m;
    }
    else
    {
      int index = indice_estacion_con_id(id, estaciones);
      visitados.push_back(estaciones[index]);
      potasActuales = (estaciones[index].esGimnasio || potasActuales+3 <= k) ? potasActuales + estaciones[index].potas : k;
      estaciones.erase(estaciones.begin() + index);
      id_estacion_actual = id;
      i++;
    }
   
  }
  if(es_solucion(estaciones)){
    double distancia = distancia_acumulada(visitados,distancias);
    vector<int> camino;
    for (int u = 0; u < visitados.size(); ++u) {
      camino.push_back(visitados[u].id);
    }
    soluciones = make_tuple(distancia, visitados.size(), camino);    
  }
}

void ordenar(vector<Estacion> &estaciones, vector< vector<double> > distancias, int id_estacion_actual){
  vector<int> ids_vistos;
  ids_vistos.push_back(id_estacion_actual);
  for (int i = 0; i < estaciones.size(); ++i) {
    int id_mas_cercano = id_mas_cercano_que_no_viste(distancias[id_estacion_actual], ids_vistos, estaciones);
    ids_vistos.push_back(id_mas_cercano);
    int indice_id_mas_cercano = indice_estacion_con_id(id_mas_cercano, estaciones);
    if (indice_id_mas_cercano > -1) swap(indice_id_mas_cercano, i, estaciones);
  }
}

int id_mas_cercano_que_no_viste(vector<double> &distancias, vector<int> &vistos, vector<Estacion> &estaciones){
  int actual = id_del_max(distancias);
  for (int j = 0; j < distancias.size(); ++j) {
    if ((distancias[j] <= distancias[actual]) && !esta(vistos, j) && (indice_estacion_con_id(j, estaciones) > -1) ) {
      actual = j;
    }
  }
  return actual;
}

void swap(int indice_id_mas_cercano, int i, vector<Estacion> &estaciones){
  Estacion tmp(estaciones[i]);
  estaciones[i] = estaciones[indice_id_mas_cercano];
  estaciones[indice_id_mas_cercano] = tmp;
}

int indice_estacion_con_id(int id, vector<Estacion> &estaciones) {
  for (int i = 0; i < estaciones.size(); ++i) {
    if (estaciones[i].id == id) {
      return i;
    }
  }
  return -1;
}

int donde_voy(vector<Estacion> estaciones, int potasActuales, int k){
  for (int i = 0; i < estaciones.size(); ++i) {
    if( puede_ganar_gimnasio(estaciones[i],potasActuales) || puede_recibir_potas(estaciones[i],potasActuales,k) ) {
      return estaciones[i].id;
    }
  }
  return -1;
}

bool esta(vector<int> &vistos, int j){
  for (int i = 0; i < vistos.size(); ++i) {
    if (vistos[i] == j) return true;
  }
  return false;
}

int id_del_max(vector<double> &distancias){
  int res = 0;
  int max_actual = -1;
  for (int l = 0; l < distancias.size(); ++l) {
    if (distancias[l] >= max_actual) {
      res = l;
      max_actual = distancias[l];
    }
  }
  return res;
}