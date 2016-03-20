#include <iostream>
#include <iomanip>

const int N = 3;

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
        {5.4, -2.3, 3.4, -3.5},
        {4.2, 1.7, -2.3, 2.7},
        {3.4, 2.4, 7.4, 1.9}
    };

    double X[N];

    for (int z = 0; z < N; z++) {
        X[z] = A[z][N];
    }

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
    
    std::cout << "X =\n";

    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
    }

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
    return 0;
}
