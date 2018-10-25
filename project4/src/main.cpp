/*==============================================================================
Title:           FYS3150 - Project 4:
Author:          Erik Johannes B. L. G. Husom
Date:            2018-10-25
Version:         0.1
Description:
- Periodic boundary conditions (PBC).
- Boltzmann constant = 1 -> temperature has dimension energy
- Coupling constant J = 1.
USAGE:
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void InitializeLattice(int N){
  // create and fill lattice
  double **Lattice = new double*[N];
  for (int i = 0; i < N; i++){
    Lattice[i] = new double[N];
  }
  for(int i=0 ; i < N ; i++) {
    for(int j=0 ; j < N ; j++) {
      Lattice[i][j] = 1.0;
    }
  }
} // end of InitializeLattice function

int main(int argc, char *argv[]){
  int N = 2;

  return 0;
} // end of main function
