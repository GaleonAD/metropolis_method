//#include <iostream>
//#include <cmath>
//#include <exception>
//#include <random>
#include "metro.h"

double deltaE (int * nb, int sk, double J, double Hmi){
	double dE = 0.; 	// zaczynamy on policzenia sumy w nawiasie
	for(int i = 0; i < 4; ++i){
		dE += (double) nb[i];
	}
	dE *= J; 	// * całka wymiany
	dE += Hmi;	// + wpływ pola
	dE *= -2.*sk;	// * spin w sprawdzanym miejscu
	return dE;	
}

bool check (int ** tablica, int L, int x, int y, 
				double J, double Hmi, double kT, 
				default_random_engine &gen){
	bool condition;
	int nb[4];
	
	// warunki brzegowe
	if (x == 0){
		nb[0] = tablica[L-1][y];
	}
	else {
		nb[0] = tablica[x-1][y];
	}
	////
	if (x == L-1){
		nb[1] = tablica[0][y];
	}
	else {
		nb[1] = tablica[x+1][y];
	}
	////
	if (y == 0){
		nb[2] = tablica[x][L-1];
	}
	else {
		nb[2] = tablica[x][y-1];
	}
	////
	if (y == L-1){
		nb[3] = tablica[x][0];
	}
	else {
		nb[3] = tablica[x][y+1];
	}
	////
	// schemat Metropolisa
	double dE = deltaE(nb, tablica[x][y], J, Hmi);
	double R;
	uniform_real_distribution<double> losR(0., 1.);
	if (dE <= 0){
		condition = true;
	}
	else {
		R = losR(gen);
		if (R < exp(-dE/kT)){
			condition = true;
		}
		else {
			condition = false;
		}
	}

	return condition;
}

void montecarlo (int ** & tablica, int L, double J, 
			double Hmi, double kT, default_random_engine &gen ){
	
	int N =  L * L;

//	default_random_engine gen;

	uniform_int_distribution<int> los(0, L - 1);

	bool condition;

	for(int i = 0; i < N; ++i){
		int x = los(gen);
		int y = los(gen);
		condition = check (tablica, L, x, y, J, Hmi, kT, gen);
		if ( condition ){
			tablica[x][y] *= -1;
		}
	}
}


void sekwencyjnie (int ** & tablica, int L,
				double J, double Hmi, double kT, default_random_engine &gen){
	bool condition;
	for(int x = 0; x < L; ++x) {
		for(int y = 0; y < L; ++y){
			condition = check (tablica, L, x, y, J, Hmi, kT, gen);
			if( condition ){
				tablica[x][y] *= -1;
			}
		}
   	}
}

void wypelnijLosowo (int ** & tablica, int L, default_random_engine &gen){
	double Rand;
	uniform_real_distribution<double> losRand(0., 1.);
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < L; ++j){
			Rand = losRand(gen);
			if ( Rand > 0.35 ){ tablica[i][j] = 1; }
			else {tablica[i][j] = -1; }
		}
	}
}

void wypelnijSpinUP (int ** & tablica, int L){
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < L; ++j){
		tablica[i][j] = 1; 
		}
	}
}

void sprawdz (int ** & tablica, int L){
  	for(int i = 0; i < L; ++i) {
       		for(int j = 0; j < L; ++j){
			if(tablica[i][j] != 1 && tablica[i][j] != -1){
			cout << "Coś nie tak z danymi wejściowymi... wychodzenie." 
				<< endl;
			throw "Bad input!";
			}
		}
	}
}
