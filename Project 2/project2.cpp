/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         1.0
Description: For solving exercises in project 2, eigenvalue problems.
USAGE:
- Program takes number of mesh poitns as command line argument
- Remember to link armadillo when compiling:
  c++ -o project2.exe project2.cpp -Wall -larmadillo
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <armadillo>
using namespace std;
using namespace std::chrono;
using namespace arma;

void jacobi_method(double **A, double **R, int n);
void rotate(double **A, double **R, int k, int l, int n);
double maxoffdiag(double **A, int *k, int *l, int n);

int main(int argc, char *argv[])
{
  // taking number of mesh points as command line argument
  int n = atoi(argv[1]);

  // creating array
  double **A = new double*[n];
  double **R = new double*[n];
  for (int i = 0; i < n; i++){
    A[i] = new double[n];
    R[i] = new double[n];
  }
  // fill tridiagonal (also printing the matrix)
  for(int i=0 ; i < n ; i++) {
      for(int j=0 ; j < n ; j++) {
          if(i==j){
            A[i][j] = 2.0;
            R[i][j] = 1.0;
          }
          else if(i==j-1||i==j+1){
            A[i][j] = -1.0;
            R[i][j] = 0.0;
          }
          else {
            A[i][j] = 0.0;
            R[i][j] = 0.0;
          }
          // cout << A[i][j] << " ";
      }
      // cout << endl;
  }

  // A[n-2][n-1] = 100;

  jacobi_method(A,R,n);

  // delete allocated memory
  for (int i = 0; i < n; i++) delete [] A[i];


  return 0;
} // end of main function

void jacobi_method(double **A, double **R, int n){
  int k, l;
  double tolerance = 1e-10;
  double max_iterations = double(n)*double(n)*double(n);
  int iterations = 0;
  double max_ = maxoffdiag(A, &k, &l, n);

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  while (max_ > tolerance && iterations < max_iterations){
    max_ = maxoffdiag(A, &k, &l, n);
    // Uncomment below if you want to print outs
    // for(int i=0 ; i < n ; i++) {
    //     for(int j=0 ; j < n ; j++) {
    //         cout << A[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Max: " << max_ << endl;
    // cout << "===========" << endl;
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

  // print out eigenvalues
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
  for (int j=0; j<n; i++){
    sum += R[0][j]*R[1][j];
  }
} // end of jacobi__method function

// Function to update matrix elements
void rotate(double **A, double **R, int k, int l, int n){
  double tau, t, c, s;
  if (A[k][l] != 0.0){
    tau = (A[l][l]-A[k][k])/(2*A[k][l]);
    if (tau>=0){
      t = 1.0/(tau + sqrt(1.0 + tau*tau));
    } else {
      t = -1.0/(-tau + sqrt(1.0 + tau*tau));
    }

    c = 1/sqrt(1+t*t);
    s = t*c;
  } else {
    c = 1.0; s = 0.0;
  }

  double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
  a_kk = A[k][k];
  a_ll = A[l][l];
  A[k][k] = a_kk*c*c - 2*A[k][l]*c*s + a_ll*s*s;
  A[l][l] = a_ll*c*c + 2*A[k][l]*c*s + a_kk*s*s;
  A[k][l] = 0.0;
  A[l][k] = 0.0;
  for (int i=0; i<n; i++){
    if (i != k && i != l){
      a_ik = A[i][k];
      a_il = A[i][l];
      A[i][k] = a_ik*c - a_il*s;
      A[k][i] = A[i][k];
      A[i][l] = a_il*c + a_ik*s;
      A[l][i] = A[i][l];
    }
  // Compute new eigenvectors
  r_ik = R[i][k];
  r_il = R[i][l];
  R[i][k] = r_ik*c - r_il*s;
  R[i][l] = r_il*c + r_ik*s;
  }
} // end of function rotate

// Function for finding maximum off-diagonal element
double maxoffdiag(double **A, int *k, int *l, int n){
  double max = 0.0;
  for (int i=0; i<n; i++){
    for (int j=i+1; j<n; j++){
      if (fabs(A[i][j])>max){
        max = fabs(A[i][j]); *k = i; *l = j;
      }
    }
  }
  return max;
} // end of maxoffdiag function
