#include <grafos.h>

Grafos::ListaAdy::ListaAdy(int n){
    this->nodosTotales = n;
    std::vector< std::vector < int > > listaAd(n);
    this->adyacencia = listaAd;
}

void Grafos::ListaAdy::agregarArista(int u, int v){
    this->adyacencia[u].push_back(v);
}

int Grafos::ListaAdy::BFS(int s, int t, int f, int c){
  int res = -1;
  std::queue<int> cola;
  int distancias[this->nodosTotales];
  //inicializo distancias en negativo ya que no se puede usar "infinito"
  for (int i = 0; i < this->nodosTotales; ++i){
    distancias[i] = -1;
  }

  cola.push(s);
  distancias[s] = 0;
  while (!cola.empty()) {
    int tope = cola.front();
    cola.pop();
    if ((tope % (f*c)) == t) {
      return distancias[tope];
    }
    for (int nroVecino = 0; nroVecino < this->adyacencia[tope].size(); ++nroVecino){
      if (distancias[this->adyacencia[tope][nroVecino]] < 0){
        distancias[this->adyacencia[tope][nroVecino]] = distancias[tope] + 1;
        cola.push(this->adyacencia[tope][nroVecino]);
      }
    }
  }
  return res;
}