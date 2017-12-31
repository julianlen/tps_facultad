#include "ejercicio1.h"

using namespace std;

int cruzarPuente(vector<int> const &canibales, vector<int> const &arqueologos){
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

void BTCruzarPuente(vector<int> const &canibalesOrigen, vector<int> const &arqueologosOrigen, vector<int> const &canibalesDestino, vector<int> const &arqueologosDestino, bool linternaDer, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones){
  vector<int> canibalesDer = linternaDer ? canibalesOrigen : canibalesDestino;
  vector<int> canibalesIzq = linternaDer ? canibalesDestino : canibalesOrigen;
  vector<int> arqueologosDer = linternaDer ? arqueologosOrigen : arqueologosDestino;
  vector<int> arqueologosIzq = linternaDer ? arqueologosDestino : arqueologosOrigen;

  bool esSolucion = canibalesIzq.size() + arqueologosIzq.size() == 0;

  if (esSolucion){

    soluciones.push_back(tiempo);

  }else{

    // Estado nuevoEstado;
    vector<int> nuevoCanibalesOrigen;
    vector<int> nuevoArqueologosOrigen;
    vector<int> nuevoCanibalesDestino;
    vector<int> nuevoArqueologosDestino;

    int cantCanibalesOrigen = canibalesOrigen.size();
    int cantArqueologosOrigen = arqueologosOrigen.size();
    int cantCanibalesDestino = canibalesDestino.size();
    int cantArqueologosDestino = arqueologosDestino.size();
    bool nuevaLinternaDer = !linternaDer;

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

          if(mandarCanibales == 2 && mandarArqueologos == 0){
            mover2PersonasMismoGrupo(nuevoCanibalesOrigen,
                                      nuevoCanibalesDestino,
                                      nuevoArqueologosOrigen,
                                      nuevoArqueologosDestino,
                                      linternaDer, true,
                                      estadosAnteriores, tiempo,
                                      soluciones);
          }

          if(mandarCanibales == 0 && mandarArqueologos == 2){
            mover2PersonasMismoGrupo(nuevoArqueologosOrigen,
                                      nuevoArqueologosDestino,
                                      nuevoCanibalesOrigen,
                                      nuevoCanibalesDestino,
                                      linternaDer, false,
                                      estadosAnteriores, tiempo,
                                      soluciones);
          }

          if(mandarCanibales == 1 && mandarArqueologos == 0){
            mover1Persona1Grupo(nuevoCanibalesOrigen,
                                nuevoCanibalesDestino,
                                nuevoArqueologosOrigen,
                                nuevoArqueologosDestino,
                                linternaDer, true,
                                estadosAnteriores, tiempo,
                                soluciones);
          }

          if(mandarCanibales == 0 && mandarArqueologos == 1){
            mover1Persona1Grupo(nuevoArqueologosOrigen,
                                nuevoArqueologosDestino,
                                nuevoCanibalesOrigen,
                                nuevoCanibalesDestino,
                                linternaDer, false,
                                estadosAnteriores, tiempo,
                                soluciones);
          }

          if(mandarCanibales == 1 && mandarArqueologos == 1){
            mover2PersonasDistintoGrupo(nuevoArqueologosOrigen,
                                        nuevoArqueologosDestino,
                                        nuevoCanibalesOrigen,
                                        nuevoCanibalesDestino,
                                        linternaDer,
                                        estadosAnteriores, tiempo,
                                        soluciones);
          }
        }
      }
    }
  }
}

void mover2PersonasMismoGrupo(vector<int> &grupoOrigen, vector<int> &grupoDestino, vector<int> &grupoFijoOrigen, vector<int> &grupoFijoDestino,  bool linternaLadoDer, bool sonCanibales, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones){ //linternaLadoDer == false ? origen = izquierda : origen = derecha
  Estado nuevoEstado;
  bool nuevaLinterna = !linternaLadoDer;
  vector<int> copiaOrigen = grupoOrigen;
  int cantGrupoOrigen = grupoOrigen.size();
  for (int i = 0; i < cantGrupoOrigen; ++i){
    grupoDestino.push_back(grupoOrigen[i]);
    int velocidad1 = grupoOrigen[i];
    grupoOrigen.erase(grupoOrigen.begin() + i);
    for (int k = i ; k < cantGrupoOrigen-1; ++k){
      grupoDestino.push_back(grupoOrigen[k]);
      int velocidad2 = grupoOrigen[k];
      vector<int> temp = grupoOrigen;
      grupoOrigen.erase(grupoOrigen.begin() + k);
      int nuevoTiempo = tiempo + max(velocidad1, velocidad2);
      if(linternaLadoDer){
        if(sonCanibales){
          nuevoEstado.set_estado(grupoFijoDestino.size(), grupoDestino.size(), grupoFijoOrigen.size(), grupoOrigen.size(), nuevaLinterna);
          estadosAnteriores.push_back(nuevoEstado);
          BTCruzarPuente(grupoDestino, grupoFijoDestino, grupoOrigen, grupoFijoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
        }
        else{
          nuevoEstado.set_estado(grupoDestino.size(), grupoFijoDestino.size(), grupoOrigen.size(), grupoFijoOrigen.size(), nuevaLinterna);
          estadosAnteriores.push_back(nuevoEstado);
          BTCruzarPuente(grupoFijoDestino, grupoDestino, grupoFijoOrigen, grupoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
        }
      }
      else{
        if(sonCanibales){
          nuevoEstado.set_estado(grupoFijoOrigen.size(), grupoOrigen.size(), grupoFijoDestino.size(), grupoDestino.size(), nuevaLinterna);
          estadosAnteriores.push_back(nuevoEstado);
          BTCruzarPuente(grupoDestino, grupoFijoDestino, grupoOrigen, grupoFijoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
        }
        else{
          nuevoEstado.set_estado(grupoOrigen.size(), grupoFijoOrigen.size(), grupoDestino.size(), grupoFijoDestino.size(), nuevaLinterna);
          estadosAnteriores.push_back(nuevoEstado);
          BTCruzarPuente(grupoFijoDestino, grupoDestino, grupoFijoOrigen, grupoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
        }
      }
      estadosAnteriores.pop_back();
      grupoDestino.pop_back();
      grupoOrigen = temp;
    }
    grupoDestino.pop_back();
    grupoOrigen = copiaOrigen;
  }
}

void mover1Persona1Grupo(vector<int> &grupoOrigen, vector<int> &grupoDestino, vector<int> &grupoFijoOrigen, vector<int> &grupoFijoDestino,  bool linternaLadoDer, bool sonCanibales, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones){  //linternaLadoDer == false ? origen = izquierda : origen = derecha
  Estado nuevoEstado;
  bool nuevaLinterna = !linternaLadoDer;
  vector<int> copiaOrigen = grupoOrigen;
  int cantGrupoOrigen = grupoOrigen.size();
  for (int i = 0; i < cantGrupoOrigen; ++i){
    grupoDestino.push_back(grupoOrigen[i]);
    int velocidad1 = grupoOrigen[i];
    grupoOrigen.erase(grupoOrigen.begin() + i);
    int nuevoTiempo = tiempo + velocidad1;
    if(linternaLadoDer){
      if(sonCanibales){
        nuevoEstado.set_estado(grupoFijoDestino.size(), grupoDestino.size(), grupoFijoOrigen.size(), grupoOrigen.size(), nuevaLinterna);
        estadosAnteriores.push_back(nuevoEstado);
        BTCruzarPuente(grupoDestino, grupoFijoDestino, grupoOrigen, grupoFijoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
      }
      else{
        nuevoEstado.set_estado(grupoDestino.size(), grupoFijoDestino.size(), grupoOrigen.size(), grupoFijoOrigen.size(), nuevaLinterna);
        estadosAnteriores.push_back(nuevoEstado);
        BTCruzarPuente(grupoFijoDestino, grupoDestino, grupoFijoOrigen, grupoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
      }
    }
    else{
      if(sonCanibales){
        nuevoEstado.set_estado(grupoFijoOrigen.size(), grupoOrigen.size(), grupoFijoDestino.size(), grupoDestino.size(), nuevaLinterna);
        estadosAnteriores.push_back(nuevoEstado);
        BTCruzarPuente(grupoDestino, grupoFijoDestino, grupoOrigen, grupoFijoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
      }
      else{
        nuevoEstado.set_estado(grupoOrigen.size(), grupoFijoOrigen.size(), grupoDestino.size(), grupoFijoDestino.size(), nuevaLinterna);
        estadosAnteriores.push_back(nuevoEstado);
        BTCruzarPuente(grupoFijoDestino, grupoDestino, grupoFijoOrigen, grupoOrigen, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
      }
    }
    estadosAnteriores.pop_back();
    grupoDestino.pop_back();
    grupoOrigen = copiaOrigen;
  }
}

void mover2PersonasDistintoGrupo(vector<int> &grupoOrigenA, vector<int> &grupoDestinoA, vector<int> &grupoOrigenB, vector<int> &grupoDestinoB,  bool linternaLadoDer, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones){
  Estado nuevoEstado;
  bool nuevaLinterna = !linternaLadoDer;
  vector<int> copiaOrigenA = grupoOrigenA;
  vector<int> copiaOrigenB = grupoOrigenB;
  int cantGrupoOrigenA = grupoOrigenA.size();
  int cantGrupoOrigenB = grupoOrigenB.size();
  for (int i = 0; i < cantGrupoOrigenA; ++i){
    grupoDestinoA.push_back(grupoOrigenA[i]);
    int velocidad1 = grupoOrigenA[i];
    grupoOrigenA.erase(grupoOrigenA.begin() + i);
    for (int k = 0 ; k < cantGrupoOrigenB; ++k){
      grupoDestinoB.push_back(grupoOrigenB[k]);
      int velocidad2 = grupoOrigenB[k];
      grupoOrigenB.erase(grupoOrigenB.begin() + k);
      int nuevoTiempo = tiempo + max(velocidad1, velocidad2);
      if(linternaLadoDer){
        nuevoEstado.set_estado(grupoDestinoA.size(), grupoDestinoB.size(), grupoOrigenA.size(), grupoOrigenB.size(), nuevaLinterna);
        estadosAnteriores.push_back(nuevoEstado);
        BTCruzarPuente(grupoDestinoB, grupoDestinoA, grupoOrigenB, grupoOrigenA, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
      }
      else{
        nuevoEstado.set_estado(grupoOrigenA.size(), grupoOrigenB.size(), grupoDestinoA.size(), grupoDestinoB.size(), nuevaLinterna);
        estadosAnteriores.push_back(nuevoEstado);
        BTCruzarPuente(grupoDestinoB, grupoDestinoA, grupoOrigenB, grupoOrigenA, nuevaLinterna, estadosAnteriores, nuevoTiempo, soluciones);
      }
      estadosAnteriores.pop_back();
      grupoDestinoB.pop_back();
      grupoOrigenB = copiaOrigenB;
    }
    grupoDestinoA.pop_back();
    grupoOrigenA = copiaOrigenA;
  }
}

bool estadoValido(int cantCanibalesOrigen, int cantArqueologosOrigen, int cantCanibalesDestino, int cantArqueologosDestino, bool linternaDer, vector<Estado> const &estadosAnteriores){
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

int indexOf(int valor, vector<int> const &lista){
  int largo = lista.size();
  for (int k = 0; k < largo; ++k){
    if(lista[k] == valor){
      return k;
    }
  }
  return -1;
}

int maximo(vector<int> const &lista){
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

int minimo(vector<int> const &lista){
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
