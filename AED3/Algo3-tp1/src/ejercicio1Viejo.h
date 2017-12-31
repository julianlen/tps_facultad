#include <vector>
#include <iostream>
#include <algorithm> //Sort esta en O(n*Log n) y reverse en O(n)
#include "Estado.h"

#include "estructuras.h"
using namespace std;

int cruzarPuente(vector<int> canibales, vector<int> arqueologos);
void BTCruzarPuente(vector<int> canibalesOrigen, vector<int> arqueologosOrigen, vector<int> canibalesDestino, vector<int> arqueologosDestino, bool linternaDer, vector<Estado> &estadosAnteriores, int tiempo, vector<int> &soluciones);
bool estadoValido(int cantCanibalesOrigen, int cantArqueologosOrigen, int cantCanibalesDestino, int cantArqueologosDestino, bool linternaDer, vector<Estado> estadosAnteriores);
int indexOf(int valor, vector<int> lista);
int maximo(vector<int> lista);
int minimo(vector<int> lista);
void sort(vector<int> &lista);
void swap(vector<int> &lista, int i, int q);