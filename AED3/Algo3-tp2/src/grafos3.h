#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>
#include <tuple>
#include <set>

#define INFINITO 1001 //C <= 10^3

using namespace std;

typedef pair<int, int> t_node; //nroNodo, peso
typedef tuple<int, int, int> ABC; //Para llegar de A a B tarda C

namespace grafos3 {
    struct Cmp
    {
        bool operator ()(const pair<int, int> &a, const pair<int, int> &b)
        {
            return a.first < b.first && a.second != b.second;
        }
    };

    struct salida {
        int T; //mínimo tiempo para ir de la estación 1 a N, o -1
        int S; //cantidad de estaciones que debe recorrer
        vector<int> escape; //S enteros que indican la forma de escapar lo más rapido posible
    };

    class ListAdy {
        public:
            ListAdy(int estaciones, int vias, vector<ABC> recorridos);  // Constructor
            salida dijkstra();
        private:
            int N;
            int M;
            vector< vector < t_node > > adyacencia;
    };
}



