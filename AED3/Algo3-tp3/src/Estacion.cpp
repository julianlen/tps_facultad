#include "Estacion.h"

Estacion::Estacion(){
  this->esGimnasio = true;
  this->potas = 0;
  this->id = 0;
}

Estacion::Estacion(bool EsGimnasio, int nroPotas, int Id){
  this->esGimnasio = EsGimnasio;
  this->potas = nroPotas;
  this->id = Id;
}

Estacion::Estacion(const Estacion &copia){
  this->esGimnasio = copia.esGimnasio;
  this->potas = copia.potas;
  this->id = copia.id;
}

void Estacion::set_estacion(bool EsGimnasio, int nroPotas, int Id){
  this->esGimnasio = EsGimnasio;
  this->potas = nroPotas;
  this->id = Id;
}

