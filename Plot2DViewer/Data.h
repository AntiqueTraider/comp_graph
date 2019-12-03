#define _USE_MATH_DEFINES
#include <cmath>


double					// Исходные значения параметров X0, Y0, px, py
X0 = 200,
Y0 = 200,
px = 50,
py = 100;

double Parabola(double x)
{
	return -x*x+2;
}

double Sinusoid(double x)
{
	return sin(x);
}
double CircleX(double t) {
	return 1 * cos(t);
}
double CircleY(double t) {
	return -1 * sin(t);
}
double ChangeX(double v, double m){
	return cos(v)*cosh(m);
}
double ChangeY(double v, double m) {
	return sin(v)*sinh(m);
}