/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         2.0
Description: For solving exercises in project 2, eigenvalue problems.
USAGE:
- Program takes number of mesh poitns as command line argument
- Compile by running "make" in terminal

POTENTIAL IMPROVEMENTS:
- Better structure of the two unit tests in jacobi_method.cpp
==============================================================================*/
#include "jacobi_method.h"

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
      }
  }

  jacobi_method(A,R,n);

  // delete allocated memory
  for (int i = 0; i < n; i++) delete [] A[i];

  return 0;
} // end of main function
