//==============================================================================
// Title:           FYS3150 Project 1 - General Algorithm
// Author:          Erik Johannes B. L. f. Husom
// Date:            2018-08-30
// Version:         1.0
// Description:     One-dimensional Poisson equation:
//                  -u''(x) = f(x)
//                  x = [0, 1]
//                  u(0) = u(1) = 0
//
//                  This program gives a general algorithm for a tridiagonal
//                  matrix which can have any elements on the super-, sub- and
//                  lead diagonals
//==============================================================================
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "time.h"
using namespace std;
ofstream dat1;

void genalgo(int n){

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
    }
    b_[1] = b[1];       // setting first element of adjusted diagonal

    for (int i=1; i<(n); i++){
        a[i] = -1.;
        c[i] = -1.;
    }

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

    // WRITING TO FILE
    dat1.open ("genalgo.dat");
    for (int i=0; i<n+2; i++){
        dat1 << setw(15) << setprecision(7) << h*i;
        dat1 << setw(15) << setprecision(7) << v[i];
        dat1 << setw(15) << setprecision(7) << u[i] << endl;
    }
    dat1.close();

    // deleting from memory
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] f;
    delete [] v;
    delete [] b_;
    delete [] f_;
    delete [] u;

}


void specalgo(int n){

    double h = 1/double(n+1);           // step length

    // initialize arrays
    double *f = new double[n+2];        // right-hand-side vector
    double *v = new double[n+2];        // numerical solution
    double *b_ = new double[n+2];       // adjusted diagonal
    double *f_ = new double[n+2];       // adjusted right-hand-side
    double *eps = new double[n+2];      // relative error

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

    eps[0] = 0.0;
    for (int i=1; i<n+2; i++){
        temp =
        eps[i] = log10(fabs((v[i]-u[i])/u[i]));
        if eps[]
    }



    // WRITING TO FILE
    dat1.open ("specalgo.dat");
    for (int i=0; i<n+2; i++){
        dat1 << setw(15) << setprecision(7) << h*i;
        dat1 << setw(15) << setprecision(7) << v[i];
        dat1 << setw(15) << setprecision(7) << u[i];
        dat1 << setw(15) << setprecision(7) << eps[i] << endl;
    }
    dat1.close();

    // deleting from memory
    delete [] f;
    delete [] v;
    delete [] b_;
    delete [] f_;
    delete [] u;
    delete [] eps;

}


int main(int argc, char* argv[])
{

    int n = atoi(argv[1]);                    // number of mesh points

    cout << "Generalized algorithm:" << endl;
    genalgo(n);

    cout << "Specialized algorithm:" << endl;

    specalgo(n);

    return 0;
}
