#ifndef METROPOLIS_H
#define METROPOLIS_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>
#include "initializeLattice.h"
using namespace std;
using namespace std::chrono;

void metropolis(int dim, int state, int nCycles, double T);

#endif /* METROPOLIS_H */
