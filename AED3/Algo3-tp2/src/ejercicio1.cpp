#include <ejercicio1.h>

void mirarDerechaYAbajo(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char derecha, char abajo, Grafos::ListaAdy &grafo){
  if (abajo == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k+1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*nivelActual)) );
  }

  if (derecha == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*nivelActual)) );
  }
}

void mirarDerechaYArriba(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char derecha, char arriba, Grafos::ListaAdy &grafo){
  if (arriba == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*(nivelActual+1))) );
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*nivelActual)) );
  }

  if (derecha == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*(nivelActual+1))) );
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*nivelActual)) );
  }
}

void mirarDerechaArribaYAbajo(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char derecha, char arriba, char abajo, Grafos::ListaAdy &grafo){
  if (arriba == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*(nivelActual+1))) );
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*nivelActual)) );
  }

  if (abajo == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*(nivelActual+1))) );
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*nivelActual)) );
  }

  if (derecha == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*(nivelActual+1))) );
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*nivelActual)) );
  }
}

void mirarIzquierdaYAbajo(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char izquierda, char abajo ,  Grafos::ListaAdy &grafo){
  if (abajo == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k+1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*nivelActual)) );
  }

  if (izquierda == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*nivelActual)) );
  }
}
void mirarIzquierdaYArriba(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char izquierda, char arriba ,  Grafos::ListaAdy &grafo){
  if (arriba == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k-1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*nivelActual)) );
  }

  if (izquierda == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*nivelActual)) );
  }
}
void mirarIzquierdaArribaYAbajo(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char izquierda, char arriba , char abajo, Grafos::ListaAdy &grafo){
  if (abajo == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k+1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*nivelActual)) );
  }

  if (arriba == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k-1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*nivelActual)) );
  }

  if (izquierda == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*nivelActual)) );
  }
}
void mirarIzquierdaDerechaYAbajo(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char izquierda, char derecha , char abajo, Grafos::ListaAdy &grafo){
  if (abajo == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k+1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*nivelActual)) );
  }

  if (derecha == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*nivelActual)) );
  }

  if (izquierda == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*nivelActual)) );
  }
}
void mirarTodos(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char izquierda, char derecha , char abajo, char arriba, Grafos::ListaAdy &grafo){
  if (abajo == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k+1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k+1)+(f*c*nivelActual)) );
  }

  if (arriba == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k-1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*nivelActual)) );
  }

  if (derecha == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*nivelActual)) );
  }

  if (izquierda == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*nivelActual)) );
  }
}
void mirarIzquierdaDerechaYArriba(int f, int c, int p, int nodoActual, int nivelActual, int i, int k, char izquierda, char derecha , char arriba, Grafos::ListaAdy &grafo){
  if (arriba == '#'){
    if (nivelActual < p) grafo.agregarArista(nodoActual, ( (f*i+k-1)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*i+k-1)+(f*c*nivelActual)) );
  }

  if (derecha == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i+1)+k)+(f*c*nivelActual)) );
  }

  if (izquierda == '#') {
    if (nivelActual < p) grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*(nivelActual+1)) ));
  }
  else{
    grafo.agregarArista(nodoActual, ((f*(i-1)+k)+(f*c*nivelActual)) );
  }
}

int parserEj1(int f, int c, int p, std::vector< std::vector < char > > matriz, Grafos::ListaAdy &grafo, int &s, int &t){

  //verifico que sean caracteres validos
  char inicio = 'o';
  short inicios = 0;
  char fin = 'x';
  short finales = 0;
  for (int i = 0; i < c; ++i){
    for (int k = 0; k < f; ++k){
      if (matriz[i][k] == inicio){
        if (inicios > 0){
          std::cout << "Error en parser. Hay mas de dos inicios" << std::endl;
          return -1;
        }
        else{
          inicios++;
          s = f*i+k;
        }
      }
      else if (matriz[i][k] == fin){
        if (finales > 0){
          std::cout << "Error en parser. Hay mas de dos finales" << std::endl;
          return -1;
        }
        else{
          finales++;
          t = f*i+k;
        }
      }
      else if (matriz[i][k] != '#' && matriz[i][k] != '.'){
        std::cout << "Error en parser. Caracter no valido: " << matriz[i][k] << " " << i << " " << k << std::endl;
        return -1;
      }
    }
  }

  //parseo la entrada a grafo
  for (int nivelActual = 0; nivelActual <= p; ++nivelActual){
    for (int i = 0; i < c; ++i){
      for (int k = 0; k < f; ++k){
        int nodoActual = f*i+k+(f*c*nivelActual);
        if (i == 0){
          if (k == 0){
            char derecha = matriz[i+1][k];
            char abajo = matriz[i][k+1];
            mirarDerechaYAbajo(f,c,p,nodoActual,nivelActual,i,k,derecha,abajo,grafo);
          }
          else if (k == f-1){
            char derecha = matriz[i+1][k];
            char arriba = matriz[i][k-1];
            mirarDerechaYArriba(f,c,p,nodoActual,nivelActual,i,k,derecha,arriba,grafo);
          }
          else{
            char derecha = matriz[i+1][k];
            char abajo = matriz[i][k+1];
            char arriba = matriz[i][k-1];
            mirarDerechaArribaYAbajo(f,c,p,nodoActual,nivelActual,i,k,derecha,arriba,abajo,grafo);
          }
        }
        else if (i == c-1){
          if (k == 0){
            char izquierda = matriz[i-1][k];
            char abajo = matriz[i][k+1];
            mirarIzquierdaYAbajo(f,c,p,nodoActual,nivelActual,i,k,izquierda,abajo,grafo);
          }
          else if (k == f-1){
            char izquierda = matriz[i-1][k];
            char arriba = matriz[i][k-1];
            mirarIzquierdaYArriba(f,c,p,nodoActual,nivelActual,i,k,izquierda,arriba,grafo);
          }
          else{
            char izquierda = matriz[i-1][k];
            char abajo = matriz[i][k+1];
            char arriba = matriz[i][k-1];
            mirarIzquierdaArribaYAbajo(f,c,p,nodoActual,nivelActual,i,k,izquierda,arriba,abajo,grafo);
          }
        }
        else{
          if (k == 0){
            char izquierda = matriz[i-1][k];
            char derecha = matriz[i+1][k];
            char abajo = matriz[i][k+1];
            mirarIzquierdaDerechaYAbajo(f,c,p,nodoActual,nivelActual,i,k,izquierda,derecha,abajo,grafo);
          }
          else if (k == f-1){
            char izquierda = matriz[i-1][k];
            char derecha = matriz[i+1][k];
            char arriba = matriz[i][k-1];
            mirarIzquierdaDerechaYArriba(f,c,p,nodoActual,nivelActual,i,k,izquierda,derecha,arriba,grafo);
          }
          else{
            char izquierda = matriz[i-1][k];
            char derecha = matriz[i+1][k];
            char abajo = matriz[i][k+1];
            char arriba = matriz[i][k-1];
            mirarTodos(f,c,p,nodoActual,nivelActual,i,k,izquierda,derecha,abajo,arriba,grafo);
          }
        }
      }
    }
  }
  return 0;
}