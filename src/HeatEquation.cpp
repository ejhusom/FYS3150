#include "HeatEquation.h"

HeatEquation::HeatEquation(double *boundaryArray){
  // Lx = 150;
  // Ly = 120;
  Lx = 1.25;
  Ly = 1;
  dl = 0.01;
  Nx = int(Lx/dl);
  Ny = int(Ly/dl);

  dt = 0.05;
  Time = 1;
  T = int(Time/dt);
  alpha = dt/(dl*dl);
  tolerance = 0.0001;

  double rho = 3.5e3;
  double cp = 1000;
  double k = 2.5;
  double l = 120;
  double Q1 = 1.4e-6*l*l/k;
  double Q2 = 0.35e-3*l*l/k;
  double Q3 = 0.05e-3*l*l/k;
  Q = new double[Ny+2];
  for (int i = 0; i < int((Ny+2)/6); i++) {
    Q[i] = Q1;
  }
  for (int i = int((Ny+2)/6); i < int(2*(Ny+2)/6); i++) {
    Q[i] = Q2;
  }
  for (int i = int(2*(Ny+2)/6); i < Ny+2; i++) {
    Q[i] = Q3;
  }


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
  for(int i=0; i < Ny+2; i++){
    // uNew[0][i] = i*dl/(Ny+1);
    uNew[0][i] = boundaryArray[i];
    // uNew[Nx+1][i] = i*dl/(Ny+1);
    uNew[Nx+1][i] = boundaryArray[i];
  }
  for(int i=0; i < Nx+2; i++){
    uNew[i][0] = 0;
    uNew[i][Ny+1] = 1;
  }
  for (int i = 0; i < Nx+2; i++) for (int j = 0; j < Ny+2; j++) uOld[i][j] = uNew[i][j];

  for (int i=0; i<Nx+2; i++){
      for (int j=0; j<Ny+2; j++){
        cout << setw(8) << setprecision(4) << uNew[i][j];
      }
    cout << endl;
  }

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
        uNew[i][j] = (dt*Q[i] + uOld[i][j] + alpha*(uGuess[i+1][j] + uGuess[i-1][j] + uGuess[i][j+1] + uGuess[i][j-1]))/(1+4*alpha);
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
