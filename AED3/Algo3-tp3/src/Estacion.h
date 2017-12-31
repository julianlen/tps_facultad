#include <vector>

#ifndef ESTACIONES_CLASS
#define ESTACIONES_CLASS

class Estacion{
    public:
        bool esGimnasio;
        int potas;
        int id;
        void set_estacion(bool EsGimnasio, int nroPotas, int Id);
        Estacion();
        Estacion(bool EsGimnasio, int nroPotas, int Id);
        Estacion(const Estacion &copia);


    private:
};

#endif