//==============================================================================
// Title:           FYS3150 Project 1
// Author:          Erik Johannes B. L. f. Husom
// Date:            2018-08-24
// Version:         0.1
// Description:     One-dimensional Poisson-equation:
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
    int n = 1000; // number of mesh points
    double h = 1/double(n);

    // initialize arrays
    double *a = new double[n-1];
    double *b = new double[n];
    double *c = new double[n-1];
    double *f = new double[n];
    double *v = new double[n];
    double *b_ = new double[n];
    double *f_ = new double[n];

    // filling f array
    for (int i=0; i<n; i++){
        f[i] = h*h*100*exp(-10*(double(i)*h));

    }

    // filling tridiagonal matrix
    for (int i=0; i<n; i++){
        b[i] = 2;
    }
    b_[0] = b[0];

    for (int i=0; i<(n-1); i++){
        a[i] = -1;
        c[i] = -1;
    }

    // forward substitution
    for (int i=1; i<n; i++){
        b_[i] = b[i] - a[i-1]*c[i-1]/b_[i-1];
        f_[i] = f[i] - a[i-1]*f[i-1]/b_[i-1];
    }

    // setting first and last v-value
    v[0] = 0;
    v[n-1] = f_[n-1]/b_[n-1];

    // backward substitution
    for (int i=n-2; i>0; i--){
        v[i] = (f_[i] - c[i]*v[i+1])/b_[i];
    }

    // analytical
    double *u = new double[n];
    for (int i=0; i<n; i++){
        u[i] = 1-(1-exp(-10))*(double(i)*h) - exp(-10*i*h);
    }

    ofstream dat1;
    dat1.open ("dat1.dat");
    // print out the arrays
    for (int i=0; i<n; i++){
        dat1 << setw(15) << setprecision(7) << h*i;
        dat1 << setw(15) << setprecision(7) << v[i];
        dat1 << setw(15) << setprecision(7) << u[i] << endl;
    }
    cout << "done";
    dat1.close();

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
