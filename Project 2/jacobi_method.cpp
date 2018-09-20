#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <armadillo>
#include "maxoffdiag.h"
#include "rotate.h"

using namespace std;
using namespace std::chrono;
using namespace arma;

void jacobi_method(double **A, double **R, int n){
  int k, l;
  double tolerance = 1e-10;
  double max_iterations = double(n)*double(n)*double(n);
  int iterations = 0;
  double max_ = maxoffdiag(A, &k, &l, n);

  // Computing eigenvalues (with timing)
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  while (max_ > tolerance && iterations < max_iterations){
    max_ = maxoffdiag(A, &k, &l, n);
    rotate(A, R, k, l, n);
    iterations++;
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  cout << "Time used: " << time_span.count() << " seconds." << endl;

  cout << "Number of iterations: " << iterations << endl;

  // extracting the eigenvalues
  double eigenvalues[n];
  for(int i=0 ; i < n ; i++) {
    for(int j=0 ; j < n ; j++) {
      if(i==j){
        eigenvalues[i] = A[i][j];
      }
    }
  }
  sort(eigenvalues, eigenvalues + n);

  //=========================================================================
  // UNIT TEST No. 1: Checking eigenvalues against Armadillo
  vec main = 2*ones<vec>(n);
  vec sub = -1*ones<vec>(n-1);
  vec super = -1*ones<vec>(n-1);
  mat A_ = diagmat(main);
  mat B = diagmat(super,1);
  mat C = diagmat(sub,-1);
  A_ = A_+B+C;
  // A_(n-2,n-1) = 100;

  for (int i=0; i<n; i++){
    if (fabs(eigenvalues[i]-eig_sym(A_)[i]) > tolerance){
      cout << "WARNING! Numerical eigenvalues not matching eigenvalues from Armadillo" << endl;
      break;
    }
  }

  // Print out eigenvalues:
  // cout << "=============================" << endl;
  // cout << setw(12) << setprecision(6) << "Calc. eig.";
  // cout << setw(12) << setprecision(6) << "Arma. eig." << endl;
  // for (int i=0; i<n; i++){
  //   cout << setw(12) << setprecision(6) << eigenvalues[i];
  //   cout << setw(12) << setprecision(6) << eig_sym(A_)[i] << endl;
  // }

  //=========================================================================
  // UNIT TEST No. 2: Checking orthogonality of eigenvectors
  double sum = 0.0;
  for (int j=0; j<n; j++){
    sum += R[0][j]*R[1][j];
  }
  if (sum > tolerance){
    cout << "WARNING! Numerical eigenvectors not matching eigenvectors from Armadillo" << endl;
  }
} // end of jacobi__method function
