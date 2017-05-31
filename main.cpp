/*
Arjan Singh (as2995)
May 15, 2017

main.cpp

Circuit simulator
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>


#include "solver.h"
#include "circuits.h"
#include "vector_help.h"

using namespace std;

int main(){

	bool OSC = 1; //Set to 1 to run oscilattor simulation
	bool RLC = 1; //Set to 1 to run RLC simulation

	//Oscilattor Parameters

	C =	1e-8; //Parasitic Capacitance
	L =	20e-6; //Circuit Inductor
	
	//RLC Parameters
	
	R_rlc = 0.005;
	L_rlc =	1e-6;
	C_rlc = 1e-6;


	std::vector<double> sim_time_osc = time_gen_osc(); //Time vector
	std::vector<double> sim_time_rlc = time_gen_rlc(); //Time vector
	double h_rlc = 5e-8; // time step for rlc
	double h_osc = 5e-8; // time step for osc

	if (RLC){
		/*
		*	Simulation of simple RLC circuit
		*	To find: [V1 i1]
		*	Capacitor is initially charged to 1 V
		*/
		std::vector< std::vector<double> > RLC_sol; //vector of solution vectors at different time intervals
		for(int i = 0; i < sim_time_rlc.size(); ++i){
	       	std::vector<double> v;
	       	//Use RK4 to solve for unknowns and time = sim_time_rlc[i]
	       	v = rungeKutta4({1,0},
	                        sim_time_rlc[i],
	                        0,
	                        h_rlc,
	                        RLC_equations);
	        RLC_sol.push_back(v);
	    }

	    //output to csv file
		ofstream file1;
		file1.precision(8);
		file1.open ("RLC_log.csv");
		file1 << "t,V1,i1,\n";
		for (int i = 0; i < sim_time_rlc.size(); ++i){
			file1 << sim_time_rlc[i] << "," << (RLC_sol[i])[0] << "," << (RLC_sol[i])[1]<< ",\n";
		}
		file1.close();
		//---------------------------------------------------------------------------------------------------
	}
	if (OSC){
		/*
		*	Simulation of Cross coupled NFET oscillator
		*	To find: [V1 V2 i1 i2]
		*	Isource = Io Sin(2pi f t), where f = 100 kHz
		*/
		std::vector< std::vector<double> > osc_sol; //vector of solution vectors at different time intervals
		
		for(int i = 0; i < sim_time_osc.size(); ++i){
	        std::vector<double> v;
	        //Use RK4 to solve for unknowns and time = sim_time_osc[i]
	        v = rungeKutta4({10,0,0,0},
	                        sim_time_osc[i],
	                        0,
	                        h_osc,
	                        osc_equations);
	        osc_sol.push_back(v);
	    }
		
		//output to csv file
		ofstream file2;
		file2.open ("osc_log.csv");
		file2 << "t,V1,V2,i1,i2," << endl;
		for (int i = 0; i < sim_time_osc.size(); ++i){
			file2 << sim_time_osc[i] << "," << (osc_sol[i])[0] << "," << (osc_sol[i])[1] << "," << (osc_sol[i])[2] << "," << (osc_sol[i])[3] << endl;
		}
		file2.close();
		//---------------------------------------------------------------------------------------------------
	}
}