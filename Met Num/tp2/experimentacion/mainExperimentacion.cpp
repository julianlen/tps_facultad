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
#include "../src/include/Eigen/Dense"
#include "../src/include/commons.h"


using namespace Eigen;
using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

void start_timer() {
    start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
    chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
    return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}


void exp1(inputFile i, bool b) {
	pair<MatrixXd, VectorXd> imAndMu = imagenesYesperanza(i);
    MatrixXd imagenes = MatrixXd(imAndMu.first);
    MatrixXd M = matrizCovarianza_XT_X(imAndMu); // PX X PX
    pair<MatrixXd, vector<double>> autos;
    if (b) {
        autos = entrenamiento(M, i.mainComponentsCount);
    }
    else
    {
        
        MatrixXd m = matrizCovarianza_X_XT(imAndMu); //IM X IM
        autos = entrenamientoEficiente(imAndMu.first.transpose(), m, i.mainComponentsCount);
    }
    MatrixXd coordenadas = tcMat(autos.first, imagenes);
}

int main(int argc, char *argv[]) {
    if (argc >= 4) {
        string pathEntrada_2 = argv[1];
        string pathSalida = argv[2];
        int experimento = atoi(argv[3]);

        if (experimento == 1) { //Experimento 1 (XXT vs XTX)
                cout << "RED/NORM" << "," << "Corrida" << "," << "XXT/XTX" << "," << "tiempo" << endl;
                string pathEntradaRed = "./inputs/fullEntrenamientoReducido.in";
                string pathEntrada = "./inputs/fullEntrenamientoNormal.in";
                inputFile ifile = read_inputfile(pathEntradaRed);
                inputFile ifile_normal = read_inputfile(pathEntrada);
                for (int i = 0; i < 20; ++i){
                    start_timer();
                    exp1(ifile, false); //XXT EFICIENTE
                    cout << "RED" << "," << i << "," << "XXT" << "," << stop_timer() << endl;
                }
                //cout << "paso 1" << endl;
                for (int i = 0; i < 20; ++i){
                    start_timer();
                    exp1(ifile, true); //XTX
                    cout << "RED" << "," << i << "," << "XTX" << "," << stop_timer() << endl;
                }
                //cout << "paso 2" << endl;
                for (int i = 0; i < 20; ++i){
                    start_timer();
                    exp1(ifile_normal, false); //XXT EFICIENTE
                    cout << "NORM" << "," << i << "," << "XXT" << "," << stop_timer() << endl;
                }
                //cout << "paso 3" << endl;
                for (int i = 0; i < 20; ++i){
                    start_timer();
                    exp1(ifile_normal, true); //XTX
                    cout << "NORM" << "," << i << "," << "XTX" << "," << stop_timer() << endl;
                }
                //cout << "paso 4" << endl;

        } else if (experimento == 2){ //Experimento 2 (Dado un entrenamiento -> Variar las componentes principales -> Calcular precision)
            
            cout << "CompPpal" << "," << "MetodoEleccion" << "," << "NroPersona" << "," <<  "VerdaderosP" << "," << "FalsosN" << "," << "FalsosP" << endl;
            pair<MatrixXd, vector<double>> autos;
            inputFile ifile = read_inputfile(pathEntrada_2);
            pair<MatrixXd, VectorXd> imAndMu = imagenesYesperanza(ifile);
            MatrixXd imagenes = MatrixXd(imAndMu.first);
            MatrixXd M = matrizCovarianza_XT_X(imAndMu);
            for (int compPpal = 1; compPpal <= 50; compPpal = compPpal+3) {

                autos = entrenamiento(M,compPpal);
                MatrixXd coordenadas = tcMat(autos.first, imagenes);
                map<int,vector<int>> metricas_v;
                map<int,vector<int>> metricas_knn;
                
                for (int i = 0; i < ifile.ntest.size(); ++i)
                {
                    VectorXd imagenParaComparar = matrixToVector(readPGM(ifile.ntest[i].first));
                    VectorXd vectorParaComparar = tc(autos.first, imagenParaComparar);
                    int test_knn = kVecinosMasCercanos(coordenadas, vectorParaComparar, 10, ifile.imagesPerPeopleCount);
                    int test_v = kVecinosMasCercanos(coordenadas, vectorParaComparar, 1, ifile.imagesPerPeopleCount);
                    int persona = ifile.ntest[i].second;
                    //KNN VECINOS
                    if (test_knn == persona) {
                        //cout << "BIEN!!!" << endl;//BIEN
                        vector<int> a { 1,0,0 };
                        pair<map<int,vector<int>>::iterator,bool> ret = metricas_knn.insert(pair<int,vector<int>>(persona, a));
                        if(ret.second==false){
                            ret.first->second[0]++;
                        }
                    } else {
                        //cout << "MAL!!!" << endl;
                        //falso NEGATIVO
                        vector<int> b { 0,1,0 };
                        pair<map<int,vector<int>>::iterator,bool> ret = metricas_knn.insert(pair<int,vector<int>>(persona, b));
                        if(ret.second==false){
                            ret.first->second[1]++;
                        }
                        //falso POSITIVO
                        vector<int> c { 0,0,1 };
                        ret = metricas_knn.insert(pair<int,vector<int>>(test_knn, c));
                        if(ret.second==false){
                            ret.first->second[2]++;
                        }
                    }

                    //VECINO MAS CERCANO
                    if (test_v == persona) {
                        //cout << "BIEN!!!" << endl;//BIEN
                        vector<int> d { 1,0,0 };
                        pair<map<int,vector<int>>::iterator,bool> ret = metricas_v.insert(pair<int,vector<int>>(persona, d));
                        if(ret.second==false){
                            ret.first->second[0]++;
                        }
                    } else {
                        //cout << "MAL!!!" << endl;
                        //falso NEGATIVO
                        vector<int> e { 0,1,0 };
                        pair<map<int,vector<int>>::iterator,bool> ret = metricas_v.insert(pair<int,vector<int>>(persona, e));
                        if(ret.second==false){
                            ret.first->second[1]++;
                        }
                        //falso POSITIVO
                        vector<int> f { 0,0,1 };
                        ret = metricas_v.insert(pair<int,vector<int>>(test_v, f));
                        if(ret.second==false){
                            ret.first->second[2]++;
                        }
                    }
                }
                for (map<int,vector<int>>::iterator it = metricas_knn.begin(); it != metricas_knn.end(); ++it) {
                    cout << compPpal << "," << "KNN" << "," << it->first << "," << it->second[0] << "," << it->second[1] << "," << it->second[2] << endl;
                    //"CompPpal" << "," << "MetodoEleccion" << "," << "NroPersona" << "," <<  "VerdaderosP" << "," << "FalsosN" << "," << "FalsosP"
                }
                for (map<int,vector<int>>::iterator it2 = metricas_v.begin(); it2 != metricas_v.end(); ++it2) {
                    cout << compPpal << "," << "V" << "," << it2->first << "," << it2->second[0] << "," << it2->second[1] << "," << it2->second[2] << endl;
                    //"CompPpal" << "," << "MetodoEleccion" << "," << "NroPersona" << "," <<  "VerdaderosP" << "," << "FalsosN" << "," << "FalsosP"
                }
            }
            writeFile(pathSalida, autos.second);
        } else if (experimento == 3) { 
	            cout << "cantKvecinos" << "," << "NroPersona" << "," <<  "VerdaderosP" << "," << "FalsosN" << "," << "FalsosP" << endl;
	            pair<MatrixXd, vector<double>> autos;
	            inputFile ifile = read_inputfile(pathEntrada_2);
	            pair<MatrixXd, VectorXd> imAndMu = imagenesYesperanza(ifile);
	            MatrixXd imagenes = MatrixXd(imAndMu.first);
                MatrixXd m = matrizCovarianza_X_XT(imAndMu);
        		autos = entrenamientoEficiente(imAndMu.first.transpose(), m, ifile.mainComponentsCount);
                MatrixXd coordenadas = tcMat(autos.first, imagenes);

                for (int k = 2; k <= 40; k++)
                {
	                map<int,vector<int>> metricas_knn;
	                
	                for (int i = 0; i < ifile.ntest.size(); ++i) {
	                    VectorXd imagenParaComparar = matrixToVector(readPGM(ifile.ntest[i].first));
	                    VectorXd vectorParaComparar = tc(autos.first, imagenParaComparar);
	                    int test_knn = kVecinosMasCercanos(coordenadas, vectorParaComparar, k, ifile.imagesPerPeopleCount);
	                    int persona = ifile.ntest[i].second;
	                    //KNN VECINOS
	                    if (test_knn == persona) {
	                        //cout << "BIEN!!!" << endl;//BIEN
	                        vector<int> a { 1,0,0 };
	                        pair<map<int,vector<int>>::iterator,bool> ret = metricas_knn.insert(pair<int,vector<int>>(persona, a));
	                        if(ret.second==false){
	                            ret.first->second[0]++;
	                        }
	                    } else {
	                        //cout << "MAL!!!" << endl;
	                        //falso NEGATIVO
	                        vector<int> b { 0,1,0 };
	                        pair<map<int,vector<int>>::iterator,bool> ret = metricas_knn.insert(pair<int,vector<int>>(persona, b));
	                        if(ret.second==false){
	                            ret.first->second[1]++;
	                        }
	                        //falso POSITIVO
	                        vector<int> c { 0,0,1 };
	                        ret = metricas_knn.insert(pair<int,vector<int>>(test_knn, c));
	                        if(ret.second==false){
	                            ret.first->second[2]++;
	                        }
	                    }
	                }
	                for (map<int,vector<int>>::iterator it = metricas_knn.begin(); it != metricas_knn.end(); ++it) {
	                    cout << k << "," << it->first << "," << it->second[0] << "," << it->second[1] << "," << it->second[2] << endl;
	                    //"k" << "," << "NroPersona" << "," <<  "VerdaderosP" << "," << "FalsosN" << "," << "FalsosP"
	                }
	            }
	            
            } else if (experimento == 4){ //Reconocer caras


            	pair<MatrixXd, vector<double>> autos;
	            inputFile ifile = read_inputfile(pathEntrada_2);
	            pair<MatrixXd, VectorXd> imAndMu = imagenesYesperanza(ifile);
	            MatrixXd imagenes = MatrixXd(imAndMu.first);
                MatrixXd m = matrizCovarianza_X_XT(imAndMu);
        		autos = entrenamientoEficiente(imAndMu.first.transpose(), m, ifile.mainComponentsCount);
                MatrixXd coordenadas = tcMat(autos.first, imagenes);

		cout << "PUTO EL QUE LEE!!!" << endl;

                VectorXd imagenParaComparar = matrixToVector(readPGM(argv[4]));
	            VectorXd vectorParaComparar = tc(autos.first, imagenParaComparar);

                if (reconocerUnaCara(coordenadas, vectorParaComparar)){
					cout << "Es el rostro de una persona" << endl;
                } else {
					cout << "NO es el rostro de una persona" << endl;
                }
           
            }
    } else {
            cerr << "Modo de uso: ./tp2 \n path con archivo de entrada \n path con archivo de salida \n nroExperimento \n Para el exp1 no es necesario path's" << endl;
            return -1;
    }
    return 0;
}
