#include <iostream>
#include <iomanip>
#include <time.h>

const int N = 4;
const int GRIDCOLS = 10;
const double EPS = 0.000001;

const double A[N][N + 1] = {
    { 6, 9, 7, 3, 97 },
    { 7, 4, 7, 2, 91 },
    { 4, 4, 4, 8, 76 },
    { 5, 3, 5, 3, 70 }
};

// correct xs are 7 2 4 3
// there are some issues with initaial matrix maybe it should contain some subtractions
// the matrix below works perfectly

//const double A[N][N + 1] = {
//    { 1, 0, 0, 0, 7 },
//    { 0, 1, 0, 0, 2},
//    { 0, 0, 1, 0, 4 },
//    { 0, 0, 0, 1, 3 }
//};

void printMatrix(double A[N][N + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            std::cout << std::setw(10) << A[i][j];
        }
        std::cout << '\n';
    }
    std::cout << std::endl << std::endl;
}

double rowSum(int rowIndex, double verticles[N]) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += A[rowIndex][i] * verticles[i];
    }
    return sum - A[rowIndex][N];
}

bool checkVerticles(double verticlesLeft[N], double verticlesRight[N]) {
    bool foundArea = true;
    for (int i = 0; i < N; i++) {
        if (rowSum(i, verticlesLeft) * rowSum(i, verticlesRight) > 0) {
            foundArea = false;
        }
    }
    return foundArea;
}

int main(int argc, const char * argv[]) {
    // initial
    //double x1[2] = { 3.15, 8.21 };
    //double x2[2] = { 3.22, 6.73 };
    //double x3[2] = { 3.45, 6.27 };
    //double x4[2] = { 4.19, 6.74 };

    clock_t cl = clock();
    // -----------------------------------
    
    double verticlesLeft[N] = {
        6, 1, 3, 2
    };
    double verticlesRight[N] = {
        8, 3, 5, 5
    };
    
    double x1Pos = verticlesLeft[0];
    
    while (verticlesRight[0] - verticlesLeft[0] > EPS && x1Pos < verticlesRight[0]) {
        double x1PosNext = x1Pos + (verticlesRight[0] - verticlesLeft[0]) / GRIDCOLS;
        double x2Pos = verticlesLeft[1];
        
        while (verticlesRight[1] - verticlesLeft[1] > EPS && x2Pos < verticlesRight[1]) {
            double x2PosNext = x2Pos + (verticlesRight[1] - verticlesLeft[1]) / GRIDCOLS;
            double x3Pos = verticlesLeft[2];
            
            while (verticlesRight[2] - verticlesLeft[2] > EPS && x3Pos < verticlesRight[2]) {
                double x3PosNext = x3Pos + (verticlesRight[2] - verticlesLeft[2]) / GRIDCOLS;
                double x4Pos = verticlesLeft[3];
                
                while (verticlesRight[3] - verticlesLeft[3] > EPS && x4Pos < verticlesRight[3]) {
                    double x4PosNext = x4Pos + (verticlesRight[3] - verticlesLeft[3]) / GRIDCOLS;
                    
                    double verticlesLeftToCheck[N] = {x1Pos, x2Pos, x3Pos, x4Pos};
                    double verticlesRightToCheck[N] = {x1PosNext, x2PosNext, x3PosNext, x4PosNext};
                    
                    if (checkVerticles(verticlesLeftToCheck, verticlesRightToCheck)) {
                        std::cout << "Border values before selecting" << std::endl;

                        std::cout << verticlesLeft[0] << "   " << verticlesRight[0] << std::endl;
                        std::cout << verticlesLeft[1] << "   " << verticlesRight[1] << std::endl;
                        std::cout << verticlesLeft[2] << "   " << verticlesRight[2] << std::endl;
                        std::cout << verticlesLeft[3] << "   " << verticlesRight[3] << std::endl;


                        verticlesLeft[0] = x1Pos;
                        verticlesRight[0] = x1PosNext;
                        
                        verticlesLeft[1] = x2Pos;
                        verticlesRight[1] = x2PosNext;
                        
                        verticlesLeft[2] = x3Pos;
                        verticlesRight[2] = x3PosNext;
                        
                        verticlesLeft[3] = x4Pos;
                        verticlesRight[3] = x4PosNext;
                        
                        std::cout << std::endl;
                        std::cout << "Border values after selecting" << std::endl;
                        std::cout << verticlesLeft[0] << "   " << verticlesRight[0] << std::endl;
                        std::cout << verticlesLeft[1] << "   " << verticlesRight[1] << std::endl;
                        std::cout << verticlesLeft[2] << "   " << verticlesRight[2] << std::endl;
                        std::cout << verticlesLeft[3] << "   " << verticlesRight[3] << std::endl;
                        std::cout << "================================" << std::endl;

                        
                        x3PosNext = x3Pos + (x3PosNext - x3Pos) / GRIDCOLS;
                        x2PosNext = x2Pos + (x2PosNext - x2Pos) / GRIDCOLS;
                        x1PosNext = x1Pos + (x1PosNext - x1Pos) / GRIDCOLS;
                        break;
                    }
                    else {
                        x4Pos = x4PosNext;
                    }
                }
                x3Pos = x3PosNext;
            }
            x2Pos = x2PosNext;
        }
        x1Pos = x1PosNext;
    }
    
    // -----------------------------------
    double resultTime;
    if (cl != (clock_t)-1)
        resultTime = (double)cl / (double)CLOCKS_PER_SEC;
    
    std::cout << "time passed = " << resultTime << " seconds\n";
    std::cout << "X =\n";
    
    for (int i = 0; i < N; i++) {
        std::cout << verticlesLeft[i] << '\n';
    }
    std::cout << "\n********************* TESTS **********************\n";
    
    double xTestLeft[N] = {6.9, 1.9, 3.9, 2.9};
    double xTestRight[N] = {7.1, 2.1, 4.1, 3.1};
    
    std::cout << "should be TRUE - " << checkVerticles(xTestLeft, xTestRight) << std::endl;
    
    for (int i = 0; i < N; i++) {
        std::cout << rowSum(i, xTestLeft) << " should be less than 0" << std::endl;
        std::cout << rowSum(i, xTestRight) << " should be greater than 0" << std::endl;
        std::cout << std::endl;
    }
    
    double xTestLeftFalse[N] = {6, 1.75, 5, 3.05};
    double xTestRightFalse[N] = {6.05, 1.8, 5.05, 3.125};
    
    std::cout << "should be False - " << checkVerticles(xTestLeftFalse, xTestRightFalse) << std::endl;
    
    for (int i = 0; i < N; i++) {
        std::cout << rowSum(i, xTestLeftFalse) << " should be less than 0" << std::endl;
        std::cout << rowSum(i, xTestRightFalse) << " should be greater than 0" << std::endl;
        std::cout << std::endl;
    }
    
    
    for (int i = 0; i < N; i++) {
        double rowSum = 0;
        for (int j = 0; j < N; j++) {
            rowSum += A[i][j] * verticlesLeft[j];
        }
        std::cout << "Sum of the row number " << i << " = " << rowSum << std::endl;
        std::cout << "Should be around " << A[i][N] << std::endl << std::endl;
    }
    std::cin.ignore();
    return 0;
}
