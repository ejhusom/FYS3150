/*==============================================================================
FYS3150 Project 4 by Erik Johannes B. L. G. Husom on 2018-10-25
Description:
- Periodic boundary conditions (PBC).
- Boltzmann constant = 1 -> temperature has dimension energy
- Coupling constant J = 1.
USAGE:
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
using namespace std;



int main(int argc, char *argv[]){
  srand (time(NULL));
  // double randomint = (((double) rand() / (RAND_MAX)) > 0.5) ? 1: -1;
  int dim = 2;
  // create and fill lattice with all spins up, plus ghost vectors for PBC
  double **Lattice = new double*[dim+2];
  for (int i = 0; i < dim+2; i++){
    Lattice[i] = new double[dim+2];
  }
  for(int i=1 ; i < dim+1 ; i++) {
    for(int j=1 ; j < dim+1 ; j++) {
      Lattice[i][j] = 1;
    }
  }
  // filling four "ghost vectors"
  for (int i = 0; i < dim+1; i++) {
    Lattice[i][dim+1] = Lattice[i][1];
    Lattice[i][0] = Lattice[i][dim];
    Lattice[dim+1][i] = Lattice[1][i];
    Lattice[0][i] = Lattice[dim][i];
  }

  double E = 0; double dE = 0;
  for (int i = 1; i < dim+1; i++) {
    for (int j = 1; j < dim+1; j++) {
      // Find random indeces
      x = 1 + (rand() % (int)(dim));
      y = 1 + (rand() % (int)(dim));

      E += Lattice[i][j]*Lattice[i][j+1];
      E += Lattice[i][j]*Lattice[i+1][j];
    }
  }

  // print matrix
  // for (int i=0; i<dim+2; i++){
  //     for (int j=0; j<dim+2; j++){
  //       cout << setw(8) << setprecision(4) << Lattice[i][j];
  //     }
  //   cout << endl;
  // }


  // deallocate memory
  for (int i = 0; i < dim+2; i++){
    delete [] Lattice[i];
  }
  delete [] Lattice;

  return 0;
} // end of main function
