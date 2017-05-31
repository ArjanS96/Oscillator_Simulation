/*
Aalaap Narasipura (agn27) and Arjan Singh (as2995)
April 17, 2017

solver.cpp

Implementation of the ODE solvers
*/

//C++ Libraries
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <climits>
#include <vector>

//Program headers
#include "vector_help.h"
#include "solver.h"
using namespace std;

vector<double> forward_Euler(vector<double> x, double t, double ti, double h, vector<double>(*df)(vector<double> , double)){

	while(ti<=t){
        x = vector_add(x, scalar_mult( (*df)(x, ti), h) );
		ti+=h;
	}

        cout << "k" << endl;
        print_vector(x);
    cout << "--------" << endl;
	return x;
}

vector<double> backward_Euler(vector<double> x, double t, double ti, double h, vector<double>(*df)(vector<double> , double)){
	while(ti<=t){
        ti+=h;
		x = vector_add(x, scalar_mult((*df)(x, ti), h) );
	}

    return x;
}

vector<double> trapezoidal_Euler(vector<double> x, double t, double ti, double h, vector<double>(*df)(vector<double> , double)){
	vector<double> fx, fx_1;
    while(ti<t){
		fx = (*df)(x, ti);
        ti +=h;
        fx_1 = (*df)(x, ti);
        x = vector_add(x, scalar_mult(vector_add(fx, fx_1), (h/2)) );
	}
    return x;
}

vector<double> rungeKutta4(vector<double> x0, double t, double t0, double h, vector<double>(*df)(vector<double>, double)){
    vector<double> k1, k2, k3, k4, k5;
 
    // Iterate for number of iterations
    vector<double> x = x0;

    while(t0<t)
    {
        // Apply Runge Kutta Formulas to find
        // next value of x
        k1 = scalar_mult((*df)(x, t0), h);
        k2 = scalar_mult((*df)(vector_add(x, scalar_mult(k1,0.5)), t0 + 0.5*h),h);
        k3 = scalar_mult((*df)(vector_add(x, scalar_mult(k2,0.75)), t0 + 0.75*h),h);
        k4 = scalar_mult((*df)(vector_add(x, k3), t0 + h),h);

        // Update next value of x
        x = vector_add(x, scalar_mult(vector_4add( scalar_mult(k1,7), 
        										   scalar_mult(k2,6), 
        										   scalar_mult(k3,8), 
        										   scalar_mult(k4,3))
        								,(1/24.0) 
        							  )
       				   );
 
        // Update next value of t
        t0 = t0 + h;
    }
 
    return x;
}

vector<double> rungeKutta4_adaptive(vector<double> x0, double t, double t0,  double h, vector<double>(*df)(vector<double>, double), double eR){
    vector<double> k1, k2, k3, k4, k5;
 
    // Iterate for number of iterations
    vector<double> x = x0;

    vector<double> E;

    while(t0<=t)
    {
        // Apply Runge Kutta Formulas to find
        // next value of x
        k1 = scalar_mult((*df)(x, t0), h);
        k2 = scalar_mult((*df)(vector_add(x, scalar_mult(k1,0.5)), t0 + 0.5*h),h);
        k3 = scalar_mult((*df)(vector_add(x, scalar_mult(k2,0.75)), t0 + 0.75*h),h);
        k4 = scalar_mult((*df)(vector_add(x, k3), t0 + h),h);

        E = scalar_mult(vector_4add(scalar_mult(k1,-5), scalar_mult(k2,5), scalar_mult(k3,8), scalar_mult(k4, -9)),
        	(h/72));

        // Update next value of x
        // Update next value of x
        x = vector_add(x, scalar_mult(vector_4add( scalar_mult(k1,7), 
        										   scalar_mult(k2,6), 
        										   scalar_mult(k3,8), 
        										   scalar_mult(k4,3))
        								,(1/24.0) 
        							  )
       				   );

        //update h
        h = h* pow(eR/(vector_mag(E)/vector_mag(x)),1/3);
 
        // Update next value of t
        t0 = t0 + h;
    }
 
    return x;
}