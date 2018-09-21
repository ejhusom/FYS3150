/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         2.0
Description: For solving exercises in project 2, eigenvalue problems.
USAGE:
- Program takes number of mesh poitns as command line argument
- Compile by running "make" in terminal
- Unit tests are run by calling testcode(n) in the main function

TODO:
- Finish eigenarma-function

POTENTIAL IMPROVEMENTS:
- Move creation of matrix into jacobi_method.cpp, and send in the elements of
  the diagonals as arguments to the function
- Better structure of the unit tests, testcode.cpp
==============================================================================*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "jacobi_method.h"
#include "testcode.h"
#include "creatematrix.h"

using namespace std;

int main(int argc, char *argv[])
{
  // taking number of mesh points and rho_n as command line argument
  int n = atoi(argv[1]);
  double rho_n = atof(argv[2]);

  double V[n] = {0}; double Diag; double NonDiag;
  if (rho_n != 0){
    double h = rho_n/double(n+1);
    Diag = 2.0/(h*h);
    NonDiag = -1.0/(h*h);
    double rho[n];
    for (int i=0; i<n; i++){
      rho[i] = (i+1)*h;
      V[i] = rho[i]*rho[i];
    }
  } else {
    Diag = 2.0;
    NonDiag = -1.0;
  }

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

  for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){
        cout << setw(8) << setprecision(4) << A[i][j];
      }
    cout << endl;
  }


  //
  // // SOLVING EQUATION
  // jacobi_method(A,R,n);
  //
  // extracting the eigenvalues
  // double eigenvalues[n];
  // for(int i=0 ; i < n ; i++) {
  //   for(int j=0 ; j < n ; j++) {
  //     if(i==j){
  //       eigenvalues[i] = A[i][j];
  //     }
  //   }
  // }
  //
  // // ofstream outfile;
  // // outfile.open ("eigenvectors.dat");
  // // for (int i=0; i<n; i++){
  // //   outfile << setw(20) << setprecision(10) << eigenvalues[i];
  // //   for (int j=0; j<n; j++){
  // //     outfile << setw(20) << setprecision(10) << R[i][j];
  // //   }
  // //   outfile << endl;
  // // }
  // // outfile.close();
  //
  // sort(eigenvalues, eigenvalues + n);
  // // Printing eigenvalues
  // for (int i=0; i<4; i++){
  //   cout << setw(8) << setprecision(4) << eigenvalues[i] << endl;
  // }
  //
  //
  // // delete allocated memory
  // for (int i = 0; i < n; i++){
  //   delete [] A[i];
  //   delete [] R[i];
  // }

  return 0;
} // end of main function
