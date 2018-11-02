#ifndef METROPOLIS_H
#define METROPOLIS_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <random>
#include "initializeLattice.h"
using namespace std;

void metropolis(int dim, int state, int loopStart, int loopStop, double T, double *ExpecVal);

#endif /* METROPOLIS_H */
