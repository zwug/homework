#include <iostream>
#include <iomanip>
#include <math.h>

const double eps = 0.001;
const int N = 3;

bool isConvergent(double A[N][N]) {
	for (int i = 0; i < N; i++) {
		double rowSum = 0;
		double diagonalEl;

		for (int j = 0; j < N; j++) {
			if (i != j) {
				rowSum += A[i][j];
			}
			else {
				diagonalEl = A[i][j];
			}
		}

		if (rowSum > diagonalEl) {
			return false;
		}
	}
	return true;
}

void calculate(double A[N][N], double B[N], double *X)
{
	double* CurrentX = new double[N];
	double diff = 1000; // between two iterations

	while (diff > eps) {
		for (int i = 0; i < N; i++) {
			CurrentX[i] = B[i];
			for (int j = 0; j < N; j++) {
				if (i != j)
					CurrentX[i] -= A[i][j] * X[j];
			}
			CurrentX[i] /= A[i][i];
		}

		diff = fabs(X[0] - CurrentX[0]);
		for (int i = 0; i < N; i++) {
			if (fabs(X[i] - CurrentX[i]) > diff) {
				diff = fabs(X[i] - CurrentX[i]);
			}
			X[i] = CurrentX[i];
		}
	}

	delete[] CurrentX;
}

void print(double A[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << std::setw(10) << A[i][j];
		}
		std::cout << '\n';
	}
	std::cout << std::endl << std::endl;
}

void print(double A[N]) {
	for (int i = 0; i < N; i++) {
		std::cout << std::setw(10) << A[i];
		std::cout << '\n';
	}
	std::cout << std::endl << std::endl;
}

int main() {
	double A[N][N] = {
		{ 5.4, -2.3, 3.4 },
		{ 4.2, 1.7, -2.3 },
		{ 3.4, 2.4, 7.4 }
	};
	double B[N] = { -3.5, 2.7, 1.9 };
	double X[N] = { 0, 1, 0 }; // initial

	if (isConvergent(A)) {
		calculate(A, B, X);
		print(X);
	}
	else {
		std::cout << "The following matrix is not diagonally dominant." << std::endl;
		print(A);
		std::cout << "Subtracting row 0 from row 1" << std::endl;
		for (int i = 0; i < N; i++) {
			A[1][i] -= A[0][i];
		}
		B[1] -= B[0];

		print(A);
		calculate(A, B, X);
		print(X);
	}

	std::cin.ignore();
	return 0;
}
