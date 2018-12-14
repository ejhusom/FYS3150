#include "PDEsolver.h"
#include "PDEsolver2D.h"
#include "HeatEquation.h"
using namespace std;

int main(int argc, char *argv[]){

  double method = 1;
  int N = 100;
  double dt = 0.001;
  double Time = 0.03;
  int dimension = 3;
  int slab = 1;
  int radioactive = 1;


  switch (argc) {
    case 6: dimension = atoi(argv[5]);
    case 5: Time = atof(argv[4]);
    case 4: dt = atof(argv[3]);
    case 3: N = atoi(argv[2]);
    case 2: method = atof(argv[1]);
  }

  //1D diffusion equation
  if (dimension == 1) {
    PDEsolver problem = PDEsolver(N, dt, Time, method, 0.0, 1.0);
    problem.solve();
  }
  //2D diffusion equation
  if (dimension == 2) {
    PDEsolver2D problem = PDEsolver2D(N, dt, Time, method);
    problem.solve();
  }
  //2D heat equation
  if (dimension == 3) {
    PDEsolver problem1D = PDEsolver(100, 0.01, 1, 2, 0.0, 1);
    problem1D.solve();
    HeatEquation problem = HeatEquation(slab, radioactive);
    problem.solve(problem1D.u);


  }

  return 0;
}
