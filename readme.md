# NFET Oscillator Circuit Simulation

This program simulates the transient behavior of a basic theoretical cross coupled NFET Oscillator.
The EKV model is used to simulate the behavior of the NFET. In addition to the Oscillator, the program
also simulates a basic theoretical RLC circuit.

Please follow these steps to change parameters and choose which simulation to run:
- To run the Oscillator simulation set OSC to 1 in "main.cpp" , else set it to 0
- To run the RLC simulation set RLC to 1 in "main.cpp" , else set it to 0
- It is possible to change the parameters of the two circuits and the step size of the ODE solver
  in "main.cpp" as well

Please follow the following steps to run the program:
- To run the simulation according to the set parameters, please type "make run" in the command shell while
  in the appropriate directory
- The output of the RLC circuit will be saved in "RLC_log.csv", and the output
  of the Oscillator circuit will be saved in "osc_log.csv"
