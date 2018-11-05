#ifndef METROPOLIS_H
#define METROPOLIS_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <random>
#include "initializeLattice.h"
using namespace std;

void metropolis(int dim, int state, int loopStart, int loopStop, double T, double *E, double *M, double *ExpecVal, double **Lattice, double ***PointerLattice, std::mt19937_64 &gen, std::uniform_real_distribution<double> &distribution, int *counter);

#endif /* METROPOLIS_H */
