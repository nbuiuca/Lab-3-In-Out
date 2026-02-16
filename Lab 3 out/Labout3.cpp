//Nhan Bui
//LAB 3 OUT
//Plotter of polynominal equations

#include <iostream>
#include "graph1.h"

using namespace std;
int getNoTerms();
int* createExponents(int no_terms);
double* createCoefficients(int no_terms);
void getPlotParameters(int& noPoints, double& x_start, double& x_end);
double* generatePoints(int* exponents, double* coefficients, int no_terms, int no_points, double x_start, double x_end);
void plotPoints(double* points, int no_points, double x_start, double x_end);
int main() {
	char repeat;
	do {
		displayGraphics();
		int NoTerms = getNoTerms();
		int* Exponents = createExponents(NoTerms);
		double* Coeff = createCoefficients(NoTerms);
		int no_points;
		double x_start, x_end;
		getPlotParameters(no_points, x_start, x_end);
		double* points = generatePoints(Exponents, Coeff, NoTerms, no_points, x_start, x_end);
		plotPoints(points, no_points, x_start, x_end);

		cout << "Repeat program? (y/n)";

		cin >> repeat;
	} while (tolower(repeat) == 'y');

}
int getNoTerms() {
	int no_terms = 0;
	do {
		cout << "Enter number of terms for the polynomial equation (between 1 and 11): " << endl;
		cin >> no_terms;
	} while (no_terms < 1 || no_terms > 11);
	return no_terms;

}
int* createExponents(int no_terms) {
	int i = 0;
	int* Expo = new int [no_terms];
	for (i; i < no_terms; i++)
	{
		cout << "Enter the exponent for term # " << i + 1 << ":" << endl;
		cin >> Expo[i];
	}
	return Expo;
}
double* createCoefficients(int no_terms) {
	int i = 0;
	double* Coeff = new double [no_terms];
	for (i; i < no_terms; i++)
	{
		cout << "Enter the Coefficients for term #" << i + 1 << ":" << endl;
		cin >> Coeff[i];
	}
	return Coeff;
}
void getPlotParameters(int& noPoints, double& x_start, double& x_end) {
	do {
		cout << "Enter # of points to be plotted (100 to 640): " << endl;
		cin >> noPoints;
	} while (noPoints < 100 || noPoints > 640);
	do {
		cout << "Enter plot's starting position on x asis (-100 to -1): " << endl;
		cin >> x_start;
	} while (x_start < -100 || x_start > -1);
	do {
		cout << "Enter plot's ending position on x asis (1 to 100): " << endl;
		cin >> x_end;
	} while (x_end < 1 || x_end > 100);

}
double* generatePoints(int* exponents, double* coefficients, int no_terms, int no_points, double x_start, double x_end) {
	double* points = new double[no_points];
	double  x = x_start;
	double offset = (x_end - x_start) / no_points;
	for (int i = 0; i < no_points; i++) {
		points[i] = 0 ;
		for (int j = 0; j < no_terms; j++) {
			points[i] += coefficients[j] * pow(x, exponents[j]);
		}
		x += offset;
	}
	return points;
}
void plotPoints(double* points, int no_points, double x_start, double x_end) {
	double xmax = 0;
	double ymax = 0;

	if (abs(x_end) > xmax)
		xmax = abs(x_end); // have to xmax = ..
	if (abs(x_start) > xmax)
		xmax = abs(x_start);
	for (int i = 0; i < no_points; ++i) {
		if (abs(points[i]) > ymax)
			ymax = abs(points[i]);
	}
	int colorXASIS;
	int colorYASIS;
	colorXASIS = drawLine(0, 240, 640, 240, 1);// xasis
	colorYASIS = drawLine(320, 0, 320, 480, 1);// yasis

	setColor(colorXASIS, 255, 255, 0);
	setColor(colorYASIS, 255, 255, 0);
	for (int i = 0; i < no_points; ++i) {
		double x = x_start + (i * (x_end - x_start) / no_points);
		if (x > 0 && points[i] > 0) {
			drawPoint(320 + (fabs(x) / xmax * 320), 240 - (fabs(points[i]) / ymax * 320));
		}
		else if (x < 0 && points[i] > 0) {
			drawPoint(320 - (fabs(x) / xmax * 320), 240 - (fabs(points[i]) / ymax * 320));
		}

		else if (x < 0 && points[i] < 0) {
			drawPoint(320 - (fabs(x) / xmax * 320), 240 + (fabs(points[i]) / ymax * 320));
		}
		else if (x > 0 && points[i] < 0) {
			drawPoint(320 + (fabs(x) / xmax * 320), 240 + (fabs(points[i]) / ymax * 320));
		}
	}
}