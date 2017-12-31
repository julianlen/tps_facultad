#include "cholesky.h"
#include <math.h>

/*
factor A as A = LLT
• solve L (LT x) = b 
	– forward substitution Ly = b 
	– back substitution LT x = y
*/

MatrixXd factorizacionCholesky(MatrixXd A) {
	int n = A.rows();
	MatrixXd matrizCholesky = MatrixXd::Zero(n, n);
	int m = A.cols();
	double eps = 1^-16;
	if (n != m){
		printf("La matriz debe ser cuadrada");
		return matrizCholesky;
	}
	double sumatoria = 0;
	matrizCholesky(0,0) = sqrt(A(0,0));
	for (int i = 1; i <= n - 1; ++i) {
		matrizCholesky(i,0) = A(i,0) / matrizCholesky(0,0);
	}
	for (int i = 1; i <= n-1; ++i) {
		for (int k = 0; k < i; ++k)	{
			sumatoria += matrizCholesky(i,k) * matrizCholesky(i,k);
		}
		matrizCholesky(i,i) = sqrt(A(i,i) - sumatoria);
		for (int j = i+1; j < n; ++j) {
			sumatoria = 0;
			for (int k = 0; k < i; ++k)	{
				sumatoria += matrizCholesky(j,k) * matrizCholesky(i,k);
			}
			matrizCholesky(j,i) = (A(j,i) - sumatoria) / matrizCholesky(i,i);
		}
	}
	sumatoria = 0;
	for (int k = 0; k < n-1; k++) {	
		sumatoria += (matrizCholesky(n-1,k) * matrizCholesky(n-1,k));
	}
	matrizCholesky(n-1,n-1) = sqrt(A(n-1,n-1) - sumatoria);
	return matrizCholesky;
}

VectorXd resolucionCholeskyAux(pair<MatrixXd, MatrixXd> LLt, VectorXd b) {
	MatrixXd L = LLt.first;
	MatrixXd Lt = LLt.second;

    VectorXd y = forward_substitution(L, b);
	VectorXd x = backward_substitution(Lt, y);
	return x;
}

pair<MatrixXd, MatrixXd> dameLLt(MatrixXd A) {
	MatrixXd L = factorizacionCholesky(A);
	MatrixXd Lt = L.transpose();
    return make_pair(L, Lt);
}


VectorXd resolucionCholesky(MatrixXd A, VectorXd b) {
    pair<MatrixXd, MatrixXd> LLt = dameLLt(A);
    return resolucionCholeskyAux(LLt, b);
}