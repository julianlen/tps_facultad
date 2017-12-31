#include "Eigen/Dense"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace Eigen;
using namespace std;

VectorXd backward_substitution(MatrixXd A, VectorXd b);
VectorXd forward_substitution(MatrixXd A, VectorXd b);
void parserDataCMM(char* pathEntrada, MatrixXd* matrizPrincipal, VectorXd* terminoIndependiente, map<int,int>* equipoNumero, map<int,int>* numeroEquipo);
void exportarSolucion(char* pathSalida, vector<double> puntos);
vector<double> obtenerPuntos(map<int, int> equipoNumero, VectorXd* solu);
vector<double> obtenerPuntos2(map<double, double> resultadoWP);