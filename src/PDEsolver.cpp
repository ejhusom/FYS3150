#include "PDEsolver.h"

PDEsolver::PDEsolver(){
}

PDEsolver::PDEsolver(int N_, double dt_, double Time_, double method_, double u_i_, double u_f_){
  //initializes problem parameters for solving the 1D diffusion equation
  //with either the explicit (0), implicit (1) or crank-nicholson scheme (0.5), specified by
  //the input parameter method_
  N = N_;
  dt = dt_;
  Time = Time_;
  T = int(Time/dt);
  dx = 1/double(N+1);
  method = method_;
  alpha = dt/(dx*dx);
  u_i = u_i_;
  u_f = u_f_;

  if (method==0){
    diag = 1 - 2*alpha;
    offDiag = alpha;
    methodName = "Explicit";
    if(fabs(alpha) > 0.5) cout << "alpha > 0.5, unstable solver." << endl;
  } else if (method==1){
    diag = 1 + 2*alpha;
    offDiag = -alpha;
    methodName = "Implicit";
  } else if (method==0.5){

    diag = 1 + 2*alpha;
    offDiag = -alpha;
    methodName = "Crank";
  } else if (method==2){
    double rho = 3.5e3;
    double cp = 1000;
    double k = 2.5;
    double l = 120;
    double Q1 = 1.4e-6*l*l/k;
    double Q2 = 0.35e-3*l*l/k;
    double Q3 = 0.05e-3*l*l/k;

    u  = new double*[T];
    for (int i = 0; i < T; i++){
      u[i] = new double[N+2];
    }

    diagArray = new double[N+2];
    for (int i = 0; i < int((N+2)/6); i++) {
      diagArray[i] = 1 + 2*alpha + Q1;
    }
    for (int i = int((N+2)/6); i < int(2*(N+2)/6); i++) {
      diagArray[i] = 1 + 2*alpha + Q2;
    }
    for (int i = int(2*(N+2)/6); i < N+2; i++) {
      diagArray[i] = 1 + 2*alpha + Q3;
    }
    offDiag = -alpha;
    methodName = "Heat1D";


  }

  uNew = new double[N+2];
  uOld = new double[N+2];
  for (int i = 0; i < N+2; i++) {
    uNew[i] = 0.0;
    uOld[i] = 0.0;
  }
  //initial conditions
  uOld[0] = u_i;
  uNew[0] = u_i;
  uOld[N+1] = u_f;
  uNew[N+1] = u_f;
}


void PDEsolver::forwardEuler(){
  //Forward euler
  for (int i = 1; i < N+1; i++) {
    uNew[i] = alpha*uOld[i-1] + (1-2*alpha)*uOld[i] + alpha*uOld[i+1];
  }
  for (int i = 0; i < N+2; i++) uOld[i] = uNew[i];
}

void PDEsolver::tridiag(){
    //Solves a tridiagonal matrix by forward and backward substitution
    double diagNew[N+2];
    double uOldTemp[N+2];
    double K;

    for(int i = 0; i < N+2; i++){
      diagNew[i] = 0;
      uOldTemp[i] = 0;
    }

    diagNew[1] = diag;
    uOldTemp[1] = uOld[1];


    //Forward substitution
    for(int i = 2; i < (N+1); i++){
      K = offDiag/diagNew[i-1];
      diagNew[i] = diag - offDiag*K;
      uOldTemp[i] = uOld[i] - uOldTemp[i-1]*K;
    }

    uNew[0] = u_i;
    uNew[N] = uOldTemp[N]/diagNew[N];
    uNew[N+1] = u_f;

    //Backward substitution
    for(int i = (N); i > 0; i--){
        uNew[i] = (uOldTemp[i] - offDiag*uNew[i+1])/diagNew[i];
    }

    for (int i = 0; i < N+2; i++) uOld[i] = uNew[i];

}

void PDEsolver::tridiagHeat(int t){

    double diagNew[N+2];
    double uOldTemp[N+2];
    double K;

    for(int i = 0; i < N+2; i++){
      diagNew[i] = 0;
      uOldTemp[i] = 0;
    }

    diagNew[1] = diagArray[1];
    uOldTemp[1] = uOld[1];


    //Forward substitution
    for(int i = 2; i < (N+1); i++){
      K = offDiag/diagNew[i-1];
      diagNew[i] = diagArray[i] - offDiag*K;
      uOldTemp[i] = uOld[i] - uOldTemp[i-1]*K;
    }

    uNew[0] = u_i;
    uNew[N] = uOldTemp[N]/diagNew[N];
    uNew[N+1] = u_f;

    //Backward substitution
    for(int i = (N); i > 0; i--){
        uNew[i] = (uOldTemp[i] - offDiag*uNew[i+1])/diagNew[i];
    }

    for (int i = 0; i < N+2; i++) uOld[i] = uNew[i];
    for (int i = 0; i < N+2; i++) u[t][i] = uNew[i];

}

void PDEsolver::solve(){
  ofstream ofile;
  ofile.open(methodName + "N" + to_string(N) + ".dat");
  if (method==0){
    for (int t = 0; t < T; t++){
      output(ofile);
      forwardEuler();
    }
  } else if (method==1){
    for (int t = 0; t < T; t++){
      output(ofile);
      tridiag();
    }
  } else if (method==0.5){
    alpha = alpha*0.5;
    for (int t = 0; t < T; t++){
      output(ofile);
      forwardEuler();
      tridiag();
    }
  } else if (method==2){
    for (int t = 0; t < T; t++){
      output(ofile);
      tridiagHeat(t);
    }
  }

  ofile.close();

}


void PDEsolver::output(ofstream &ofile){
  for(int i = 0; i < N+2; i++){
    ofile << setw(20) << setprecision(8) << uNew[i];
  }
  ofile << endl;
}

void PDEsolver::analytical(double Time, int xPoints){
  //analytical solution to the 1D diffusion equation
  ofstream outfile;
  int nFourier = 10000;
  outfile.open("analytical_t=" + to_string(Time) + "_xPoints=" + to_string(xPoints) + ".txt");
  for(int i = 0; i < xPoints+1; i++){
    double x = ((double) i)/((double) xPoints);
    double u = 0;
    for(int j = 1; j < nFourier+1; j++){
      double nPi = M_PI*j;
      double nPi2 = nPi*nPi;
      double an = 2*(nPi*cos(nPi) - sin(nPi))/(nPi2);
      u += an*exp(-nPi2*Time)*sin(nPi*x);
    }
    u += x;
    outfile << setw(15) << setprecision (8) << x;
    outfile << setw(15) << setprecision (8) << u << endl;
  }
  outfile.close();
}


PDEsolver::~PDEsolver(){
  delete [] uNew;
  delete [] uOld;
  delete [] diagArray;
}
