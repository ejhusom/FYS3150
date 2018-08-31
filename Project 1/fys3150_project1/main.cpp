//==============================================================================
// Title:           FYS3150 Project 1 - General Algorithm
// Author:          Erik Johannes B. L. G. Husom
// Date:            2018-08-30
// Version:         1.0
// Description:     One-dimensional Poisson equation:
//                  -u''(x) = f(x)
//                  x = [0, 1]
//                  u(0) = u(1) = 0
//
// The program gives a general and a specific algorithm for solving the equation,
// in addition to computing the error for the specific algorithm.
//==============================================================================
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "time.h"
using namespace std;
ofstream dat1;

void genalgo(int n, int print){

    double h = 1/double(n+1);           // step length

    // initialize arrays
    double *a = new double[n+2];        // sub-diagonal
    double *b = new double[n+2];        // main diagonal
    double *c = new double[n+2];        // super-diagonal
    double *f = new double[n+2];        // right-hand-side vector
    double *v = new double[n+2];        // numerical solution
    double *b_ = new double[n+2];       // adjusted diagonal
    double *f_ = new double[n+2];       // adjusted right-hand-side

    // filling f-array
    double hh100 = h*h*100.0;
    double h10 = 10*h;
    for (int i=1; i<(n+1); i++){
        f[i] = hh100*exp(-h10*i);
    }
    f_[1] = f[1];       // setting first element of adjusted right-hand-side

    // filling tridiagonal matrix
    for (int i=1; i<(n+1); i++){
        b[i] = 2.;
        a[i] = -1.;
        c[i] = -1.;
    }
    b_[1] = b[1];       // setting first element of adjusted diagonal


    clock_t start, finish;
    start = clock();

    // forward substitution
    for (int i=2; i<(n+1); i++){
        double temp = a[i-1]/b_[i-1];   // reducing one FLOP
        b_[i] = b[i] - temp*c[i-1];
        f_[i] = f[i] - temp*f_[i-1];
    }

    // setting first and last v-value
    v[0] = 0;
    v[n] = f_[n]/b_[n];
    v[n+1] = 0;

    // backward substitution
    for (int i=n-1; i>0; i--){
        v[i] = (f_[i] - c[i]*v[i+1])/b_[i];
    }

    finish = clock();
    double timeused = (double) (finish - start)/(CLOCKS_PER_SEC );
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(10) << setw(20) << "Time used= " << timeused  << endl;

    // analytical
    double *u = new double[n+2];
    for (int i=0; i<n+2; i++){
        u[i] = 1-(1-exp(-10))*(double(i)*h) - exp(-10*i*h);
    }

    // relative error function
    double *eps = new double[n+2];
    for (int i=0; i<n+2; i++){
        eps[i] = log10(fabs((v[i]-u[i])/u[i]));
    }
    eps[n+1] = 0.0;

    // WRITING TO FILE
    if (print>0){
        dat1.open ("genalgo.dat");
        for (int i=0; i<n+2; i++){
            dat1 << setw(30) << setprecision(15) << h*i;
            dat1 << setw(30) << setprecision(15) << u[i];
            dat1 << setw(30) << setprecision(15) << v[i];
            dat1 << setw(30) << setprecision(15) << eps[i] << endl;
        }
        dat1.close();
    }

    // deleting from memory
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] f;
    delete [] v;
    delete [] b_;
    delete [] f_;
    delete [] u;
    delete [] eps;

}


double specalgo(int n, int print){

    double h = 1/double(n+1);           // step length

    // initialize arrays
    double *f = new double[n+2];        // right-hand-side vector
    double *v = new double[n+2];        // numerical solution
    double *b_ = new double[n+2];       // adjusted diagonal
    double *f_ = new double[n+2];       // adjusted right-hand-side

    // filling f-array
    double hh100 = h*h*100.;
    double h10 = h*10;
    for (int i=1; i<(n+1); i++){
        f[i] = hh100*exp(-i*h10);
    }
    f_[1] = f[1];       // setting first element of adjusted right-hand-side

    b_[1] = 2.0;       // setting first element of adjusted diagonal

    clock_t start, finish;
    start = clock();

    // forward substitution
    for (int i=2; i<(n+1); i++){
        b_[i] = 2 - 1/b_[i-1];
        f_[i] = f[i] + f_[i-1]/b_[i-1];
    }

    // setting first and last v-value
    v[0] = 0;
    v[n] = f_[n]/b_[n];
    v[n+1] = 0;


    // backward substitution
    for (int i=n-1; i>0; i--){
        v[i] = (f_[i] + v[i+1])/b_[i];
    }
    finish = clock();
    double timeused = (double) (finish - start)/(CLOCKS_PER_SEC );
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(10) << setw(20) << "Time used= " << timeused  << endl;

    // analytical
    double *u = new double[n+2];
    for (int i=0; i<n+2; i++){
        u[i] = 1-(1-exp(-10))*(i*h) - exp(-h10*i);
    }

    // relative error function
    double *eps = new double[n+2];
    double e_max = -pow(10,6);
    for (int i=0; i<n+1; i++){
        eps[i] = log10(fabs((v[i]-u[i])/u[i]));
        if(eps[i]>e_max){
            e_max = eps[i];
        }
    }
    eps[n+1] = 0.0;


    // WRITING TO FILE
    if (print>0){
            dat1.open ("specalgo.dat");
            for (int i=0; i<n+2; i++){
                dat1 << setw(30) << setprecision(15) << h*i;
                dat1 << setw(30) << setprecision(15) << u[i];
                dat1 << setw(30) << setprecision(15) << v[i];
                dat1 << setw(30) << setprecision(15) << eps[i] << endl;
            }
            dat1.close();
    }

    // deleting from memory
    delete [] f;
    delete [] v;
    delete [] b_;
    delete [] f_;
    delete [] u;
    delete [] eps;

    return e_max;

}

// Compute the maximum error for different steplengths
void epsilons(){
    double *epsilons = new double[7];
    for (int i=0; i<8; i++){
        int n = int(pow(10,i));
        epsilons[i] = specalgo(n,0);
    }

    // write to file
    dat1.open ("epsilons.dat");
    for (int i=1; i<8; i++){
        int n = int(pow(10,i));
        double h = 1/(double(n)+1);
        dat1 << setw(20) << setprecision(10) << log10(h);
        dat1 << setw(20) << setprecision(10) << epsilons[i] << endl;
    }
    dat1.close();

    delete [] epsilons;
}

/*
** The function
**       ludcmp()
** takes as input a two-dimensional matrix a[][] of dimension n and
** replaces it by the LU decomposition of a rowwise permutation of
** itself. The results is stored in a[][] in the form given by
** eq. (2.3.14) in "Numerical Recipe", sect. 2.3, page 45. The vector
** indx[] records the row permutation effected by the partial pivoting;
** d is output as +1 or -1 depending on whether the number of row
** interchanges was even or odd, respectively. This routine is used in
** combination with the function lubksb() to solve linear equations or
** invert a matrix. The function is slightly modified from the version
** in in Numerical recipe and uses memory allocation functions in the
** present module.
*/

void ludcmp(double **a, int n, int *indx, double *d)
{
int      i, imax, j, k;
double   big, dum, sum, temp, *vv;

vv = new(nothrow) double [n];
if(!vv) {
printf("\n\nError in function ludcm():");
printf("\nNot enough memory for vv[%d]\n",n);
exit(1);
}

*d = 1.0;                              // no row interchange yet
for(i = 0; i < n; i++) {     // loop over rows to get scaling information
  big = 0.0;
  for(j = 0; j < n; j++) {
     if((temp = fabs(a[i][j])) > big) big = temp;
  }
  if(big == 0.0) {
     printf("\n\nSingular matrix in routine ludcmp()\n");
     exit(1);
  }
  vv[i] = 1.0/big;                 // save scaling */
} // end i-loop */

for(j = 0; j < n; j++) {     // loop over columns of Crout's method
  for(i = 0; i< j; i++) {   // not i = j
     sum = a[i][j];
 for(k = 0; k < i; k++) sum -= a[i][k]*a[k][j];
 a[i][j] = sum;
  }
  big = 0.0;   // initialization for search for largest pivot element
  for(i = j; i< n; i++) {
     sum = a[i][j];
 for(k = 0; k < j; k++) sum -= a[i][k]*a[k][j];
 a[i][j] = sum;
 if((dum = vv[i]*fabs(sum)) >= big) {
    big = dum;
    imax = i;
 }
  } // end i-loop
  if(j != imax) {    // do we need to interchange rows ?
     for(k = 0;k< n; k++) {       // yes
    dum        = a[imax][k];
    a[imax][k] = a[j][k];
    a[j][k]    = dum;
 }
 (*d)    *= -1;            // and change the parit of d
 vv[imax] = vv[j];         // also interchange scaling factor
  }
  indx[j] = imax;
  if(fabs(a[j][j]) < 0.0)  a[j][j] = 0.0;

    /*
    ** if the pivot element is 0.0 the matrix is singular
    ** (at least to the precision of the algorithm). For
    ** some application of singular matrices, it is desirable
    ** to substitute 0.0 for 0.0,
    */

  if(j < (n - 1)) {                   // divide by pivot element
     dum = 1.0/a[j][j];
 for(i=j+1;i < n; i++) a[i][j] *= dum;
  }
} // end j-loop over columns

delete [] vv;   // release local memory

}  // End: function ludcmp()

/*
** The function
**             lubksb()
** solves the set of linear equations A X = B of dimension n.
** a[][] is input, not as the matrix A[][] but rather as
** its LU decomposition, determined by the function ludcmp(),
** indx[] is input as the permutation vector returned by
** ludcmp(). b[] is input as the right-hand side vector B,
** The solution X is returned in B. The input data a[][],
** n and indx[] are not modified. This routine take into
** account the possibility that b[] will begin with many
** 0.0 elements, so it is efficient for use in matrix
** inversion.
** The function is slightly modified from the version in
** in Numerical recipe.
*/

void lubksb(double **a, int n, int *indx, double *b)
{
int        i, ii = -1, ip, j;
double     sum;

for(i = 0; i< n; i++) {
  ip    = indx[i];
  sum   = b[ip];
  b[ip] = b[i];
  if(ii > -1)   for(j = ii; j < i; j++) sum -= a[i][j] * b[j];
  else if(sum) ii = i;
  b[i] = sum;
}
for(i = n - 1; i >= 0; i--) {
  sum = b[i];
  for(j = i+1; j < n; j++) sum -= a[i][j] * b[j];
  b[i] = sum/a[i][i];
}
} // End: function lubksb()

int main(int argc, char* argv[])
{

//    int n = atoi(argv[1]);                    // number of mesh points

//    cout << "Generalized algorithm:" << endl;
//    genalgo(n,1);

//    cout << "Specialized algorithm:" << endl;
//    specalgo(n,1);

//    epsilons();


    int N = 5;
    double **A;
    A = new double*[N];
    //   initialize all elements to 0.0
    for(int i=0; i<N; i++) {
        for(int j=0 ; j< N ; j++){
            A[i][j] = 0.0;
        }
    }
    for(int i=0 ; i < N ; i++) {
        for(int j=0 ; j < N ; j++) {
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


//    int nArray[5];
//    for (int i=0; i<N; i++){
//        nArray[i] = 1;
//    }

    // filling f-array
    double *f = new double[N];
    double h = 1/N;
    double hh100 = h*h*100.0;
    double h10 = 10*h;
    for (int i=1; i<(N+1); i++){
        f[i] = hh100*exp(-h10*i);
    }

//    ludcmp(A, N, nArray, f);

    cout << "end" << endl;

//    return 0;
}
