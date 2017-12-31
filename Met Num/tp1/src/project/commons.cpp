#include "commons.h"

VectorXd backward_substitution(MatrixXd A, VectorXd b) {
    int n = b.size();
    VectorXd y = VectorXd::Zero(n);

    if (A.rows() != A.cols() || A.rows() != n) {
    	cout << "La matriz debe ser cuadrada" << endl;
        return y; //Las dimensiones no concuerdan
    }
	for (int i = n - 1; i >= 0; i--) {
        y(i) = b(i);
        for (int j = n - 1; j >= i + 1; j--) {
            y(i) = y(i) - (A(i,j) * y(j));
        }
        y(i) = y(i) / A(i,i);
    }
    return y;
}


VectorXd forward_substitution(MatrixXd A, VectorXd b) {
    int n = b.size();
    VectorXd y = VectorXd::Zero(n);
    if (A.rows() != A.cols() || A.rows() != n) {
    	cout << "La matriz debe ser cuadrada" << endl;
        return y; //Las dimensiones no concuerdan
    }
    for (int i = 0; i < n; i++) {
        y(i) = b(i);
        for (int j = 0; j < i ; j++) {
            y(i) = y(i) - (A(i,j) * y(j));
        }
        y(i) = y(i) / A(i,i);
    }
    return y;
}

void parserDataCMM(char* pathEntrada, MatrixXd* matrizPrincipal, VectorXd* terminoIndependiente, map<int,int>* equipoNumero, map<int,int>* numeroEquipo) {
    int cantEquipos;
    int cantPartidos;
    int fecha;
    int equipoLocal;
    int golesLocal;
    int equipoVisitante;
    int golesVisitante;
    int numeroAuxiliar = 0;
    pair<map<int,int>::iterator,bool> retLocal;
    pair<map<int,int>::iterator,bool> retVisit;
    string line;

    ifstream archivoEntrada(pathEntrada);
    if (getline(archivoEntrada, line)) {
        istringstream iss(line);

        iss >> cantEquipos >> cantPartidos;

        *matrizPrincipal = MatrixXd::Zero(cantEquipos, cantEquipos);
        *terminoIndependiente = VectorXd::Zero(cantEquipos);

        for (int i = 0; i < cantEquipos; i++) {
            (*matrizPrincipal)(i,i) = 2;
        }

        while (getline(archivoEntrada, line)) {
            istringstream iss(line);
            iss >> fecha >> equipoLocal >> golesLocal >> equipoVisitante >> golesVisitante;

            retLocal = equipoNumero->insert(pair<int,int>(equipoLocal, numeroAuxiliar));
            if (retLocal.second) {
                numeroEquipo->insert(pair<int,int>(numeroAuxiliar, equipoLocal));
                numeroAuxiliar++;
            }

            retVisit = equipoNumero->insert(pair<int,int>(equipoVisitante, numeroAuxiliar));
            if (retVisit.second) {
                numeroEquipo->insert(pair<int,int>(numeroAuxiliar, equipoVisitante));
                numeroAuxiliar++;   
            }

            int equipoLocalDicc = retLocal.first->second;
            int equipoVisitDicc = retVisit.first->second;

            (*matrizPrincipal)(equipoLocalDicc, equipoVisitDicc)--;
            (*matrizPrincipal)(equipoVisitDicc, equipoLocalDicc)--;
            (*matrizPrincipal)(equipoVisitDicc, equipoVisitDicc)++;
            (*matrizPrincipal)(equipoLocalDicc, equipoLocalDicc)++;

            if (golesLocal > golesVisitante) {
                (*terminoIndependiente)(equipoLocalDicc)++;
                (*terminoIndependiente)(equipoVisitDicc)--;
            } 
            else {
                (*terminoIndependiente)(equipoVisitDicc)++;
                (*terminoIndependiente)(equipoLocalDicc)--;
            }

            cout << endl;
        }

        archivoEntrada.close();
        for (int i = 0; i < cantEquipos; i++) {
            (*terminoIndependiente)(i) = (*terminoIndependiente)(i)/2 + 1;
        }
    }
}

vector<double> obtenerPuntos(map<int, int> equipoNumero, VectorXd* solu) {
    vector<double> v;
    for (map<int,int>::iterator it = equipoNumero.begin(); it != equipoNumero.end(); ++it) {
        v.push_back((*solu)(it->second));
    }
    return v;
}

vector<double> obtenerPuntos2(map<double, double> resultadoWP) {
    vector<double> v;
    for (map<double,double>::iterator it = resultadoWP.begin(); it != resultadoWP.end(); ++it) {
        v.push_back(it->second);
    }
    return v;
}

void exportarSolucion(char* pathSalida, vector<double> puntos) {
    ofstream fileRespuesta;
    fileRespuesta.open(pathSalida);
    for (std::vector<double>::iterator it = puntos.begin() ; it != puntos.end(); ++it) {
        fileRespuesta.precision(6);
        fileRespuesta << fixed;
        fileRespuesta << *it << endl;
    }
    fileRespuesta.close();
}