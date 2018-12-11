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


  switch (argc) {
    case 6: dimension = atoi(argv[5]);
    case 5: Time = atof(argv[4]);
    case 4: dt = atof(argv[3]);
    case 3: N = atoi(argv[2]);
    case 2: method = atof(argv[1]);
  }

  if (dimension == 1) {
    PDEsolver problem = PDEsolver(N, dt, Time, method, 0.0, 1.0);
    problem.solve();
  }
  if (dimension == 2) {
    PDEsolver2D problem = PDEsolver2D(N, dt, Time, method);
    problem.solve();
  }
  if (dimension == 3) {
    PDEsolver problem1D = PDEsolver(100, 0.01, 1, 2, 0.0, 1);
    problem1D.solve();
    HeatEquation problem = HeatEquation(slab);
    problem.solve(problem1D.u);
    //
    // double *bc;
    // bc = new double[problem.Ny + 2];
    // for (int i=0; i<N; i++){
    //   bc[i] = problem.uNew[int((problem.Ny + 2)/2)][i];
    // }
    //
    // HeatEquation problem2 = HeatEquation(bc);
    // problem2.solve();
  }

  return 0;
}
