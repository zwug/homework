#include <iostream>
#include <complex>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int COMPLEX_VALUES = 256;
const int DOUBLE_VALUES = 500;

complex<double> * h;
double * x;

void randInit(complex<double> *h, double *x) {
  for (int j = 0 ; j < COMPLEX_VALUES ; j++) {
    h[j] = complex<double>( 2 + (rand() % 10) / 10.0, rand() % 20);
  }

  for (int j = 0 ; j < DOUBLE_VALUES ; j++) {
    x[j] = (rand() % 1000) / 1000.0;
  }
}

complex<double> filter(complex<double> *h, double *x) {
  clock_t begin = clock();
  complex<double> sum = 0;

  for (int n = 0; n < DOUBLE_VALUES; n++) {
    for (int m = 0; m < COMPLEX_VALUES; m++) {
      sum += h[m] * x[n];
    }
  }

  clock_t end = clock();
  cout << "clock ticks passed = " << double(end - begin) << endl;
  return sum;
}

int main()
{
    h = new complex<double>[COMPLEX_VALUES]; // input data
    x = new double [DOUBLE_VALUES]; // input data

    randInit(h, x);
    cout << "Sum = " << filter(h, x) << endl;
    return 0;
}
