#include <vector>

class Estado{
    public:
        int arqueologosIzq;
        int canibalesIzq;
        int arqueologosDer;
        int canibalesDer;
        bool linternaDer;
        void set_estado(int arqueologosIzq, int canibalesIzq, int arqueologosDer, int canibalesDer, bool linternaDerecha);
        Estado();
        Estado(int arqueologosIzq, int canibalesIzq, int arqueologosDer, int canibalesDer, bool linternaDerecha);


    private:
};