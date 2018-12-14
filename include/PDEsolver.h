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
  int N;
  double Time;
  int T;
  double dt;
  double dx;
  double alpha;
  double diag;
  double offDiag;
  double method;
  double *uNew;
  double *uOld;
  double **u;
  double u_i;
  double u_f;
  double *diagArray;
  double *Q4;
  // Initializers
  PDEsolver();
  PDEsolver(int N_, double dt_, double T_, double method_, double u_i_, double u_f_);
  ~PDEsolver();
  // Functions
  void forwardEuler();
  void tridiag();
  void tridiagHeat(int t);
  void solve();
  void solve2D();
  void output(ofstream &ofile);
  void analytical(double Time, int xPoints);
};

#endif /* PDESOLVER_H */
