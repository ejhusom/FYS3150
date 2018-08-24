//==============================================================================
// Title:           FYS3150 Project 1
// Author:          Erik Johannes B. L. f. Husom
// Date:            2018-08-24
// Version:         0.1
// Description:     One-dimensional Poisson equation:
//                  -u''(x) = f(x)
//                  x = [0, 1]
//                  u(0) = u(1) = 0
//==============================================================================
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
ofstream dat1;

int main()
{
    int n = 10000;                   // number of mesh points
    double h = 1/double(n+1);         // step length

    // initialize arrays
    double *a = new double[n+2];    // sub-diagonal
    double *b = new double[n+2];      // main diagonal
    double *c = new double[n+2];    // super-diagonal
    double *f = new double[n+2];      // right-hand-side vector
    double *v = new double[n+2];      // numerical solution
    double *b_ = new double[n+2];     // adjusted diagonal
    double *f_ = new double[n+2];     // adjusted right-hand-side

    // filling f-array
    for (int i=1; i<(n+1); i++){
        f[i] = h*h*100*exp(-10*double(i)*h);
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

    // forward substitution
    for (int i=2; i<(n+1); i++){
        b_[i] = b[i] - a[i-1]*c[i-1]/b_[i-1];
        f_[i] = f[i] - a[i-1]*f_[i-1]/b_[i-1];
    }

//    cout << "f - f_ - b_" << endl;
//    // print out matrix
//    for (int i=0; i<(n+3); i++){
//        cout << setw(15) << setprecision(7) << f[i];
//        cout << setw(15) << setprecision(7) << f_[i];
//        cout << setw(15) << setprecision(7) << b_[i] << endl;
//    }

    // setting first and last v-value
    v[0] = 0;
    v[n] = f_[n]/b_[n];
    v[n+1] = 0;

    // backward substitution
    for (int i=n-1; i>0; i--){
        v[i] = (f_[i] - c[i]*v[i+1])/b_[i];
    }

    // analytical
    double *u = new double[n];
    for (int i=0; i<n; i++){
        u[i] = 1-(1-exp(-10))*(double(i)*h) - exp(-10*i*h);
    }

    // WRITING TO FILE
    ofstream dat1;
    dat1.open ("dat1.dat");
    for (int i=0; i<n; i++){
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

    return 0;
}
