#ifndef INITIALIZELATTICE_H
#define INITIALIZELATTICE_H
#include <random>
#include <iostream>
#include <iomanip>
using namespace std;

void initializeLattice(double **Lattice, int dim, int state, double *E, double *M, std::mt19937_64 &gen, std::uniform_real_distribution<double> &distribution);

#endif /* INITIALIZELATTICE_H */
