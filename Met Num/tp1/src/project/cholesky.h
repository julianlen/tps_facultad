#include "commons.h"

using namespace Eigen;
using namespace std;

MatrixXd factorizacionCholesky(MatrixXd A);
VectorXd resolucionCholeskyAux(pair<MatrixXd, MatrixXd> inversaTranspuesta, VectorXd b);
pair<MatrixXd, MatrixXd> dameLLt(MatrixXd A);

VectorXd resolucionCholesky(MatrixXd A, VectorXd b);