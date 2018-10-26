#include "metropolis.h"

void metropolis(int dim, int state, int nCycles, double T){
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0,1.0);

  double *ExpectationValues = new double[5];
  for (size_t i = 0; i < 5; i++) ExpectationValues[i] = 0;
  double E, M = 0;
  double **Lattice = new double*[dim+2];
  for (int i = 0; i < dim+2; i++){
    Lattice[i] = new double[dim+2];
  }
  initializeLattice(Lattice, dim, state, &E, &M, gen, distribution);

  double *w = new double[17];
  for (int i = 0; i < 17; i+=4) w[i] = exp(-(i-8)/T);

  int x, y, dE;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for (int cycle = 0; cycle < nCycles; cycle++) {
    for (int i = 1; i < dim*dim+1; i++) {
      // Find random indeces x, y
      x = 1 + (int) (distribution(gen)*(double)dim);
      y = 1 + (int) (distribution(gen)*(double)dim);
      // cout << x << " " << y << endl;
      dE = 2*Lattice[x][y]*(Lattice[x-1][y]+
        Lattice[x+1][y]+
        Lattice[x][y-1]+
        Lattice[x][y+1]);
        if (distribution(gen) <= w[dE+8]) {
          Lattice[x][y] *= -1;  // flip the spin
          if (x == 1) Lattice[dim+1][y] *= -1;
          if (x == dim) Lattice[0][y] *= -1;
          if (y == 1) Lattice[x][dim+1] *= -1;
          if (y == dim) Lattice[x][0] *= -1;
          M += 2*Lattice[x][y]; // update magnetization
          E += (double) dE;     // update energy
        }
      }
      ExpectationValues[0] += E;
      ExpectationValues[1] += E*E;
      ExpectationValues[2] += M;
      ExpectationValues[3] += M*M;
      ExpectationValues[4] += fabs(E);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Time used: " << time_span.count() << " seconds." << endl;

    double Emean = ExpectationValues[0]/nCycles;
    double E2mean = ExpectationValues[1]/nCycles;

    cout << "<E>: " << Emean << endl;
    cout << "CV: " << (E2mean - Emean*Emean)/(T*T) << endl;

    // deallocate memory
    for (int i = 0; i < dim+2; i++){
      delete [] Lattice[i];
    }
    delete [] Lattice;
    delete [] ExpectationValues;
    delete [] w;
} // end of Metropolis function
