#include <stdbool.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef pair<int, vector< vector<int> > > salida;

salida Mochilero(int cantMochilas, int cantTesoros, vector<int> capacidades, vector<int> tesoroCant, vector<int> tesoroPeso, vector<int> tesoroValor);
