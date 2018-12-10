#include "HeatEquation.h"

HeatEquation::HeatEquation(){
  // Lx = 150;
  // Ly = 120;
  Ly = 10;
  Lx = 10;
  dl = 1;
  Nx = int(Lx/dl);
  Ny = int(Ly/dl);

  dt = 0.1;
  Time = 1;
  T = int(Time/dt);
  alpha = dt/(dl*dl);
  tolerance = 0.0001;

  double rho = 3.5e3;
  double cp = 1000;
  double k = 2.5;
  double betaSq = k/(rho*cp);
  Q1 = 1.4e-6*betaSq/k;
  Q2 = 0.35e-3*betaSq/k;
  Q3 = 0.05e-3*betaSq/k;


  uNew = new double*[Nx+2];
  uOld = new double*[Nx+2];
  uGuess = new double*[Nx+2];
  for (int i = 0; i < Nx+2; i++){
    uNew[i] = new double[Ny+2];
    uOld[i] = new double[Ny+2];
    uGuess[i] = new double[Ny+2];
  }
  for (int i = 0; i < Nx+2; i++) {
    for (int j = 0; j < Ny+2; j++) {
      uNew[i][j] = 0.0;
      uGuess[i][j] = 1.0;
    }
  }
  for(int i=0; i < Nx+2; i++){
    uNew[i][0] = 8.0;
    uNew[i][Ny+1] = 1300.0;
  }
  for(int i=0; i < Ny+2; i++){
    uNew[0][i] = 8 + 1292*i*dl/(Ny+1);
    uNew[Nx+1][i] = 8 + 1292*i*dl/(Ny+1);
  }
  for (int i = 0; i < Nx+2; i++) for (int j = 0; j < Ny+2; j++) uOld[i][j] = uNew[i][j];

}

int HeatEquation::jacobi() {
  int maxIterations = 100000;
  double diff = 1;
  int iterations = 0;
  for (int i = 0; i < Nx+2; i++) for (int j = 0; j < Ny+2; j++) uGuess[i][j] = 1.0;

  while (diff > tolerance && iterations < maxIterations){
    diff = 0;
    for (int i = 1; i < Nx+1; i++){
      for (int j = 1; j < Ny+1; j++){
        uNew[i][j] = (dt*Q1 + uOld[i][j] + alpha*(uGuess[i+1][j] + uGuess[i-1][j] + uGuess[i][j+1] + uGuess[i][j-1]))/(1+4*alpha);
        diff += fabs(uNew[i][j] - uGuess[i][j]);
      }
    }
    for (int i = 0; i < Nx+2; i++){
      for (int j = 0; j < Ny+2 ;j++){
        uGuess[i][j] = uNew[i][j];
      }
    }
    iterations++;
  }
  for (int i = 0; i < Nx+2; i++) for (int j = 0; j < Ny+2; j++) uOld[i][j] = uNew[i][j];
  return iterations;
}

void HeatEquation::solve(){
  int it;
  ofstream ofile;
  ofile.open("HeatEquation.dat");
  for (int t = 0; t < T; t++){
    output(ofile);
    it = jacobi();
    cout << "t:" << double(t)/double(T)*double(Time) << endl;
    cout << "Number of iterations: " << it << endl;
  }
  ofile.close();
}

void HeatEquation::output(ofstream &ofile){
  for (int i=0; i<Nx+2; i++){
      for (int j=0; j<Ny+2; j++){
        ofile << setw(20) << setprecision(8) << uNew[i][j];
      }
    ofile << endl;
  }
}

HeatEquation::~HeatEquation(){
  for (int i = 0; i < Nx+2; i++){
    delete [] uNew[i];
    delete [] uOld[i];
    delete [] uGuess[i];
  }

  delete [] uNew;
  delete [] uOld;
  delete [] uGuess;
}
