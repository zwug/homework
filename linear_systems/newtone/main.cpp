#include <iostream>

const double PI = 3.14;
const double EPS = 0.001;

double buckingham(double r, double l, double p, double t, double v, double Q, double x) {
	double firstItem = (PI * r * r * x) / (8.0 * l * p * v);
	double Multiplier = (2.0 * t * l) / (r * x);
	return firstItem * (1.0 - (4.0 / 3.0) * Multiplier + (1.0 / 3.0) * std::pow(Multiplier, 4)) - Q;
}

double buckinghamDeriv(double r, double l, double p, double t, double v, double x) {
	return (PI * (std::pow(x * r, 4) - std::pow(2.0 * t * l, 4))) / (8 * l * p * r*r * v * std::pow(x, 4));
}

void calculateX(int initialX) {
	double Q = 200;

	double r = 0.1;
	double l = 1;
	double p = 870;
	double t = 20;
	double v = 40;

	double x1 = initialX - buckingham(r, l, p, t, v, Q, initialX) / buckinghamDeriv(r, l, p, t, v, initialX);
	double x0 = initialX;

	while (abs(x0 - x1) > EPS) {
		x0 = x1;
		x1 = x1 - buckingham(r, l, p, t, v, Q, x1) / buckinghamDeriv(r, l, p, t, v, x1);
	}

	std::cout << "accuracy accomplished " << EPS << std::endl;
	std::cout << "initial X = " << initialX << ", root = " << x1 << std::endl;
	std::cout << "*****  Press any key  *****" << std::endl;
	std::cin.ignore();
}

int main() {
	calculateX(1);
	calculateX(10);
	return 0;
}
