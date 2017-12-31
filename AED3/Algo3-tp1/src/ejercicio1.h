#include <vector>
#include <iostream>
#include <algorithm> //Sort esta en O(n*Log n) y reverse en O(n)
#include "Estado.h"

#include "estructuras.h"
using namespace std;

int cruzarPuente(vector<int> const &canibales, vector<int> const &arqueologos);
void BTCruzarPuente(vector<int> const &canibalesOrigen, vector<int> const &arqueologosOrigen, vector<int> const &canibalesDestino, vector<int> const &arqueologosDestino, bool linternaDer, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones);
void mover1Persona1Grupo(vector<int> &grupoOrigen, vector<int> &grupoDestino, vector<int> &grupoFijoOrigen, vector<int> &grupoFijoDestino,  bool linternaLadoDer, bool sonCanibales, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones);
void mover2PersonasMismoGrupo(vector<int> &grupoOrigen, vector<int> &grupoDestino, vector<int> &grupoFijoOrigen, vector<int> &grupoFijoDestino,  bool linternaLadoDer, bool sonCanibales, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones);
void mover2PersonasDistintoGrupo(vector<int> &grupoOrigenA, vector<int> &grupoDestinoA, vector<int> &grupoOrigenB, vector<int> &grupoDestinoB,  bool linternaLadoDer, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones);
bool estadoValido(int cantCanibalesOrigen, int cantArqueologosOrigen, int cantCanibalesDestino, int cantArqueologosDestino, bool linternaDer, vector<Estado> const &estadosAnteriores);
int indexOf(int valor, vector<int> const &lista);
int maximo(vector<int> const &lista);
int minimo(vector<int> const &lista);
void sort(vector<int> &lista);
void swap(vector<int> &lista, int i, int q);