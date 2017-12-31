#include "Estado.h"

Estado::Estado(){
  this->arqueologosIzq = 0;
  this->canibalesIzq = 0;
  this->arqueologosDer = 0;
  this->canibalesDer = 0;
  this->linternaDer = true;
}

Estado::Estado(int arqueologosIzq, int canibalesIzq, int arqueologosDer, int canibalesDer, bool linternaDerecha){
  this->arqueologosIzq = arqueologosIzq;
  this->canibalesIzq = canibalesIzq;
  this->arqueologosDer = arqueologosDer;
  this->canibalesDer = canibalesDer;
  this->linternaDer = linternaDerecha;
}

void Estado::set_estado(int arqueologosIzq, int canibalesIzq, int arqueologosDer, int canibalesDer, bool linternaDerecha){
  this->arqueologosIzq = arqueologosIzq;
  this->canibalesIzq = canibalesIzq;
  this->arqueologosDer = arqueologosDer;
  this->canibalesDer = canibalesDer;
  this->linternaDer = linternaDerecha;
}