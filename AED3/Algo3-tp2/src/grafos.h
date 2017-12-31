#include <vector>
#include <queue>
#include <iostream>

#ifndef GRAFOS_CLASS
#define GRAFOS_CLASS


namespace Grafos {

    class ListaAdy{

        public:
            int nodosTotales;
            std::vector< std::vector < int > > adyacencia;
            ListaAdy(int n);  // Constructor
            void agregarArista(int u, int v);
            int BFS(int s, int t, int f, int c);

    };
}

#endif