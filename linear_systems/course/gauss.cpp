#include <iostream>
#include <iomanip>
#include <time.h>

const int N = 4;

void printMatrix(double A[N][N + 1]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N + 1; j++) {
			std::cout << std::setw(10) << A[i][j];
		}
		std::cout << '\n';
	}
	std::cout << std::endl << std::endl;
}

int main(int argc, const char * argv[]) {
	double A[N][N + 1] = {
		{ 6, 9, 7, 3, 97 },
		{ 7, 4, 7, 2, 91 },
		{ 4, 4, 4, 8, 76 },
		{ 5, 3, 5, 3, 70 }
	};

	double X[N];

	for (int z = 0; z < N; z++) {
		X[z] = A[z][N];
	}

	clock_t cl = clock();

	for (int k = 1; k < N; k++) {
		for (int j = k; j < N; j++) {
			double m = A[j][k - 1] / A[k - 1][k - 1];
			for (int i = 0; i <= N; i++) {
				A[j][i] -= m * A[k - 1][i];
			}
			X[j] -= m * X[k - 1];
		}
	}

	std::cout << "Matrix A to triangle view =\n";
	printMatrix(A);

	for (int i = N - 1; i >= 0; i--) {
		for (int j = i + 1; j < N; j++) {
			X[i] -= A[i][j] * X[j];
		}
		X[i] /= A[i][i];
	}

	double resultTime;
	if (cl != (clock_t)-1)
		resultTime = (double)cl / (double)CLOCKS_PER_SEC;

	std::cout << "time passed = " << resultTime << " seconds\n";
	std::cout << "X =\n";

	for (int i = 0; i < N; i++) {
		std::cout << X[i] << '\n';
	}

	std::cout << "\n********************* TESTS **********************\n";

	for (int i = 0; i < N; i++) {
		double rowSum = 0;
		for (int j = 0; j < N; j++) {
			rowSum += A[i][j] * X[j];
		}
		std::cout << "Sum of the row number " << i << " = " << rowSum << std::endl;
		std::cout << "Should be around " << A[i][N] << std::endl << std::endl;
	}
	std::cin.ignore();
	return 0;
}
