/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         1.0
Description: For solving exercises in project 2.
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

void jacobi_method(int n);
void rotate(double **A, int k, int l, int n);
double maxoffdiag(double **A, int *k, int *l, int n);

int main(int argc, char *argv[])
{ // taking number of mesh points as command line argument
  int n = atoi(argv[1]);
  jacobi_method(n);
  return 0;
} // end of main function

void jacobi_method(int n){
  double **A;
  A = new double*[n];
  for (int i = 0; i < n; i++){
    A[i] = new double[n];
  }
  // initialize all elements to 0.0
  for (int i=0; i<n; i++) {
      for(int j=0 ; j< n ; j++){
          A[i][j] = 0.0;
      }
  }
  // fill tridiagonal (also printing the matrix)
  for(int i=0 ; i < n ; i++) {
      for(int j=0 ; j < n ; j++) {
          if(i==j){
              A[i][j] = 2.0;
          }
          else if(i==j-1||i==j+1){
              A[i][j] = -1.0;
          }
          // cout << A[i][j] << " ";
      }
      // cout << endl;
  }

  

  int k, l;
  double tolerance = 1e-10;
  double max_iterations = double(n)*double(n)*double(n);
  int iterations = 0;
  double max_ = maxoffdiag(A, &k, &l, n);

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  while (max_ > tolerance && iterations < max_iterations){
    max_ = maxoffdiag(A, &k, &l, n);
    rotate(A, k, l, n);
    iterations++;
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  cout << "Time used: " << time_span.count() << " seconds." << endl;

  cout << "Number of iterations:" << iterations << endl;

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
  delete [] A;

  // Checking against armadillo
  vec main = 2*ones<vec>(n);
  vec sub = -1*ones<vec>(n-1);
  vec super = -1*ones<vec>(n-1);
  mat A_ = diagmat(main);
  mat B = diagmat(super,1);
  mat C = diagmat(sub,-1);
  A_ = A_+B+C;

  cout << "=========" << endl;
  cout << setw(12) << setprecision(6) << "Calc. eig.";
  cout << setw(12) << setprecision(6) << "Arma. eig." << endl;
  for (int i=0; i<n; i++){
    cout << setw(12) << setprecision(6) << eigenvalues[i];
    cout << setw(12) << setprecision(6) << eig_sym(A_)[i] << endl;
  }
} // end of jacobi__method function

// Function to update matrix elements
void rotate(double **A, int k, int l, int n){
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

  double a_kk, a_ll, a_ik, a_il;
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
