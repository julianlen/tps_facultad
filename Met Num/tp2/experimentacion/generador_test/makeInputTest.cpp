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

using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;


int main(int argc, char *argv[]) {
    if (argc >= 6) {
        int reducidas = atoi(argv[1]);
        int cantPersonas = atoi(argv[2]);
        int imagenesXpersona = atoi(argv[3]);
        int compPpales = atoi(argv[4]);
        int cantPersonasReconocer = atoi(argv[5]);
        vector<int> personasAReconocer;
        for (int c = 1; c <= cantPersonasReconocer; c++){
            personasAReconocer.push_back(atoi(argv[5+c]));
        }

        int filas;
        int cols;

        if (reducidas == 0){
            filas = 23;
            cols = 28;
        } else {
            filas = 92;
            cols = 112;
        }

        cout << "../data/ImagenesCaras";
        if (reducidas == 0) cout << "Red"; //REDUCIDAS = 0 VS NORMALES = 1
        cout << "/ " << filas << " " << cols << " " << cantPersonas << " " << imagenesXpersona << " " << compPpales << endl;
        //IMAGENES PARAA ENTRENAR
        for (int i = 1; i <= cantPersonas; i++) {
            cout << "s" << i << "/ ";
            for(int j = 1; j <= imagenesXpersona; j++){
                cout << j;
                if (j != imagenesXpersona)     {
                    cout << " ";
                }
            }
            cout << endl;
        }
        //IMAGENES PARA RECONOCER
        for (int k = 0; k < personasAReconocer.size(); k++) {
            for(int im = imagenesXpersona + 1; im <= 10; im++){
            int aux = personasAReconocer[k];
            cout << "../data/ImagenesCaras";
            if (reducidas == 0) cout << "Red"; //REDUCIDAS = 0 VS NORMALES = 1
            cout << "/s" << aux << "/";
            cout << im << ".pgm " << aux << endl;
            }
        }


    }
    else {

        cout << "ENTRENAMIENTO" << endl;
        cout << "Reducidas = 0 o no = 1" << endl;
        cout << "Cantidad de Personas" << endl;
        cout << "Imagenes por persona" << endl;
        cout << "Comp ppales" << endl;
        cout << "RECONOCIMIENTO" << endl;
        cout << "Cant personas a reconocer" << endl;
        cout << "Cuales" << endl;


        return -1;
    }
    return 0;
}