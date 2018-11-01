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
    case 5: T = atof(argv[4]);
    case 4: nCycles = atoi(argv[3]);
    case 3: state = atoi(argv[2]);
    case 2: dim = atoi(argv[1]);
  }

  // metropolis(dim, state, nCycles, T);
  // analyticalEnergy(T);
  // analyticalSpecificHeat(T);

  int a = 4;
  int n = 4;
  double array[n] = {1,2,3,4};
  // double *pointerarray = new double[n];
  double *pointerarray[n];
  for (int i = 0; i < n; i++) {
    pointerarray[i] = &array[i];
  }
  pointerarray[0] = &array[2];
  cout << "Array / Pointerarray\n";
  for (int i=0; i<n; i++){
    cout << setw(12) << setprecision(6) << array[i];
    cout << setw(12) << setprecision(6) << *pointerarray[i] << endl;
  }
  array[2] = 100;
  cout << "=============\n";
  for (int i=0; i<n; i++){
    cout << setw(12) << setprecision(6) << array[i];
    cout << setw(12) << setprecision(6) << *pointerarray[i] << endl;
  }
  cout << "=====================================\n";
  double **Lattice = new double*[dim+2];
  for (int i = 0; i < dim+2; i++){
    Lattice[i] = new double[dim+2];
  }


  for(int i=1 ; i < dim+1 ; i++) {
    for(int j=1 ; j < dim+1 ; j++) {
      Lattice[i][j] = 1;
    }
  }
  for (int i=0; i<dim+2; i++){
      for (int j=0; j<dim+2; j++){
        cout << setw(8) << setprecision(4) << Lattice[i][j];
      }
    cout << endl;
  }
  cout << "============================\n";


  double*** PointerLattice = new double**[dim+2];
  for (int i = 0; i < dim+2; i++){
    PointerLattice[i] = new double*[dim+2];
  }

  for(int i=0 ; i < dim+2 ; i++) {
    for(int j=0 ; j < dim+2 ; j++) {
      PointerLattice[i][j] = &Lattice[i][j];
    }
  }

  for (int i=0; i<dim+2; i++){
      for (int j=0; j<dim+2; j++){
        // PointerLattice[i][j] = &Lattice[i][j];
        cout << setw(8) << setprecision(4) << *PointerLattice[i][j];
      }
    cout << endl;
  }
  cout << "============================\n";
  Lattice[0][0] = 1000;
  for (int i=0; i<dim+2; i++){
    for (int j=0; j<dim+2; j++){
      // PointerLattice[i][j] = &Lattice[i][j];
      cout << setw(8) << setprecision(4) << *PointerLattice[i][j];
    }
    cout << endl;
  }

  return 0;
} // end of main function
