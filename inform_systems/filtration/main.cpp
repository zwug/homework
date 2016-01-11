#include <iostream>
#include <complex>
#include <vector>
#include <stdlib.h>
#include <omp.h>
#include <ctime>

using namespace std;

const int X_COUNT = 500;
const int H_COUNT = 16;

const int X_SIZE = 1000;
const int H_SIZE = 256;

void randInitMulti(vector<complex<double>> *h, vector<complex<double>> *x) {
	double start_time = omp_get_wtime();
	#pragma omp parallel for shared(h)
	for (int j = 0; j < H_COUNT; j++) {
		for (int i = 0; i < H_SIZE; i++) {
			h[j].push_back(complex<double>((rand() % 50) / 100.0 - 1, (rand() % 50) / 100.0 - 1));
		}
	}
	#pragma omp parallel for shared(x)
	for (int j = 0; j < X_COUNT; j++) {
		for (int i = 0; i < X_SIZE; i++) {
			x[j].push_back(complex<double>((rand() % 50) / 100.0 - 1, (rand() % 50) / 100.0 - 1));
		}
	}

	double time = omp_get_wtime() - start_time;
	cout << "INITIALIZTION with 4 threads" << endl;
	cout << "time passed with 4 threads= " << time << endl;
}

void randInitSingle(vector<complex<double>> *h, vector<complex<double>> *x) {
	double start_time = omp_get_wtime();
	#pragma omp parallel for
	for (int j = 0; j < H_COUNT; j++) {
		for (int i = 0; i < H_SIZE; i++) {
			h[j].push_back(complex<double>((rand() % 50) / 100.0 - 1, (rand() % 50) / 100.0 - 1));
		}
	}
	#pragma omp parallel for
	for (int j = 0; j < X_COUNT; j++) {
		for (int i = 0; i < X_SIZE; i++) {
			x[j].push_back(complex<double>((rand() % 50) / 100.0 - 1, (rand() % 50) / 100.0 - 1));
		}
	}
	double time = omp_get_wtime() - start_time;
	cout << "INITIALIZTION with single thread" << endl;
	cout << "time passed = " << time << endl;
}

complex<double> *filter(vector<complex<double>> *h, vector<complex<double>> *x, complex<double> y[]) {
	double start_time = omp_get_wtime();
	#pragma omp parallel for shared(y)
	for (int n = 0; n < H_COUNT; n++) {
		y[n] = 0;
		for (int m = 0; m < H_SIZE; m++) {
			y[n] += h[n][m] * x[n][m];
		}
	}

	double time = omp_get_wtime() - start_time;

	cout << "time passed with 4 threads= " << time << endl;
	return y;
}

complex<double> *filterSingle(vector<complex<double>> *h, vector<complex<double>> *x, complex<double> y[]) {
	double start_time = omp_get_wtime();

	for (int n = 0; n < H_COUNT; n++) {
		y[n] = 0;
		for (int m = 0; m < H_SIZE; m++) {
			y[n] += h[n][m] * x[n][m];
		}
	}

	double time = omp_get_wtime() - start_time;

	cout << "time passed single threaded= " << time << endl;
	return y;
}

int main()
{
	vector<complex<double>> h[H_COUNT];
	vector<complex<double>> x[X_COUNT];

	randInitMulti(h, x);
	randInitSingle(h, x);
	cout << "********CALCULATING***********" << endl;
	complex<double> *result = new complex<double>[H_COUNT];
	result = filterSingle(h, x, result);
	result = filter(h, x, result);
	for (int i = 0; i < H_COUNT; i++) {
		cout << "y[" << i << "] = " << result[i] << endl;
	}
	cin.get();
	return 0;
}
