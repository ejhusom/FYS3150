#include "PDEsolver.h"

PDEsolver::PDEsolver(){
}

PDEsolver::PDEsolver(int N_, double dt_, int Time_, double method){
  N = N_;
  dt = dt_;
  Time = Time_;
  T = int(Time/dt);
  dx = 1/double(N+1);
  alpha = dt/(dx*dx);

  if (method==0){
    diag = 1 + 2*alpha;
    superDiag = -alpha;
    methodName = "Explicit";
    if(fabs(alpha) > 0.5) cout << "alpha > 0.5, unstable solver." << endl;
  } else if (method==1){
    //mulig fortegn forran alphaleddet er feil, litt ukonsist i forelesningsnotater
    //alternativt er diag = 1 - 2*alpha og superDiag = -alpha. Mest sannsynlig er det ikke feil..
    diag = 1 + 2*alpha;
    superDiag = -alpha;
    methodName = "Implicit";
  } else if (method==2){
    diag = 2 + 2*alpha;
    superDiag = -alpha;
    methodName = "Crank";
  }

  uNew = new double[N];
  uOld = new double[N];
  for (int i = 0; i < N; i++) {
    uNew[i] = 0.0;
    uOld[i] = 0.0;
  }
  //initial condition
  uOld[N-1] = 1.0;
}


void PDEsolver::forwardEuler(){
  for (int i = 1; i < N-1; i++) {
    uNew[i] = alpha*uOld[i-1] + (1-2*alpha)*uOld[i] + alpha*uOld[i+1];
  }
  for (int i = 0; i < N; i++) uOld[i] = uNew[i];
}

void PDEsolver::tridiag(){

    double diagNew[N];
    double uOldTemp[N];
    double K;

    for(int i = 0; i < N; i++){
      diagNew[i] = 0;
      uOldTemp[i] = 0;
    }

    diagNew[0] = diag;
    uOldTemp[0] = uOld[0];


    //Forward substitution
    for(int i = 1; i < N; i++){
      K = superDiag/diagNew[i-1];
      diagNew[i] = diag - superDiag*K;
      uOldTemp[i] = uOld[i] + uOldTemp[i-1]*K;
    }

    uNew[N] = uOldTemp[N]/diagNew[N];

    //Backward substitution
    for(int i = N-1; i > 0; i--){
        uNew[i] = (uOldTemp[i] - superDiag*uNew[i+1])/diagNew[i];
    }

    // for(int i = 0; i < N; i++) cout << diagNew[i] << endl;

}

void PDEsolver::solve(){
  ofstream ofile;
  ofile.open(methodName + "N" + to_string(N) + ".dat");
  for (int t = 0; t < T; t++){
    // tridiag();
    forwardEuler();
    output(ofile);
  }

  ofile.close();

}



void PDEsolver::output(ofstream &ofile){
  for(int i = 0; i < N; i++){
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
}
