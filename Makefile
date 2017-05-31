.PHONY: all test clean

compile:
	 g++ -std=c++11 circuits.cpp solver.cpp vector_help.cpp main.cpp -o main

run:
	g++ -std=c++11 circuits.cpp solver.cpp vector_help.cpp main.cpp -o main
	./main