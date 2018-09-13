/*==============================================================================
Title:           FYS3150 Project 2 - Eigenvalue Problems
Author:          Erik Johannes B. L. G. Husom
Date:            2018-09-13
Version:         0.1
Description: For solving exercises in project 2.
USAGE:
Compile with: c++ project2.cpp -o project2.exe -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "time.h"
#include <armadillo>
using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{
  // creating tridiagonal matrix
  // int n = 5;
  // vec main = 2*ones<vec>(n);
  // vec sub = -1*ones<vec>(n-1);
  // vec super = -1*ones<vec>(n-1);
  // mat A = diagmat(main);
  // mat B = diagmat(super,1);
  // mat C = diagmat(sub,-1);
  // A = A+B+C;
  // // test
  // A.print();

  // generate random symmetric matrix
  // int n = 2;
  // mat T = randu<mat>(n,n);
  // mat A = symmatu(T);
  // A.print();
  int n = 3;
  mat A = randu<mat>(n,n);

  double tolerance = 1e-8;
  double max;
  for (int i=0; i<n; i++){
    for int j=0; i<n; j++){
      if (i!=j){
        if (fabs(A(i,j)))>max){
          max = fabs(A(i,j)); k = i; l = j;
        }
      }
    }
  }
  

  return 0;
} // end of main function

void jacobi_method(){

} // end of jacobi__method function
