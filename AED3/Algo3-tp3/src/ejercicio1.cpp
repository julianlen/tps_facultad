#include "ejercicio1.h"

using namespace std;

void imprimir_estaciones(vector<Estacion> &estaciones){
  cout << endl;
  for (int i = 0; i < estaciones.size(); ++i)
  {
    cout << estaciones[i].id << " ";
  }
  cout << endl;
}

tuple<double, int, vector<int> > solverEj1(vector<Estacion> &estaciones, const vector<vector<double> > &distancias, int n, int m, int k){
  vector<int> camino_nulo;
  tuple<double, int, vector<int> > solucion = make_tuple(-1,-1,camino_nulo);
  if(puede_ser_que_tenga_solucion(estaciones,k)){
	  vector<Estacion> visitados;
	  BT_capturar_gimnasios(estaciones,distancias,n,m,k,visitados,0,solucion);
  }
  return solucion;
}

void BT_capturar_gimnasios(vector<Estacion> &estaciones, const vector< vector<double> > &distancias, int n, int m, int k, std::vector<Estacion> &visitados, int potasActuales, tuple<double,int,vector<int> > &soluciones){
  if (visitados.size() == 3 && visitados[0].id == 1 && visitados[1].id == 3 && visitados[2].id == 0)
  {
    cout << "PELOTUDO! Es solucion?? " << es_solucion(estaciones) << endl;
    cout << distancia_acumulada(visitados,distancias) << endl;
    cout << get<0>(soluciones) << endl;

  }
  if (es_solucion(estaciones)){
    double distancia = distancia_acumulada(visitados,distancias);
    vector<int> camino;
    for (int i = 0; i < visitados.size(); ++i) {
      camino.push_back(visitados[i].id);
    }
    soluciones = (make_tuple(distancia, visitados.size(), camino));
  }
  else{
    // imprimir_estaciones(visitados);
    for (int i = 0; i < estaciones.size(); ++i) {
      double nueva_distancia = 0;
      if (visitados.size() > 0) {
        int id_ultimo_visitado = visitados.back().id;
        double proxima_distancia = distancias[id_ultimo_visitado][estaciones[i].id];
        nueva_distancia = proxima_distancia + distancia_acumulada(visitados,distancias);
      }
      if ( (get<0>(soluciones) >= 0 && nueva_distancia < get<0>(soluciones)) || (get<0>(soluciones) < 0) ) {
        if (puede_ganar_gimnasio(estaciones[i],potasActuales) || puede_recibir_potas(estaciones[i],potasActuales,k)) {    //Poda: no va a la pokeparada si la mochila está llena
          visitados.push_back(estaciones[i]);
          int nuevoPotasActuales = (estaciones[i].esGimnasio || potasActuales + 3 <= k) ? potasActuales + estaciones[i].potas : k;
          estaciones.erase(estaciones.begin() + i);
          BT_capturar_gimnasios(estaciones,distancias,n,m,k,visitados,nuevoPotasActuales,soluciones);
          Estacion ultimaEstacion(visitados.back());
          visitados.pop_back();
          estaciones.insert(estaciones.begin() + i, ultimaEstacion);
        }
      }
    }
  }

}

bool puede_ganar_gimnasio(Estacion &estacion,int potas){
    return estacion.esGimnasio && estacion.potas+potas >= 0;
}

bool puede_recibir_potas(Estacion &estacion,int potas,int tamano_mochila){
  return (!estacion.esGimnasio) && (potas < tamano_mochila);
}

bool puede_ser_que_tenga_solucion(vector<Estacion> &estaciones, int k){
  int potasNecesarias = 0;
  int potasPosibles = 0;
  for (int i = 0; i  < estaciones.size(); i++) {
    if(estaciones[i].esGimnasio){
      int potas_gym = estaciones[i].potas;
      if (k + potas_gym < 0) return false; //Poda: Tamaño de la mochila >= potas del gimnasio
      potasNecesarias = potasNecesarias - potas_gym; //potas_gym es <0
    }
    else{
      potasPosibles += 3;
    }
  }
  return potasNecesarias <= potasPosibles; //Poda: sumatoria (posiones(gimnasio)) <= m*3 con m == cantidad de pokeparadas
}


bool es_solucion(std::vector<Estacion> &estaciones){
  for (int i = 0; i < estaciones.size(); i++) {
    if(estaciones[i].esGimnasio) {
      return false;
    }
  }
  return true;
}

double distancia_acumulada(vector<Estacion> &visitados, const std::vector<std::vector<double> > &distancias){
  double distancia = 0;
  for (int i = 0; i < visitados.size() - 1; ++i) {
    distancia += distancias[visitados[i].id][visitados[i+1].id];
  }
  return distancia;
}