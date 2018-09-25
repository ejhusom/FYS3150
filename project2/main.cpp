/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         2.0
Description: For solving exercises in project 2, eigenvalue problems.
USAGE:
Compile by running "make" in terminal
The executable can be run with no or several command line arguments:
- No cmd arg: Running tests and giving usage information
- First cmd arg: Number of mesh points.
- Second cmd arg: rho_Max, spherical coordinates, (optional).
- Third cmd arg: omega, strength of oscillator potential, (optional).

TODO: Plot psi
TODO: Check eigenvalues 2e

POTENTIAL IMPROVEMENTS:
==============================================================================*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "jacobi_method.h"
#include "testcode.h"
#include "eigenarma.h"

using namespace std;

int main(int argc, char *argv[]){
  // Taking command line arguments
  int n = 0; double rho_n = 0; double omega = 0;
  struct winsize size;
  ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
  switch (argc) {
    case 1: for (int i = 0; i < size.ws_col; i++) cout << "=";
            cout << endl;
            cout << "USAGE:" << endl;
            cout << "- No cmd arg: Running tests" << endl;
            cout << "- 1. cmd arg: Number of mesh points" << endl;
            cout << "- 2. cmd arg: rho_Max, spherical coordinates (optional)" << endl;
            cout << "- 3. cmd arg: omega, strength of oscillator potential (optional)" << endl;
            testcode(10);
            return 0;
    case 4: omega = atof(argv[3]);
    case 3: rho_n = atof(argv[2]);
    case 2: n = atoi(argv[1]);
  }

  // Initialize parameters
  double V[n] = {0}; double rho[n] = {0};
  double Diag; double NonDiag;
  if (rho_n != 0){
    double h = rho_n/double(n+1);
    Diag = 2.0/(h*h);
    NonDiag = -1.0/(h*h);
    for (int i=0; i<n; i++){
      rho[i] = (i+1)*h;
      V[i] = rho[i]*rho[i];
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
  double **A = new double*[n];
  double **R = new double*[n];
  for (int i = 0; i < n; i++){
    A[i] = new double[n];
    R[i] = new double[n];
  }
  // fill tridiagonal
  for(int i=0 ; i < n ; i++) {
      for(int j=0 ; j < n ; j++) {
          if(i==j){
            A[i][j] = Diag + V[i];
            R[i][j] = 1.0;
          }
          else if(i==j-1||i==j+1){
            A[i][j] = NonDiag;
            R[i][j] = 0.0;
          }
          else {
            A[i][j] = 0.0;
            R[i][j] = 0.0;
          }
      }
  }

  // SOLVING EQUATION
  double timing; int it; double timing_arma; double eigs[n];
  // Finding eigenvalues with Jacobi method
  jacobi_method(A,R,n,&timing,&it);
  // Finding eigenvalues with Armadillo
  eigenarma(n,eigs,rho_n,omega,&timing_arma);

  // Extracting and sorting the eigenvalues from Jacobi method
  double eigenvalues[n];
  for(int i=0 ; i < n ; i++) {
    for(int j=0 ; j < n ; j++) {
      if(i==j){
        eigenvalues[i] = A[i][j];
      }
    }
  }
  sort(eigenvalues, eigenvalues + n);

  // Printing results
  for (int i = 0; i < size.ws_col; i++) cout << "=";
  cout << "Three first eigenvalues\n";
  cout << setw(12) << "Jacobi" << setw(12) << "Arma." << endl;
  for (int i=0; i<4; i++){
    cout << setw(12) << setprecision(5) << eigenvalues[i] << setw(12) << setprecision(5) << eigs[i] << endl;
  }
  for (int i = 0; i < size.ws_col; i++) cout << "-";
  cout << "Timing\n";
  cout << setw(12) << "Jacobi" << setw(12) << "Arma." << endl;
  cout << setw(12) << setprecision(4) << timing << setw(12) << setprecision(4) << timing_arma << endl;
  for (int i = 0; i < size.ws_col; i++) cout << "-";
  cout << "Number of iterations (Jacobi): " << it << endl;

  // delete allocated memory
  for (int i = 0; i < n; i++){
    delete [] A[i];
    delete [] R[i];
  }

  return 0;
} // end of main function
