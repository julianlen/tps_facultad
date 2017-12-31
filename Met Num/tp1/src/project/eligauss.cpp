#include "eligauss.h"

VectorXd gaussian_elimination(MatrixXd A, VectorXd b) {
	VectorXd ret = VectorXd::Zero(b.size());

	int n = A.rows();
	int m = A.cols();

	double eps = 1^-16;
	if (n != m){
		cout << "La matriz debe ser cuadrada" << endl;
		return ret;
	}

	double v = 0;
	for	(int k = 0; k < n - 1; k++) {
		bool valorNoNulo = abs(A(k, k)) > eps;
		if (!valorNoNulo) {
			cout << "Uno de los pivotes es cero. Realizar Gauss con pivoteo parcial" << endl;
			
			int maxIndex = k+1;
			double max = A(maxIndex, k);
			for (int i = k+2; i < n; ++i)
			{
				if (A(i, k) > max)
				{
					maxIndex = i;
					max = A(maxIndex, k);
				}
			}
			if (abs(max) > eps) {

				A.row(k).swap(A.row(maxIndex));
				b.row(k).swap(b.row(maxIndex));
				valorNoNulo = true;
			}
		}

		if (valorNoNulo) {
			for (int i = k+1; i < n; i++) {
				v = A(i, k) / A(k, k);
				A(i, k) = 0;
				for (int j = k+1; j < n; j++) {
					A(i, j) = A(i, j) - v * A(k, j);
				}
				b(i) = b(i) - v * b(k);
			}
		}
	}

	ret = backward_substitution(A, b);
	return ret;
}
