/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         0.1
Description: For solving exercises in project 2.
USAGE:
Compile with: c++ -o project2.exe project2.cpp -Wall -larmadillo (if using armadillo functions)
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "time.h"
#include <armadillo>
using namespace std;
using namespace arma;

void rotate(double **A, int k, int l, int n);
double maxoffdiag(double **A, int *k, int *l, int n);

void jacobi_method(){
  int n = 4;
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

  for(int i=0 ; i < n ; i++) {
      for(int j=0 ; j < n ; j++) {
          if(i==j){
              A[i][j] = 2.0;
          }
          else if(i==j-1||i==j+1){
              A[i][j] = -1.0;
          }
          cout << A[i][j] << " ";
      }
      cout << endl;
  }
  int k, l;
  double tolerance = 1e-10;
  // double max_iterations = double(n)*double(n)*double(n);
  // int iterations = 0;
  double max_ = maxoffdiag(A, &k, &l, n);
  while (max_ > tolerance){ // && iterations < max_iterations){
    max_ = maxoffdiag(A, &k, &l, n);
    rotate(A, k, l, n);
    // iterations++;
  }

  cout << "=========" << endl;
  cout << "Result matrix:" << endl;
  for(int i=0 ; i < n ; i++) {
      for(int j=0 ; j < n ; j++) {
          cout << A[i][j] << " ";
      }
      cout << endl;
  }
  delete [] A;
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


int main(int argc, char *argv[])
{

  // generate random symmetric matrix
  // int n = 2;
  // mat T = randu<mat>(n,n);
  // mat A = symmatu(T);
  // A.print();

  jacobi_method();

  // creating tridiagonal matrix
  int n = 4;
  vec main = 2*ones<vec>(n);
  vec sub = -1*ones<vec>(n-1);
  vec super = -1*ones<vec>(n-1);
  mat A_ = diagmat(main);
  mat B = diagmat(super,1);
  mat C = diagmat(sub,-1);
  A_ = A_+B+C;
  // test
  // A_.print();
  cout << "========" << endl;
  cout << eig_sym(A_);

  return 0;
} // end of main function
