#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include "maxoffdiag.h"
#include "rotate.h"

using namespace std;
using namespace std::chrono;

void jacobi_method(double **A, double **R, int n, double *timing, int *it){
  int k, l;
  double tolerance = 1e-10;
  double max_iterations = double(n)*double(n)*double(n);
  int iterations = 0;
  double max_ = maxoffdiag(A, &k, &l, n);

  // Computing eigenvalues (with timing)
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  while (max_ > tolerance && iterations < max_iterations){
    max_ = maxoffdiag(A, &k, &l, n);
    rotate(A, R, k, l, n);
    iterations++;
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  // Return timing of algorithm and number of iterations
  *timing = double(time_span.count());
  *it = iterations;
} // end of jacobi__method function
