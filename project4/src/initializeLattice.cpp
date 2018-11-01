#include "initializeLattice.h"

void initializeLattice(double **Lattice, double ***PointerLattice, int dim, int state, double *E, double *M, std::mt19937_64 &gen, std::uniform_real_distribution<double> &distribution){
  // create and fill lattice with all spins up, plus ghost vectors for PBC
  if (state==1) {
    for(int i=1 ; i < dim+1 ; i++) {
      for(int j=1 ; j < dim+1 ; j++) {
        Lattice[i][j] = 1;
      }
    }
    *M = dim*dim;
  } else {
    for(int i=1 ; i < dim+1 ; i++) {
      for(int j=1 ; j < dim+1 ; j++) {
        Lattice[i][j] = (distribution(gen) > 0.5) ? 1: -1;
        *M += (double) Lattice[i][j];
      }
    }
  }
  // Set elements of pointer lattice
  for(int i=0 ; i < dim+2 ; i++) {
    for(int j=0 ; j < dim+2 ; j++) {
      PointerLattice[i][j] = &Lattice[i][j];
    }
  }
  // filling four mirror elements
  for (int i = 1; i < dim+1; i++) {
    PointerLattice[i][dim+1] = &Lattice[i][1];
    PointerLattice[i][0] = &Lattice[i][dim];
    PointerLattice[dim+1][i] = &Lattice[1][i];
    PointerLattice[0][i] = &Lattice[dim][i];
  }
  // finding initial energy
  for(int i=1 ; i < dim+1 ; i++) {
    for(int j=1 ; j < dim+1 ; j++) {
      *E -= *PointerLattice[i][j]*(*PointerLattice[i+1][j]+*PointerLattice[i][j+1]);
    }
  }
} // end of function initializeLattice
