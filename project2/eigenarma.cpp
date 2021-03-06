#include <armadillo>
#include <chrono>
#include <iostream>

using namespace arma;
using namespace std;
using namespace std::chrono;

// Get eigenvectors and -values from Armadillo and writes them to file
void eigenarma(int n, double *eigs, double rho_n=0, double omega=0, double *timing_arma=0){
  // Determine parameters
  vec rho = zeros<vec>(n);
  vec V = zeros<vec>(n);
  double Diag; double NonDiag;
  if (rho_n != 0){
    double h = rho_n/double(n+1);
    Diag = 2.0/(h*h);
    NonDiag = -1.0/(h*h);
    for (int i=0; i<n; i++){
      rho(i) = (i+1)*h;
      V(i) = rho(i)*rho(i);
    }
    if (omega > 0){
      double omega2 = omega*omega;
      for (int i=0; i<n; i++){
        V[i] = V[i]*omega2 + 1/rho[i];
      }
    }
  } else {
    Diag = 2.0;
    NonDiag = -1.0;
  }

  // Create matrix
  vec main = Diag*ones<vec>(n);
  main += V;
  vec off = NonDiag*ones<vec>(n-1);
  mat A = diagmat(main);
  mat B = diagmat(off,1);
  mat C = diagmat(off,-1);
  A = A+B+C;
  vec eigval;
  mat eigvec;

  // Solving and timing
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  eig_sym(eigval, eigvec, A);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  // Returning eigenvalues and timing
  *timing_arma = double(time_span.count());
  // double eigs[n];
  for (int i = 0; i < n; i++) {
    eigs[i] = eigval(i);
  }

  // Save results for plotting
  // eigvec.save("eigvec_o" + to_string(omega) + ".dat",raw_ascii);
  // eigval.save("eigval_o" + to_string(omega) + ".dat",raw_ascii);
  // rho.save("rho_o" + to_string(omega) + ".dat",raw_ascii);
}
