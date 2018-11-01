#include "metropolis.h"

void metropolis(int dim, int state, int nCycles, double T){
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0,1.0);

  double *ExpecVal = new double[5];
  for (size_t i = 0; i < 5; i++) ExpecVal[i] = 0;
  double E, M = 0;
  double **Lattice = new double*[dim+2];
  for (int i = 0; i < dim+2; i++){
    Lattice[i] = new double[dim+2];
  }
  double ***PointerLattice = new double**[dim+2];
  for (int i = 0; i < dim+2; i++){
    PointerLattice[i] = new double*[dim+2];
  }
  initializeLattice(Lattice, PointerLattice, dim, state, &E, &M, gen, distribution);

  double *w = new double[17];
  for (int i = 0; i < 17; i+=4) w[i] = exp(-(i-8)/T);

  int x, y, dE;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for (int cycle = 0; cycle < nCycles; cycle++) {
    for (int i = 1; i < dim*dim+1; i++) {
      // Find random indeces x, y
      x = 1 + (int) (distribution(gen)*(double)dim);
      y = 1 + (int) (distribution(gen)*(double)dim);
      dE = 2**PointerLattice[x][y]*(*PointerLattice[x-1][y]+*PointerLattice[x+1][y]+*PointerLattice[x][y-1]+*PointerLattice[x][y+1]);
      if (distribution(gen) <= w[dE+8]) {
        Lattice[x][y] *= -1;  // flip the spin
        M += 2**PointerLattice[x][y]; // update magnetization
        E += (double) dE;     // update energy
      }
    }
    ExpecVal[0] += E;
    ExpecVal[1] += E*E;
    ExpecVal[2] += M;
    ExpecVal[3] += M*M;
    ExpecVal[4] += fabs(M);
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  cout << "Time used: " << time_span.count() << " seconds." << endl;

  double EV_E = ExpecVal[0]/nCycles/dim/dim;
  double EV_E2 = ExpecVal[1]/nCycles/dim/dim;
  double EV_M = ExpecVal[2]/nCycles/dim/dim;
  double EV_M2 = ExpecVal[3]/nCycles/dim/dim;
  double EV_Mabs = ExpecVal[4]/nCycles/dim/dim;


  cout << "Temperature: " << T << endl;
  cout << "Number of cycles: " << nCycles << endl;
  cout << "<E>: " << EV_E << endl;
  cout << "CV: " << (EV_E2 - EV_E*EV_E)/(T*T) << endl;

  // deallocate memory
  for (int i = 0; i < dim+2; i++){
    delete [] Lattice[i];
    delete [] PointerLattice[i];
  }
  delete [] Lattice;
  delete [] PointerLattice;
  delete [] ExpecVal;
  delete [] w;
} // end of Metropolis function
