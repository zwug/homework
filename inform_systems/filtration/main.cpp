#include <iostream>
#include <complex>
#include <vector>
#include <stdlib.h>
#include <omp.h>
#include <ctime>

using namespace std;

const int X_COUNT = 500;
const int H_COUNT = 16;

const int X_SIZE = 10000;
const int H_SIZE = 256;

void randInit(vector<complex<double>> *h, vector<complex<double>> *x) {
	for (int j = 0; j < H_COUNT; j++) {
		for (int i = 0; i < H_SIZE; i++) {
			h[j].push_back(complex<double>(2 + (rand() % 10) / 10.0, rand() % 20));
		}
	}

	for (int j = 0; j < X_COUNT; j++) {
		for (int i = 0; i < X_SIZE; i++) {
			x[j].push_back(complex<double>(2 + (rand() % 10) / 10.0, rand() % 20));
		}
	}
}

complex<double> filter(vector<complex<double>> *h, vector<complex<double>> *x) {
	complex<double> sum = 0;

	double start_time = omp_get_wtime();
	#pragma omp parallel for

	for (int n = 0; n < H_COUNT; n++) {
		for (int m = 0; m < H_SIZE; m++) {
			sum += h[n][m] * x[n][m];
		}
	}

	double time = omp_get_wtime() - start_time;

	cout << "time passed = " << time << endl;
	return sum;
}

int main()
{
	vector<complex<double>> h[H_COUNT];
	vector<complex<double>> x[X_COUNT];

	randInit(h, x);
	cout << "Sum = " << filter(h, x) << endl;
	cin.get();
	return 0;
}
