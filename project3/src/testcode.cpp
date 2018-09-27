#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <armadillo>
#include <sys/ioctl.h>
#include "jacobi_method.h"

using namespace std;
using namespace arma;

// Function for testing the jacobi method
// Both unit tests have passed for tolerance >= 1e-13
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
  double timing; int it;
  jacobi_method(A,R,n,&timing,&it);

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

  // Get size of terminal for nice print formatting
  struct winsize size;
  ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
  for (int i = 0; i < size.ws_col; i++) {
    cout << "=";
  }
  cout << endl;
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
  double tolerance = 1e-13;
  double success = true;
  for (int i=0; i<n; i++){
    if (fabs(eigenvalues[i]-lambda[i]) > tolerance){
      cout << left << setw(35) << "TEST: correct eigenvalues";
      cout << left << " | \033[1;31mFAILED\033[0m" << endl;
      success = false;
      break;
    }
  }
  if (success){
    cout << left << setw(35) << "TEST: correct eigenvalues";
    cout << left << " | \033[1;32mPASSED\033[0m" << endl;
  }
  //=========================================================================
  // UNIT TEST No. 2: Checking orthogonality of eigenvectors.
  double sum; bool failure = false;
  for (int k=0; k<n; k++){
    for (int j=k; j<n; j++){
      sum = 0.0;
      for (int i=0; i<n; i++){
        sum += R[i][j]*R[i][j+1];
      }
      if (sum > tolerance){
        failure = true;
      }
    }
  }
  if (failure){
    cout << left << setw(35) << "TEST: orthogonality of eigenvectors",
    cout << left << " | \033[1;31mFAILED\033[0m" << endl;
  } else {
    cout << left << setw(35) << "TEST: orthogonality of eigenvectors",
    cout << left << " | \033[1;32mPASSED\033[0m" << endl;
  }

  // delete allocated memory
  for (int i = 0; i < n; i++){
    delete [] A[i];
    delete [] R[i];
  }
}
