#ifndef PDESOLVER_H
#define PDESOLVER_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

class PDEsolver{


public:
  // Properties
  string methodName;
  // ofstream ofile;
  int N;
  double Time;
  int T;
  double dt;
  double dx;
  double alpha;
  double diag;
  double superDiag;
  double *uNew;
  double *uOld;
  // Initializers
  PDEsolver();
  PDEsolver(int N_, double dt_, int T_, double method);
  ~PDEsolver();
  // Functions
  void forwardEuler();
  void tridiag();
  void solve();
  void output(ofstream &ofile);
  void analytical(double Time);

};

#endif /* PDESOLVER_H */
