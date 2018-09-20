#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <armadillo>
#include "jacobi_method.h"

using namespace std;
using namespace arma;

void testcode(int n){
  // CREATING TOEPLITZ MATRIX
  double **A = new double*[n];   // toeplitz matrix
  double **R = new double*[n];   // matrix for storing eigenvectors
  for (int i = 0; i < n; i++){
    A[i] = new double[n];
    R[i] = new double[n];
  }
  // fill tridiagonal
  for(int i=0 ; i < n ; i++) {
      for(int j=0 ; j < n ; j++) {
          if(i==j){
            A[i][j] = 2.0;
            R[i][j] = 1.0;
          }
          // else if(i==j-1||i==j+1){
          else if(i==j-1||i==j+1){
            A[i][j] = -1.0;
            R[i][j] = 0.0;
          }
          else {
            A[i][j] = 0.0;
            R[i][j] = 0.0;
          }
      }
  }

  // SOLVING EQUATION
  jacobi_method(A,R,n);

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
  // UNIT TEST No. 1: Checking eigenvalues against analytical solution
  double lambda[n];
  double d = 2.0;
  double a = -1.0;
  // Computing analytical eigenvalues
  for (int j=1; j<n+1; j++){
    lambda[j-1] = d + 2*a*cos(j*acos(-1)/(n+1));
  }
  // Checking analytical eigenvalues against numerical eigenvalues
  double tolerance = 1e-10;
  for (int i=0; i<n; i++){
    if (fabs(eigenvalues[i]-lambda[i]) > tolerance){
      cout << "WARNING! Numerical eigenvalues not matching analytical eigenvalues" << endl;
      break;
    }
  }
  // Printing eigenvalues
  for (int i=0; i<n; i++){
    cout << setw(8) << setprecision(4) << lambda[i];
    cout << setw(8) << setprecision(4) << eigenvalues[i] << endl;
  }


  //=========================================================================
  // UNIT TEST No. 2: Checking orthogonality of eigenvectors.
  double sum = 0.0;
  for (int k=0; k<n; k++){
    for (int j=k; j<n; j++){
      for (int i=0; i<n; i++){
        sum += R[i][j]*R[i][j+1];
      }
    }
  }
  if (sum > tolerance){
    cout << "WARNING! Numerical eigenvectors not matching analytical eigenvectors" << endl;
  }
  // delete allocated memory
  for (int i = 0; i < n; i++){
    delete [] A[i];
    delete [] R[i];
  }
}
