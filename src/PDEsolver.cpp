#include "PDEsolver.h"

PDEsolver::PDEsolver(){
}

PDEsolver::PDEsolver(int N_, double dt_, double Time_, double method_, double u_i_, double u_f_){
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

    // for (int i=0; i<N+2; i++){
    //   cout << setw(12) << setprecision(6) << diagArray[i] << endl;
    // }

  }

  uNew = new double[N+2];
  uOld = new double[N+2];
  for (int i = 0; i < N+2; i++) {
    uNew[i] = 0.0;
    uOld[i] = 0.0;
  }
  //initial condition
  uOld[0] = u_i;
  uNew[0] = u_i;
  uOld[N+1] = u_f;
  uNew[N+1] = u_f;
}


void PDEsolver::forwardEuler(){
  for (int i = 1; i < N+1; i++) {
    uNew[i] = alpha*uOld[i-1] + (1-2*alpha)*uOld[i] + alpha*uOld[i+1];
  }
  for (int i = 0; i < N+2; i++) uOld[i] = uNew[i];
}

void PDEsolver::tridiag(){

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
      // diagNew[i] = diag - offDiag*K;
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
    // cout << "test\n";
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

void PDEsolver::analytical(double Time){
  ofstream outfile;
  //tror vi har feil analytical solution. Den skal jo være u(0, t) = 0 i x=0 og u(L, t) = 1 i x=L.
  //våres analytiske er 0 i begge ender..
  outfile.open("analytical.dat");
  for (int i=0; i < N; i++){
    double x = double(i)/N;
    // // double u = sin(M_PI*x)*exp(M_PI*M_PI*Time);

    double u = 100*exp(-Time)*sin(M_PI*x);
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
