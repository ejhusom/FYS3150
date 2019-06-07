#include "PDEsolver2D.h"

PDEsolver2D::PDEsolver2D(){
}

PDEsolver2D::PDEsolver2D(int N_, double dt_, double Time_, double method_){
  //solves the 2D dimensional diffusion equation with jacobis method
  N = N_;
  dt = dt_;
  Time = Time_;
  T = int(Time/dt);
  dx = 1/double(N+1);
  method = method_;
  alpha = dt/(dx*dx);
  methodName = "Implicit";
  tolerance = 0.0001;

  uNew = new double*[N+2];
  uOld = new double*[N+2];
  uGuess = new double*[N+2];
  for (int i = 0; i < N+2; i++){
    uNew[i] = new double[N+2];
    uOld[i] = new double[N+2];
    uGuess[i] = new double[N+2];
  }
  for (int i = 0; i < N+2; i++) {
    for (int j = 0; j < N+2; j++) {
      // uNew[i][j] = 0.0;
      uNew[i][j] = sin(M_PI*i/(N+1))*sin(M_PI*j/(N+1)); // analytical solution
      uGuess[i][j] = 1.0;
    }
  }
  for(int i=0; i < N+2; i++){
    uNew[i][0] = 0.0;
    uNew[i][N+1] = 0.0;
    uNew[0][i] = 0.0;
    uNew[N+1][i] = 0.0;
  }
  for (int i = 0; i < N+2; i++) for (int j = 0; j < N+2; j++) uOld[i][j] = uNew[i][j];

}

int PDEsolver2D::jacobi() {
  int maxIterations = 100000;
  double diff = 1;
  int iterations = 0;
  for (int i = 0; i < N+2; i++) for (int j = 0; j < N+2; j++) uGuess[i][j] = 1.0;

  while (diff > tolerance && iterations < maxIterations){
    diff = 0;
    for (int i = 1; i < N+1; i++){
      for (int j = 1; j < N+1; j++){
        uNew[i][j] = (uOld[i][j] + alpha*(uGuess[i+1][j] + uGuess[i-1][j] + uGuess[i][j+1] + uGuess[i][j-1]))/(1+4*alpha);
        diff += fabs(uNew[i][j] - uGuess[i][j]);
      }
    }
    for (int i = 0; i < N+2; i++){
      for (int j = 0; j < N+2 ;j++){
        uGuess[i][j] = uNew[i][j];
      }
    }
    iterations++;
  }
  for (int i = 0; i < N+2; i++) for (int j = 0; j < N+2; j++) uOld[i][j] = uNew[i][j];
  return iterations;
}

void PDEsolver2D::solve(){
  int it;
  ofstream ofile;
  ofile.open(methodName + "2DN" + to_string(N) + ".dat");
  for (int t = 0; t < T; t++){
    output(ofile);
    it = jacobi();
    cout << "t:" << double(t)/double(T)*double(Time) << endl;
    cout << "Number of iterations: " << it << endl;
  }
  ofile.close();
}

void PDEsolver2D::output(ofstream &ofile){
  for (int i=0; i<N+2; i++){
      for (int j=0; j<N+2; j++){
        ofile << setw(20) << setprecision(8) << uNew[i][j];
      }
    ofile << endl;
  }
}

PDEsolver2D::~PDEsolver2D(){
  for (int i = 0; i < N+2; i++){
    delete [] uNew[i];
    delete [] uOld[i];
    delete [] uGuess[i];
  }

  delete [] uNew;
  delete [] uOld;
  delete [] uGuess;
}
