/*
Arjan Singh (as2995)
May 15, 2017

circuits.h

Circuit equations, parameters and constants
*/

#include <vector>
using namespace std;

//Oscillator Parameters
extern double C; //Parasitic Capacitance
extern double L; //Circuit Inductor

//RLC Parameters
extern double R_rlc;
extern double L_rlc;
extern double C_rlc;

double i(double t);

vector<double> time_gen_osc();

vector<double> time_gen_rlc();

double ID_EKV(double VGS, double VDS);

vector<double> osc_equations(vector<double> V, double t);

vector<double> RLC_equations(vector<double> V, double t);
