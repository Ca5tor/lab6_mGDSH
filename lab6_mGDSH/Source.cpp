#include <iostream>
#include <iomanip>

double f(double x, double y) { 
	return (5*x*x + 6*y*y +3*x -2*y +3);
}

double gx(double x) { return (10 * x + 3); } // df/dx

double gy(double y) { return (12 * y - 2); } // df/dy

double DP(double x, double y, double L0) {
	double P, T, L = L0;
	double S = f(x, y);// Значение целевой функции в текущей точке

	P = f(x - L * gx(x), y - L * gy(y));
	T = L / 2 * (gx(x) * gx(x) + gy(y) * gy(y));

	while (S - P < T) {
		L /= 2;
		P = f(x - L * gx(x), y - L * gy(y));
		T = L / 2 * (gx(x) * gx(x) + gy(y) * gy(y));
	} 

	return L;
}

void GDH(double x, double y, double E) {
	double xmin, ymin, L;
	int k = 0;

	std::cout << "k\tx\t\ty\t      gx\t    gy" << std::endl;
	std::cout << k << std::setw(9) << x << std::setw(15) << y << std::setw(15) <<
		gx(x) << std::setw(15) << gy(y) << std::endl;

	k = 1;

	while (std::abs(gx(x)) > E && std::abs(gy(y)) > E) {
		L = DP(x, y, 0.5);
		x = x - L * gx(x);
		y = y - L * gy(y);

		std::cout << std::setprecision(4) << k << std::setw(9) <<
			x << std::setw(15) << y << std::setw(15) <<
			gx(x) << std::setw(15) << gy(y) << std::endl;

		k++;
	}
	xmin = x;
	ymin = y;
	std::cout << "\n\tXmin= " << x << "\tYmin= " << y << std::endl;
}

void main() {
	double a = 0.f, b = 0.f, E = 0.0001f;
	GDH(a, b, E);
	std::cin.get();
}