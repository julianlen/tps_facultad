#include <grafos.h>
#include <iostream>

void mirarDerechaYAbajo(int f, int c, int p, int u, int nivelActual, int i, int k, char derecha, char abajo, Grafos::ListaAdy &grafo);
void mirarDerechaYArriba(int f, int c, int p, int u, int nivelActual, int i, int k, char derecha, char arriba, Grafos::ListaAdy &grafo);
void mirarDerechaArribaYAbajo(int f, int c, int p, int u, int nivelActual, int i, int k, char derecha, char arriba, char abajo, Grafos::ListaAdy &grafo);
void mirarIzquierdaYAbajo(int f, int c, int p, int u, int nivelActual, int i, int k, char izquierda, char abajo ,  Grafos::ListaAdy &grafo);
void mirarIzquierdaYArriba(int f, int c, int p, int u, int nivelActual, int i, int k, char izquierda, char arriba ,  Grafos::ListaAdy &grafo);
void mirarIzquierdaArribaYAbajo(int f, int c, int p, int u, int nivelActual, int i, int k, char izquierda, char arriba , char abajo, Grafos::ListaAdy &grafo);
void mirarIzquierdaDerechaYAbajo(int f, int c, int p, int u, int nivelActual, int i, int k, char izquierda, char derecha , char abajo, Grafos::ListaAdy &grafo);
void mirarTodos(int f, int c, int p, int u, int nivelActual, int i, int k, char izquierda, char derecha , char abajo, char arriba, Grafos::ListaAdy &grafo);
void mirarIzquierdaDerechaYArriba(int f, int c, int p, int u, int nivelActual, int i, int k, char izquierda, char derecha , char arriba, Grafos::ListaAdy &grafo);
int parserEj1(int f, int c, int p, std::vector< std::vector < char > > matriz, Grafos::ListaAdy &grafo, int &s, int &t);
