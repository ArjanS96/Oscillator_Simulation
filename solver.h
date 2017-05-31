/*
Arjan Singh (as2995)
April 17, 2017

solver.cpp

Implementation of the ODE solvers
*/

#include <vector>
using namespace std;

vector<double> forward_Euler(vector<double> x, double t, double ti, double h, vector<double>(*df)(vector<double> , double));

vector<double> backward_Euler(vector<double> x, double t, double ti, double h, vector<double>(*df)(vector<double> , double));

vector<double> trapezoidal_Euler(vector<double> x, double t, double ti, double h, vector<double>(*df)(vector<double> , double));

vector<double> rungeKutta4(vector<double> x0, double t, double t0, double h, vector<double>(*df)(vector<double>, double));

vector<double> rungeKutta4_adaptive(vector<double> x0, double t, double t0,  double h, vector<double>(*df)(vector<double>, double), double eR);