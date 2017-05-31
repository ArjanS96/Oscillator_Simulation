#include <cmath>
#include <vector>
#include "circuits.h"
using namespace std;

//Oscillator Parameters
double R = 0.1; //Parasitic Resistance
double Rs = 0.1; //Source Resistance

double Is = 5e-6; //Saturation Current
double k = 0.9;

double VTH = 0.3; //Threshold Voltage
double VT = 26e-3;

double C; //Parasitic Capacitance
double L; //Circuit Inductor
double Io = 0.5e-3; //Source Current magnitude
double f =  100e3; //Source Current frequency

//RLC Parameters
double R_rlc;
double L_rlc;
double C_rlc;


//Source current
double i(double t){
	return Io*sin(2*M_PI*f*t);
}

/* 
*	Returns a vector of time values for the oscillator circuit
* 	Unknowns are calculated at these times
*/
vector<double> time_gen_osc(){
	vector<double> t;
	t.push_back(0);
	double cur_t;
	while(cur_t<=20e-6){
		cur_t+=5e-8;
		t.push_back(cur_t);
	}
	return t;
}

/* 
*	Returns a vector of time values for the RLC circuit
* 	Unknowns are calculated at these times
*/
vector<double> time_gen_rlc(){
	vector<double> t;
	t.push_back(0);
	double cur_t;
	while(cur_t<=1e-3){
		cur_t+=1e-6;
		t.push_back(cur_t);
	}
	return t;
}

/* 
*	Returns the curretn through an NFET for a given Vgs and Vds value
*/
double ID_EKV(double VGS, double VDS){
	return Is*pow(log(1+exp((k*(VGS - VTH))/(2*VT))), 2) - Is*(pow(log(1+exp((k*(VGS - VTH)-VDS)/(2*VT))),2));
}	

/* 
*	Returns a vector containing differential equations pertaining to the RLC circuit 
*/
vector<double> RLC_equations(vector<double> V, double t){
	vector<double> v;
	double v1 = V[0];
	double i1 = V[1];

	double dV1_dt = -i1/C_rlc;
	double di1_dt = (v1-i1*R_rlc)/L_rlc;

	v.push_back(dV1_dt); //Equation for dV1/dt
	v.push_back(di1_dt); //Equation for di1/dt

	return v;
}

/* 
*	Returns a vector containing differential equations pertaining to the oscillator circuit 
*/
vector<double> osc_equations(vector<double> V, double t){
	vector<double> v;
	double v1 = V[0];
	double v2 = V[1];
	double i1 = V[2];
	double i2 = V[3];

	double v4 = (i(t) - i1 - i2)/Rs;
	double v6 = 0; //No bottom current source

	double dv1_dt = (i1-ID_EKV(v2-v6, v1-v6))/C;
	double dv2_dt = (i2-ID_EKV(v1-v6, v2-v6))/C;
	double di1_dt = (v4-i1*R-v1)/L;
	double di2_dt = (v4-i2*R-v2)/L;

	v.push_back(dv1_dt); //Equation for dV1/dt
	v.push_back(dv2_dt); //Equation for dV2/dt
	v.push_back(di1_dt); //Equation for di1/dt
	v.push_back(di2_dt); //Equation for di2/dt

	return v;
}