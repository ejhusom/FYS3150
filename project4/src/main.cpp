/*=============================================================================
FYS3150 Project 4 by Erik Johannes B. L. G. Husom on 2018-10-25
Description:
- Periodic boundary conditions (PBC).
- Boltzmann constant = 1 -> temperature has dimension energy
- Coupling constant J = 1.
USAGE:
=============================================================================*/
#include "metropolis.h"
#include "analytical.h"
using namespace std;


int main(int argc, char *argv[]){

  int dim = 2;
  int state = 1; // 1: ordered initial state, else: random state
  int nCycles = 100;
  double T = 1;
  switch (argc) {
    case 4: nCycles = atoi(argv[3]);
    case 3: state = atoi(argv[2]);
    case 2: dim = atoi(argv[1]);
  }

  metropolis(dim, state, nCycles, T);
  analyticalEnergy(T);
  analyticalSpecificHeat(T);

  return 0;
} // end of main function
