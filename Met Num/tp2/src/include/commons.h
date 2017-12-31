#include "Eigen/Dense"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "pgmLibrary.h"
#include <map>


using namespace Eigen;
using namespace std;

#define EPS 0.00000001

struct inputFile {
    vector<vector<string> > imagesPaths;
    int pxRows;
    int pxCols;
    int peopleCount;
    int imagesPerPeopleCount;
    int mainComponentsCount;
    vector<pair<string, int> > ntest;
};

void resolver(string pathEntrada, string pathSalida);
pair<double, VectorXd> metodoPotencia(MatrixXd B, VectorXd x);
MatrixXd deflacion(MatrixXd B, pair<double, VectorXd> autos);
pair<MatrixXd, vector<double>> entrenamiento(MatrixXd M, int cantAutovectores);
pair<MatrixXd, vector<double>> entrenamientoEficiente(MatrixXd Xt, MatrixXd m, int cantAutovectores);
MatrixXd tcMat(MatrixXd autovectores, MatrixXd imagenes);
inputFile read_inputfile(string filePath);
pair<MatrixXd, VectorXd> imagenesYesperanza(inputFile ifile);
MatrixXd matrizCovarianza_XT_X(pair<MatrixXd, VectorXd> xAndMu);
MatrixXd matrizCovarianza_X_XT(pair<MatrixXd, VectorXd> xAndMu);
VectorXd tc(MatrixXd autovectores, VectorXd imagen);
VectorXd matrixToVector(MatrixXd mat);
bool pairCompare(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem);
int kVecinosMasCercanos(MatrixXd matrizTC, VectorXd imagenuevaTC, uint k, int imagenesPorPersona);
void writeFile(string path, vector<double> autovalores);
bool reconocerUnaCara(MatrixXd matrizCoordenadas, VectorXd imagenARecnocer);
MatrixXd dameCentroDeMasa(MatrixXd matrizTC, int imagenXpers, int cantPersonas, int cantCoordenadas);
int dameCentroMasCercano(VectorXd vectorNuevo, MatrixXd matrizMasas);