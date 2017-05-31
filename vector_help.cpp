/*
Aalaap Narasipura (agn27) and Arjan Singh (as2995)
April 17, 2017

vector_help.cpp

Operations on vectors
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
using namespace std;

void print_vector(vector<double> v){
	vector<double> a;
	cout << "";

	for (int i = 0; i < v.size(); ++i){
		cout << setprecision(10) << v[i] << " ";
	}

	cout << "" << endl;
}

vector<double> scalar_mult(vector<double> v, double t){
	vector<double> a;
	for (int i = 0; i < v.size(); ++i){
		a.push_back(v[i]*t);
	}

	return a;
}

vector<double> vector_add(vector<double> v1, vector<double> v2){
	vector<double> a;
	for (int i = 0; i < v1.size(); ++i){
		a.push_back(v1[i]+v2[i]);
	}

	return a;
} 

vector<double> vector_4add(vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4){
	vector<double> a;
	for (int i = 0; i < v1.size(); ++i){
		a.push_back(v1[i]+v2[i]+v3[i]+v4[i]);
	}

	return a;
}

double vector_mag(vector<double> v){
	double a;
	for (int i = 0; i < v.size(); ++i){
		a += pow(v[i], 2);
	}

	return pow(a, 1/2);
} 