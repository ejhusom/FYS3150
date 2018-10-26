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
#include <random>
using namespace std;

void InitializeLattice(double **Lattice, int dim, int state, double *E, double *M, std::mt19937_64 &gen, std::uniform_real_distribution<double> &distribution);

int main(int argc, char *argv[]){
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0,1.0);



  int dim = 2;
  int state = 1; // 1: ordered initial state, else: random state
  int nCycles = 100;
  double T = 100;
  switch (argc) {
    case 4: nCycles = atoi(argv[3]);
    case 3: state = atoi(argv[2]);
    case 2: dim = atoi(argv[1]);
  }

  double E = 0;
  double M = 0;
  double **Lattice = new double*[dim+2];
  for (int i = 0; i < dim+2; i++){
    Lattice[i] = new double[dim+2];
  }
  InitializeLattice(Lattice, dim, state, &E, &M, gen, distribution);

  double *w = new double[17];
  for (int i = 0; i < 17; i+=4) w[i] = exp(-(i-8)/T);

  int x, y, dE;
  for (int cycle = 0; cycle < nCycles; cycle++) {
    for (int i = 1; i < dim+1; i++) {
      for (int j = 1; j < dim+1; j++) {
        // Find random indeces x, y
        x = 1 + (int) (distribution(gen)*(double)dim);
        y = 1 + (int) (distribution(gen)*(double)dim);
        dE = 2*Lattice[x][y]*(Lattice[x-1][y]+
          Lattice[x+1][y]+
          Lattice[x][y-1]+
          Lattice[x][y+1]);
          if (distribution(gen) <= w[dE+8]) {
            Lattice[x][y] *= -1;  // flip the spin
            M += 2*Lattice[x][y]; // update magnetization
            E += (double) dE;     // update energy
          }
        }
      }
  }

  // print matrix
  for (int i=0; i<dim+2; i++){
      for (int j=0; j<dim+2; j++){
        cout << setw(8) << setprecision(4) << Lattice[i][j];
      }
    cout << endl;
  }

  // deallocate memory
  for (int i = 0; i < dim+2; i++){
    delete [] Lattice[i];
  }
  delete [] Lattice;
  delete [] w;

  return 0;
} // end of main function

void InitializeLattice(double **Lattice, int dim, int state, double *E, double *M, std::mt19937_64 &gen, std::uniform_real_distribution<double> &distribution){
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
  // filling four "ghost vectors"
  for (int i = 0; i < dim+1; i++) {
    Lattice[i][dim+1] = Lattice[i][1];
    Lattice[i][0] = Lattice[i][dim];
    Lattice[dim+1][i] = Lattice[1][i];
    Lattice[0][i] = Lattice[dim][i];
  }
} // end of function InitializeLattice
