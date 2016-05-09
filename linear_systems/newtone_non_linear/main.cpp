#include <iostream>

const int N = 2;
const double EPS = 0.000001;

double F(double x, double y) {
	return sin(x + y) - 1.2 * x - 0.2;
}

double G(double x, double y) {
	return x*x + y*y - 1;
}

double Fx(double x, double y) {
	return cos(x + y) - 1.2;
}

double Fy(double x, double y) {
	return cos(x + y);
}

double Gx(double x, double y) {
	return 2 * x;
}

double Gy(double x, double y) {
	return 2 * y;
}

double *systemResults(double x, double y) {
	static double *result;
	result = new double[N];
	result[0] = F(x, y);
	result[1] = G(x, y);
	return result;
}

double **Yrevert(double x, double y) {
	static double **Y;
	double detY = Fx(x, y) * Gy(x, y) - Fy(x, y) - Gx(x, y);
	Y = new double*[N];
	Y[0] = new double[N];
	Y[1] = new double[N];
	Y[0][0] = Gy(x, y) / detY;
	Y[0][1] = -1 * Fy(x, y) / detY;
	Y[1][0] = -1 * Gx(x, y) / detY;
	Y[1][1] = Fx(x, y) / detY;
	return Y;
}


int main() {
	double next[N];
	// initial values
	double curr[N] = { 0, 0 };
	int iter = 0;

	for (; abs(next[0] - curr[0]) > EPS; iter++) {
		double subtrahend[N] = { 0, 0 };
		double **Ymatrix;
		Ymatrix = Yrevert(curr[0], curr[1]);
		double Fmatrix[N] = {F(curr[0], curr[1]), G(curr[0], curr[1])};

		

		for (int i = 0; i < N; i++) {
			if (iter != 0) {
				curr[i] = next[i];
			}
			for (int  j = 0; j < N; j++) {
				subtrahend[i] += Ymatrix[i][j] * Fmatrix[j];
			}
			next[i] = curr[i] - subtrahend[i];
		}


		delete [] Ymatrix;
	}

	std::cout << "iterations done: " << iter << std::endl;
	std::cout << "x = " << curr[0] << std::endl;
	std::cout << "y = " << curr[1] << std::endl;

	std::cout << "************************* TESTS ******************************" << std::endl;
	std::cout << "F(x, y) = " << F(curr[0], curr[1]) <<std::endl;
	std::cout << "G(x, y) = " << G(curr[0], curr[1]) << std::endl;
	std::cout << "**************************************************************" << std::endl;

	std::cin.ignore();
	return 0;
}
