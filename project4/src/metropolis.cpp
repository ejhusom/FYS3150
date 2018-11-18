#include "metropolis.h"

void metropolis(int dim, int state, int loopStart, int loopStop, double T, double *E, double *M, double *ExpecVal, double **Lattice, double ***PointerLattice, std::mt19937_64 &gen, std::uniform_real_distribution<double> &distribution, int *counter){
  double *w = new double[17];
  for (int i = 0; i < 17; i+=4) w[i] = exp(-(i-8)/T);

  ofstream dfile;
  dfile.open("4dState1T" + to_string(T) + ".dat");

  int x, y, dE;
  for (int cycle = loopStart; cycle < loopStop; cycle++){
    for (int i = 1; i < dim*dim+1; i++) {
      // Find random indeces x, y
      x = 1 + (int) (distribution(gen)*(double)dim);
      y = 1 + (int) (distribution(gen)*(double)dim);
      dE = 2**PointerLattice[x][y]*(*PointerLattice[x-1][y]+*PointerLattice[x+1][y]+*PointerLattice[x][y-1]+*PointerLattice[x][y+1]);
      if (distribution(gen) <= w[dE+8]) {
        *counter += 1;
        Lattice[x][y] *= -1;  // flip the spin
        *M += 2**PointerLattice[x][y]; // update magnetization
        *E += (double) dE;     // update energy
      }
    }
    ExpecVal[0] += *E;   ExpecVal[1] += *E**E;
    ExpecVal[2] += *M;   ExpecVal[3] += *M**M;
    ExpecVal[4] += fabs(*M);
    // Uncomment the next two lines to produce results for task 4c
    // cout << setw(15) << setprecision(8) << *E/100/dim/dim;
    // cout << setw(15) << setprecision(8) << fabs(*M)/100/dim/dim << endl;
    // Uncomment the next line to produce results for task 4c
    dfile << setw(15) << setprecision(8) << *E/1000000/dim/dim << endl;
  }
  dfile.close();
  delete [] w;
} // end of Metropolis function
