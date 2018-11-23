#include "PDEsolver.h"
using namespace std;

int main(int argc, char *argv[]){

  int N = 100;
  double dt = 0.00001;
  int Time = 1;
  double method = 0;

  switch (argc) {
    case 5: Time = atof(argv[4]);
    case 4: dt = atoi(argv[3]);
    case 3: N = atoi(argv[2]);
    case 2: method = atoi(argv[1]);
  }

  PDEsolver problem = PDEsolver(N, dt, Time, method);
  problem.solve();
  problem.analytical(Time);



  return 0;
}
