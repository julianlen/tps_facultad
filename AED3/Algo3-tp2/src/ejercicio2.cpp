#include <ejercicio2.h>

using namespace std;

int solveEj2(vector< vector< char > > matriz, int filasReal, int columnasReal){
  int nodos = 0;
  bool encerrado = false;
  bool encerradoRes = false;
  vector<arista> aristas;
  for (int iFilas = 0; iFilas < filasReal; ++iFilas) { //Para este entonces, asumo que aquellas paredes indestructibles, seran pasadas como #.
    for (int iColumnas = 0; iColumnas < columnasReal; ++iColumnas) {
      if (matriz[iFilas][iColumnas] == '.') {
        nodos++; //Chequeo cuantos nodos hay
        if (matriz[iFilas][iColumnas + 1] != '#') {
        	arista a;
        	a.inicio = iFilas * columnasReal + iColumnas;
        	a.fin = iFilas * columnasReal + iColumnas + 1;
        	a.costo = 0;
        	aristas.push_back(a);
        } //La entrada es guardada como una matriz.

        if (matriz[iFilas + 1][iColumnas] != '#') {
        	arista a;
        	a.inicio = iFilas * columnasReal + iColumnas;
        	a.fin = (iFilas + 1) * columnasReal + iColumnas;
        	a.costo = 0;
        	aristas.push_back(a);
        }
        encerrado = matriz[iFilas][iColumnas + 1] == '#' && matriz[iFilas + 1][iColumnas] == '#' && matriz[iFilas - 1][iColumnas] == '#' && matriz[iFilas][iColumnas - 1] == '#';
        encerradoRes = encerradoRes || encerrado;
        //Me fijo si hay algun nodo inalcanzable (en el caso de que haya uno solo se contempla con #nodos).

      }

      if (esNumero(matriz[iFilas][iColumnas])) {
        bool puseNumero = false;
        if (matriz[iFilas][iColumnas + 1] != '#' && !esNumero(matriz[iFilas][iColumnas + 1])) {
        	arista a;
        	a.inicio = iFilas * columnasReal + iColumnas;
        	a.fin = iFilas * columnasReal + iColumnas + 1;
        	a.costo = matriz[iFilas][iColumnas] - '0';
        	aristas.push_back(a);
        	puseNumero = true;
        } 
        if (matriz[iFilas + 1][iColumnas] != '#' && !esNumero(matriz[iFilas + 1][iColumnas])) {
        	arista a;
        	a.inicio = iFilas * columnasReal + iColumnas;
        	a.fin = (iFilas + 1) * columnasReal + iColumnas;
        	a.costo = 0;
        	if(!puseNumero)
        	  a.costo = matriz[iFilas][iColumnas] - '0';
        	aristas.push_back(a);
        }
      }
    }
  }
  int res = 0;

  if(nodos == 0 || (nodos > 1 && encerradoRes) ){ //Chequeo que sean todas paredes o haya alguno inalcanzable
    res = -1;
  }
  else{
    int V = filasReal*columnasReal; //Kruskal
    init(V);
    vector<arista> solucion;
    sort(aristas.begin(), aristas.end()); // ordeno las aristas por costo de menor a mayor


    for (uint i = 0; i < aristas.size(); i++) {
      arista a = aristas[i];
      if (find(a.inicio) != find(a.fin)) {
        solucion.push_back(a);
        uni(a.inicio, a.fin);
      }
    } //Fin Kruskal

    for (int i = 0; i < solucion.size(); ++i)
    {
      res += solucion[i].costo;
    }
  }

  return res;
}