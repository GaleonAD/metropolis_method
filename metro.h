#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <cmath>
#include <exception>
#include <random>

using std::default_random_engine;
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::cout;
using std::endl;

double deltaE (int * nb, int sk, double J, double Hmi);

void montecarlo (int ** & tablica, int L,
				double J, double Hmi, double kT, 
				default_random_engine & gen);

void sekwencyjnie (int ** & tablica, int L, 
				double J, double Hmi, double kT, 
				default_random_engine & gen);

bool check (int ** tablica, int L, int x, int y, 
				double J, double Hmi, double kT, 
				default_random_engine & gen);

void wypelnijLosowo (int ** & tablica, int L, default_random_engine &gen);

void sprawdz (int ** & tablica, int L);

void wypelnijSpinUP (int ** & tablica, int L);

#endif
