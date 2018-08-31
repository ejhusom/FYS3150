//==============================================================================
// Title:           FYS3150 Project 1, task 1e
// Author:          Erik Johannes B. L. G. Husom (adapted from Morten)
// Date:            2018-08.31
// Version:         0.1
// Description: Using Armadillo and LUL decomposition for comparing the results in the other tasks.
//==============================================================================
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

int main()
{
    mat A = randu<mat>(5,5);
    vec b = randu<vec>(5);

    A.print("A =");
    b.print("b=");
    // solve Ax = b
    vec x = solve(A,b);
    // print x
    x.print("x=");
    // find LU decomp of A, if needed, P is the permutation matrix
    mat L, U;
    lu(L,U,A);
    // print l
    L.print(" L= ");
    // print U
    U.print(" U= ");
    //Check that A = LU
    (A-L*U).print("Test of LU decomposition");
    return 0;
}
