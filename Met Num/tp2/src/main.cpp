#include <iostream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atol */
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>
#include <random>
#include <vector>
#include "include/Eigen/Dense"
#include "include/commons.h"


using namespace Eigen;
using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

int main(int argc, char *argv[]) {
    
    switch(argc) {
        case 3:
        case 4: {
                string pathEntrada = argv[1];
                string pathSalida = argv[2];
                resolver(pathEntrada, pathSalida);                
                break;
            }
        default: {
                cerr << "Modo de uso: ./tp2 \n path con archivo de entrada \n path con archivo de salida" << endl;
                return -1;
            }
    }

    return 0;
}