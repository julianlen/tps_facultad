#include "ejercicio1.h"

using namespace std;

int cruzarPuente(vector<int> canibales, vector<int> arqueologos){
  vector<int> arqDer;
  vector<int> caniDer;
  Estado primerEstado(arqueologos.size(), canibales.size(), arqDer.size(), caniDer.size(), false);
  vector<int> resultados;
  vector<Estado> estados;
  estados.push_back(primerEstado);
  int resultado = -1;
  if(canibales.size() <= arqueologos.size() || arqueologos.size() == 0){
    BTCruzarPuente(canibales, arqueologos, caniDer, arqDer, false, estados, 0, resultados);
    resultado = minimo(resultados);
  }
  return resultado;
}

void BTCruzarPuente(vector<int> canibalesOrigen, vector<int> arqueologosOrigen, vector<int> canibalesDestino, vector<int> arqueologosDestino, bool linternaDer, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones){
  vector<int> canibalesDer = linternaDer ? canibalesOrigen : canibalesDestino;
  vector<int> canibalesIzq = linternaDer ? canibalesDestino : canibalesOrigen;
  vector<int> arqueologosDer = linternaDer ? arqueologosOrigen : arqueologosDestino;
  vector<int> arqueologosIzq = linternaDer ? arqueologosDestino : arqueologosOrigen;

  bool esSolucion = canibalesIzq.size() + arqueologosIzq.size() == 0;

  if (esSolucion){

    soluciones.push_back(tiempo);

  }else{

    Estado nuevoEstado;
    vector<int> nuevoCanibalesOrigen;
    vector<int> nuevoArqueologosOrigen;
    vector<int> nuevoCanibalesDestino;
    vector<int> nuevoArqueologosDestino;

    int cantCanibalesOrigen = canibalesOrigen.size();
    int cantArqueologosOrigen = arqueologosOrigen.size();
    int cantCanibalesDestino = canibalesDestino.size();
    int cantArqueologosDestino = arqueologosDestino.size();
    bool nuevaLinternaDer = !linternaDer;

    if (canibalesOrigen.size() > 0) { sort(canibalesOrigen.begin(), canibalesOrigen.end()); }
    if (canibalesDestino.size() > 0) { sort(canibalesDestino.begin(), canibalesDestino.end()); }
    if (arqueologosOrigen.size() > 0) { sort(arqueologosOrigen.begin(), arqueologosOrigen.end()); }
    if (arqueologosDestino.size() > 0) { sort(arqueologosDestino.begin(), arqueologosDestino.end()); }

    //Mando 0 canibales y 1 arqueologo, o
    //0 canibales y 2 arqueologos, o
    //1 canibal y 1 arqueologo o
    //2 canibales o 0 arqueologos
    for (int mandarCanibales = 0; mandarCanibales <= 2; mandarCanibales++){
      for (int mandarArqueologos = mandarCanibales == 0 ? 1 : 0; mandarArqueologos <= 2 - mandarCanibales; mandarArqueologos++){
        if (estadoValido(cantCanibalesOrigen - mandarCanibales,
                         cantArqueologosOrigen - mandarArqueologos,
                         cantCanibalesDestino + mandarCanibales,
                         cantArqueologosDestino + mandarArqueologos,
                         linternaDer, estadosAnteriores)){

          //Hago una copia de las listas (para no modificar otras listas)
          nuevoCanibalesOrigen = canibalesOrigen;
          nuevoArqueologosOrigen = arqueologosOrigen;
          nuevoCanibalesDestino = canibalesDestino;
          nuevoArqueologosDestino = arqueologosDestino;

          vector<int> canibalesMasRapidos;
          if (mandarCanibales > 0){
            for (int q = 0; q < mandarCanibales; ++q){
              canibalesMasRapidos.push_back(nuevoCanibalesOrigen[q]);
            }

            for (int i = 0; i < mandarCanibales; i++){
              int index = indexOf(canibalesMasRapidos[i], nuevoCanibalesOrigen);
              nuevoCanibalesOrigen.erase(nuevoCanibalesOrigen.begin() + index);
              nuevoCanibalesDestino.push_back(canibalesMasRapidos[i]);
            }
          }

          vector<int> arqueologosMasRapidos;
          if (mandarArqueologos > 0){
            for (int q = 0; q < mandarArqueologos; ++q){
              arqueologosMasRapidos.push_back(nuevoArqueologosOrigen[q]);
            }

            for (int i = 0; i < mandarArqueologos; i++){
              int index = indexOf(arqueologosMasRapidos[i], nuevoArqueologosOrigen);
              nuevoArqueologosOrigen.erase(nuevoArqueologosOrigen.begin() + index);
              nuevoArqueologosDestino.push_back(arqueologosMasRapidos[i]);
            }
          }

          int arqueologosDerNuevoEstado = arqueologosDer.size() + (linternaDer ? -1 : 1) * mandarArqueologos;
          int arqueologosIzqNuevoEstado = arqueologosIzq.size() + (linternaDer ? 1 : -1) * mandarArqueologos;
          int canibalesDerNuevoEstado   = canibalesDer.size()   + (linternaDer ? -1 : 1) * mandarCanibales;
          int canibalesIzqNuevoEstado   = canibalesIzq.size()   + (linternaDer ? 1 : -1) * mandarCanibales;
          bool linternaDerNuevoEstado   = nuevaLinternaDer;

          nuevoEstado.set_estado(arqueologosIzqNuevoEstado, canibalesIzqNuevoEstado, arqueologosDerNuevoEstado, canibalesDerNuevoEstado, linternaDerNuevoEstado);

          estadosAnteriores.push_back(nuevoEstado);
          int nuevoTiempo = tiempo + max(mandarArqueologos > 0 ? maximo(arqueologosMasRapidos) : 0, mandarCanibales > 0 ? maximo(canibalesMasRapidos) : 0);
          BTCruzarPuente(nuevoCanibalesDestino, nuevoArqueologosDestino, nuevoCanibalesOrigen, nuevoArqueologosOrigen, nuevaLinternaDer, estadosAnteriores, nuevoTiempo, soluciones);
          estadosAnteriores.pop_back();
        }
      }
    }
  }
}

bool estadoValido(int cantCanibalesOrigen, int cantArqueologosOrigen, int cantCanibalesDestino, int cantArqueologosDestino, bool linternaDer, vector<Estado> estadosAnteriores){
  if (cantCanibalesOrigen < 0 || cantArqueologosOrigen < 0){ return false; }

  int canibalesDer = linternaDer ? cantCanibalesOrigen : cantCanibalesDestino;
  int canibalesIzq = linternaDer ? cantCanibalesDestino : cantCanibalesOrigen;
  int arqueologosDer = linternaDer ? cantArqueologosOrigen : cantArqueologosDestino;
  int arqueologosIzq = linternaDer ? cantArqueologosDestino : cantArqueologosOrigen;

  if ((0 < arqueologosDer && arqueologosDer < canibalesDer) ||
    (0 < arqueologosIzq && arqueologosIzq < canibalesIzq))
    return false;

  for (uint i = 0; i < estadosAnteriores.size(); i++)
  {
    Estado estadoAnterior = estadosAnteriores[i];
    if (estadoAnterior.arqueologosDer == arqueologosDer &&
      estadoAnterior.canibalesDer == canibalesDer &&
      estadoAnterior.linternaDer == !linternaDer)
      return false;
  }

  return true;
}


int indexOf(int valor, vector<int> lista){
  int largo = lista.size();
  for (int k = 0; k < largo; ++k){
    if(lista[k] == valor){
      return k;
    }
  }
  return -1;
}

int maximo(vector<int> lista){
  int largo = lista.size();
  int res;
  if (largo > 0) {
    res = lista[0];
  }else{
    res = -1;
  }
  for (int k = 0; k < largo; ++k){
    if (res < lista[k]) res = lista[k];
  }
  return res;
}

int minimo(vector<int> lista){
  int largo = lista.size();
  int res;
  if (largo > 0) {
    res = lista[0];
  }else{
    res = -1;
  }
  for (int k = 0; k < largo; ++k){
    if (res > lista[k]) res = lista[k];
  }
  return res;
}
