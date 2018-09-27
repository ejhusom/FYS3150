#include "odesolver.h"

void odesolver::VelocityVerlet(int meshpoints, double time_f){
  double h = time_f/meshpoints; // time step
  double h2 = h/2;
  double hh2 = h*h/2;
  // Arrays for position, velocity and acceleration
  double *x = new double[meshpoints];
  double *v = new double[meshpoints];
  double *a = new double[meshpoints];
  // Intial conditions
  x[0] = 0;
  v[0] = 0;
  // The Velocity Verlet Method
  for (int i = 0; i < meshpoints; i++) {
    x[i+1] = x[i] + h*v[i] + a[i]*hh2;
    a[i+1] = x[i+1]; // TODO: NOT SURE WHAT TO DO HERE!!!
    v[i+1] = v[i] + h2*(a[i+1] + a[i]);
  }

  delete [] x;
  delete [] v;
  delete [] a;

} // end of function function
