#include <iostream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atol */
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include <random>
#include "eligauss.h"
#include "cholesky.h"
#include "commons.h"
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

//Funciones Auxiliares

void start_timer() {
    start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
    chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
    return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}


bool pairCompare(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem) {
  return firstElem.second > secondElem.second;

}
void simDefPosGenerator(MatrixXd* matrizExperimental){
    (*matrizExperimental) = 0.5*((*matrizExperimental)*(matrizExperimental->inverse()));
    uint col_rows = matrizExperimental->rows();
    MatrixXd matrizAux = MatrixXd::Zero(col_rows, col_rows);
    matrizAux.setIdentity();
    (*matrizExperimental) = (*matrizExperimental) + (matrizExperimental->rows())*(matrizAux);
}

void generadorRandomTerminoInExp(VectorXd* terminoInExp)
{
    random_device rd;
    mt19937 gen(rd());
    int max = 100;
    uniform_int_distribution<> numerito(-50,max);
    int col_rows = terminoInExp->rows();
    for (int i = 0; i < col_rows; i++){
        (*terminoInExp)(i) = numerito(gen);
    }   
}

void generadorRandomMatrizExperimental(MatrixXd* matrizExperimental)
{
    random_device rd;
    mt19937 gen(rd());
    int max = 100;
    uniform_int_distribution<> numerito(-50,max);
    int col_rows = matrizExperimental->rows();
    for (int k1 = 0; k1 < col_rows; k1++) {
        for (int k2 = 0; k2 < col_rows; k2++) {
            (*matrizExperimental)(k1,k2) = numerito(gen);          
            if (k1 == k2) (*matrizExperimental)(k1,k2) = abs((*matrizExperimental)(k1,k2)) + max;
        }
    }
    
}

void generadorRandom(MatrixXd* matrizExperimental, VectorXd* terminoInExp){
    generadorRandomMatrizExperimental(matrizExperimental);
    generadorRandomTerminoInExp(terminoInExp);
}




map<double,double> parserDataWP(char* pathEntrada){
    map<int, pair<double,double> > equipoPuntos;
    map<double, double> resultadoFinal; //equipo, ganados/totales
    int cantEquipos;
    int cantPartidos;
    int fecha;
    int equipoLocal;
    int golesLocal;
    int equipoVisitante;
    int golesVisitante;
    pair<map<int,pair<double, double> >::iterator,bool> retInsertLocal;
    pair<map<int,pair<double, double> >::iterator,bool> retInsertVisitante;
    map<int,pair<double, double> >::iterator it;
    fstream archivoEntrada;
    archivoEntrada.open(pathEntrada);
    if (archivoEntrada.is_open()) {
        archivoEntrada >> cantEquipos;
        archivoEntrada >> cantPartidos;
        while (archivoEntrada.good()) {
            archivoEntrada >> fecha;
            archivoEntrada >> equipoLocal;
            archivoEntrada >> golesLocal;
            archivoEntrada >> equipoVisitante;
            archivoEntrada >> golesVisitante;          
            retInsertLocal = equipoPuntos.insert(make_pair(equipoLocal, make_pair(0, 1)));
            if (!retInsertLocal.second) {                //si ya existe

                ((retInsertLocal.first)->second).second++;
            }

            retInsertVisitante = equipoPuntos.insert(make_pair(equipoVisitante, make_pair(0, 1)));
            if (!retInsertVisitante.second) {                //si ya existe
                ((retInsertVisitante.first)->second).second++;
            }

            if (golesLocal > golesVisitante) {
                ((retInsertLocal.first)->second).first++;
            } 
            else {
                ((retInsertVisitante.first)->second).first++;
            }
        }
        archivoEntrada.close();

        for (it=equipoPuntos.begin(); it!=equipoPuntos.end(); ++it) {
            double percentage = (it->second).first / (it->second).second;
            resultadoFinal.insert(make_pair(it->first, percentage));
        }
    } 
    else {
        cout << "Error opening file";
    }
    return resultadoFinal;
}


//------------------------


int main(int argc, char *argv[]) {
    // ./tp1 pathEntrada pathSalida metodo experimento
    string sep = "\n----------------------------------------\n";
    MatrixXd matrizExperimental;
    VectorXd terminoInExp;
    int metodo = 0;
    uint experimentar;
    VectorXd terminoIndependiente;
    MatrixXd matrizPrincipal;
    map<int,int> equipoNumero;
    map<int,int> numeroEquipo;
    map<double,double> resultadoWP;
    
    if (argc == 4 || argc == 5) {
        char* pathEntrada = argv[1];
        char* pathSalida = argv[2];
        metodo = atoi(argv[3]);

        if (metodo == 2) {
            resultadoWP = parserDataWP(pathEntrada);
        } 
        else {
            parserDataCMM(pathEntrada, &matrizPrincipal, &terminoIndependiente, &equipoNumero, &numeroEquipo);
        }

        //SIN EXPERIMENTACION
        if (argc == 4) {
            switch(metodo) {
                case 0: {
                            VectorXd solu = gaussian_elimination(matrizPrincipal, terminoIndependiente);
                            vector<double> puntos = obtenerPuntos(equipoNumero, &solu);
                            exportarSolucion(pathSalida, puntos);
                            break;
                        }
                case 1: {
                            VectorXd solu = resolucionCholesky(matrizPrincipal, terminoIndependiente);
                            vector<double> puntos = obtenerPuntos(equipoNumero, &solu);
                            exportarSolucion(pathSalida, puntos);
                            break;
                        }
                case 2: {
                            vector<double> puntos = obtenerPuntos2(resultadoWP);
                            exportarSolucion(pathSalida, puntos);
                            break;
                        }
            }
        }
        //CON EXPERIMENTACION
        else if (argc == 5) {
            experimentar = atoi(argv[4]);
            if (metodo != 2) {
                parserDataCMM(pathEntrada, &matrizPrincipal, &terminoIndependiente, &equipoNumero, &numeroEquipo);       
            } 
            else {
            	resultadoWP = parserDataWP(pathEntrada);
            }
            
            if (experimentar == 1) {
                if (metodo == 0) {
                    int col_rows;
                    int nroMatriz = 0;
                    cout << "Metodo" << "," << "sizes" << "," << "nroMatriz" << "," << "tiempo" << endl;
                    for (int size = 1; size < 51; size++) {
                        col_rows = size*100;
                        matrizExperimental = MatrixXd::Zero(col_rows, col_rows);
                        terminoInExp = VectorXd::Zero(col_rows);
                        for (int matrizMismoSize = 0; matrizMismoSize < 10; ++matrizMismoSize) {                        
                            generadorRandom(&matrizExperimental, &terminoInExp);
                            for (int repeticion = 0; repeticion < 10; repeticion++) {
                                start_timer();
                                VectorXd solucion = gaussian_elimination(matrizExperimental, terminoInExp);
                                cout << "G" << "," << matrizExperimental.rows() << "," << nroMatriz << "," << stop_timer() << endl;
                            }
                            nroMatriz++;
                        }
                    }
                }
                else if (metodo == 1) {                 
                    int col_rows;
                    int nroMatriz = 0;
                    cout << "Metodo" << "," << "sizes" << "," << "nroMatriz" << "," << "tiempo" << endl;
                    for (int size = 1; size < 51; size++) {
                        col_rows = size*100;
                        matrizExperimental = MatrixXd::Zero(col_rows, col_rows);
                        terminoInExp = VectorXd::Zero(col_rows);
                        for (int matrizMismoSize = 0; matrizMismoSize < 10; ++matrizMismoSize) {                        
                            generadorRandom(&matrizExperimental, &terminoInExp);
                            simDefPosGenerator(&matrizExperimental);
                            for (int repeticion = 0; repeticion < 10; repeticion++) {
                                start_timer();
                                VectorXd solu = resolucionCholesky(matrizExperimental, terminoInExp);
                                cout << "C" << "," << matrizExperimental.rows() << "," << nroMatriz << "," << stop_timer() << endl;
                            }
                            nroMatriz++;
                        }
                    }
                }
            }
            else if (experimentar == 2) {
                int col_rows;
                int nroTermIndpte = 0;
                double tiempoResolverCholesky = 0;
                cout << "Metodo" << "," << "sizes" << "," << "nroTermIndpte" << "," << "tiempo" << endl;
                for (int size = 1; size < 51; size++) {
                    col_rows = size*100;
                    matrizExperimental = MatrixXd::Zero(col_rows, col_rows);
                    terminoInExp = VectorXd::Zero(col_rows);
                    generadorRandomMatrizExperimental(&matrizExperimental);
                    simDefPosGenerator(&matrizExperimental);
                    start_timer();
                    pair<MatrixXd, MatrixXd> LLt = dameLLt(matrizExperimental);
                    tiempoResolverCholesky = stop_timer();
                    for (int termIndpteMismoSize = 0; termIndpteMismoSize < 10; ++termIndpteMismoSize) {
                        generadorRandomTerminoInExp(&terminoInExp);
                        for (int repeticion = 0; repeticion < 10; repeticion++) {
                            start_timer();
                            VectorXd solucion = gaussian_elimination(matrizExperimental, terminoInExp);
                            cout << "G" << "," << matrizExperimental.rows() << "," << nroTermIndpte << "," << stop_timer() << endl;
                        }
                        for (int repeticion = 0; repeticion < 10; repeticion++) {
                            start_timer();
                            VectorXd x = resolucionCholeskyAux(LLt, terminoInExp);
                            tiempoResolverCholesky += stop_timer();
                            cout << "C" << "," << matrizExperimental.rows() << "," << nroTermIndpte << "," << tiempoResolverCholesky << endl;
                            tiempoResolverCholesky = 0;
                        }
                        nroTermIndpte++;
                    }
                }
            }
            else if (experimentar == 3){
                resultadoWP = parserDataWP(pathEntrada);
                vector<pair<int,double>> rankingWP;
                for (map<double,double>::iterator it=resultadoWP.begin(); it!=resultadoWP.end(); ++it) {
                    rankingWP.push_back(make_pair(it->first,it->second));
                }
                sort(rankingWP.begin(), rankingWP.end(), pairCompare);
                for (int i = 0; i < rankingWP.size(); ++i) {
                    cout << "(" << rankingWP[i].first << " , " << rankingWP[i].second << " )"<< endl;
                }
                parserDataCMM(pathEntrada, &matrizPrincipal, &terminoIndependiente, &equipoNumero, &numeroEquipo);
                VectorXd solu = gaussian_elimination(matrizPrincipal, terminoIndependiente);
                vector<pair<int,double>> rankingCMM;
                for (int i = 0; i < solu.rows(); ++i) {
                    int aux = (*numeroEquipo.find(i)).second;
                    rankingCMM.push_back(make_pair(aux,solu(i)));
                }
                sort(rankingCMM.begin(), rankingCMM.end(), pairCompare);
                cout << endl;
                for (int i = 0; i < rankingCMM.size(); ++i) {
                    cout << "(" << rankingCMM[i].first << " , " << rankingCMM[i].second << " )"<< endl;
                }
                int deltaSwaps = 0;
                for (int i = 0; i < rankingWP.size(); ++i)
                {
                    int equipo = rankingWP[i].first;
                    for (int j = 0; j < rankingWP.size(); ++j)
                    {
                        if (equipo == rankingCMM[j].first){
                            deltaSwaps += abs(i-j);
                        }
                    }
                }
                cout << endl << endl << rankingWP.size() << endl << deltaSwaps/rankingWP.size() << endl;
                int deltaSwaps2 = 0;
                for (int i = 0; i < 10; ++i)
                {
                    int equipo = rankingWP[i].first;
                    for (int j = 0; j < rankingWP.size(); ++j)
                    {
                        if (equipo == rankingCMM[j].first){
                            deltaSwaps2 += abs(i-j);
                        }
                    }
                }
                cout << endl << endl << 10 << endl << deltaSwaps2/10 << endl;
            }
        }
    }
    else {
        cout << "Modo de uso: ./tp1 \n Path con archivo de entrada \n Path con archivo de salida \n Metodo de rating \n [Experimentacion (1 = Cualitativo1, 2 = Cualitativo2)]" << endl;
        cout << "- Metodos de rating: 0 CMM-EG, 1 CMM-CL, 2 WP-EG donde:" << endl;
        cout << "   CMM-EG: Eliminacion Gaussiana" << endl;
        cout << "   CMM-CL: Cholesky" << endl;
        cout << "   WP: Winner Percentage" << endl;
        return -1;
    }
  return 0;
}

