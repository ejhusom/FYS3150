#include "HeatEquation.h"

HeatEquation::HeatEquation(int _slab, int _radioactive){
  // Lx = 150;
  // Ly = 120;
  Lx = 1.25;
  Ly = 1;
  // dl = 0.1;
  dl = 0.01;
  Nx = int(Lx/dl);
  Ny = int(Ly/dl);
  slab = _slab;
  radioactive = _radioactive;
  if (radioactive == 0) slab = 0;

  dt = 0.1;
  // dt = 0.05;
  Time = 1;
  T = int(Time/dt);
  alpha = dt/(dl*dl);
  tolerance = 0.0001;

  double rho = 3.5e3;
  double cp = 1000;
  double k = 2.5;
  double uc = 1300;
  // double tc = 1e9;
  double tc = 3.15576e16;
  // double l = 26.7;
  double l = 120000;
  // double l = 0;

  beta = tc*k/(rho*cp*l*l);
  gamma = tc/(rho*cp*uc);
  // beta = rho*cp*l*l/(k*tc);

  double Q1 = 1.4e-6*tc/(rho*cp*uc);
  double Q2 = 0.35e-6*tc/(rho*cp*uc);
  double Q3 = 0.05e-6*tc/(rho*cp*uc);
  // double Q1 = 1.4e-6*l*l/k;
  // double Q2 = 0.35e-6*l*l/k;
  // double Q3 = 0.05e-6*l*l/k;

  if (radioactive == 0){
    Q1 = 0;
    Q2 = 0;
    Q3 = 0;
  }

  Q = new double[Ny+2];
  Q4 = new double[T];
  for (int i = 0; i < int((Ny+2)/6); i++) {
    Q[i] = Q1;
  }
  for (int i = int((Ny+2)/6); i < int(2*(Ny+2)/6); i++) {
    Q[i] = Q2;
  }
  for (int i = int(2*(Ny+2)/6); i < Ny+2; i++) {
    Q[i] = Q3;
  }

  if(slab == 1) decay(l, k);



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
    uNew[0][i] = i/double(Ny+1);
    // uNew[0][i] = 0;
    // uNew[0][i] = boundaryArray[i];
    // uNew[Nx+1][i] = 0;
    uNew[Nx+1][i] = i/double(Ny+1);
    // uNew[Nx+1][i] = boundaryArray[i];
  }
  for(int i=0; i < Nx+2; i++){
    uNew[i][0] = 0;
    uNew[i][Ny+1] = 1;
  }

  if(slab == 12){
    mat uMatrix = zeros<mat>(Nx+2, Ny+2);
    uMatrix.load("HeatEquationSteadyStateQ.dat");
    for (int i = 0; i < Nx+2; i++) {
      for (int j = 0; j < Ny+2; j++) {
        uNew[i][j] = uMatrix(i, j);
      }
    }
  }

  for (int i = 0; i < Nx+2; i++) for (int j = 0; j < Ny+2; j++) uOld[i][j] = uNew[i][j];

}

int HeatEquation::jacobi(int t, double **boundaryMatrix) {
  int maxIterations = 100000;
  double diff = 1;
  int iterations = 0;
  for (int i = 0; i < Nx+2; i++) for (int j = 0; j < Ny+2; j++) uGuess[i][j] = 1.0;

  while (diff > tolerance && iterations < maxIterations){
    diff = 0;
    for (int i = 1; i < Nx+1; i++){
      for (int j = 1; j < Ny+1; j++){
        uNew[i][j] = (dt*Q[i] + uOld[i][j] + beta*alpha*(uGuess[i+1][j] + uGuess[i-1][j] + uGuess[i][j+1] + uGuess[i][j-1]))/(1+4*alpha*beta);
        // uNew[i][j] = (dt*Q[i] + uOld[i][j] + alpha*(uGuess[i+1][j] + uGuess[i-1][j] + uGuess[i][j+1] + uGuess[i][j-1]))/(1+4*alpha);
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

  // for(int i=0; i < Ny+2; i++){
  //   uNew[0][i] = boundaryMatrix[t][i];
  //   uNew[Nx+1][i] = boundaryMatrix[t][i];
  // }

  return iterations;
}

void HeatEquation::decay(double l, double k){
  double halfTimes[3] = {4.47, 14.0, 1.25};
  double weights[3] = {0.2, 0.2, 0.1};
  for(int i = 0; i < 3; i++) weights[i] *= 1e-6*gamma;
  for(int tp = 0; tp < T; tp++){
    double sumQ4 = 0;
    double t = tp/(double) T;
    for(int i = 0; i < 3; i++){
      sumQ4 += weights[i]*pow(0.5, t/halfTimes[i]);
      // cout << sumQ4 << endl;
    }
    Q4[tp] = sumQ4;
  }
}

void HeatEquation::solve(double **boundaryMatrix){
  int it;
  ofstream ofile;
  if(slab == 1){
    ofile.open("HeatEquationSlab.dat");
    cout << "Slab" << endl;
  }
  if(slab == 0 && Q[0] != 0){
    ofile.open("HeatEquationNoSlab.dat");
    cout << "Q, but no slab" << endl;
  }
  if(Q[0] == 0 && slab == 0){
    ofile.open("HeatEquationNoQ.dat");
    cout << "No Q" << endl;
  }
  for (int t = 0; t < T; t++){
    if(slab == 1){
      for (int i = int(2*(Ny+2)/6); i < Ny+2; i++) {
        Q[i] += Q4[t];
        // cout << "Q4= " << Q4[t] << endl;
      }
    }
    output(ofile);
    it = jacobi(t, boundaryMatrix);
    ///

    ///
    cout << "t:" << double(t)/double(T)*double(Time) << endl;
    cout << "Number of iterations: " << it << endl;
  }
  output(ofile);
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
