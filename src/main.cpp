#include "PDEsolver.h"
#include "PDEsolver2D.h"
using namespace std;

int main(int argc, char *argv[]){

  double method = 1;
  int N = 100;
  double dt = 0.001;
  double Time = 0.03;
  int dimension = 2;

  switch (argc) {
    case 6: dimension = atoi(argv[5]);
    case 5: Time = atof(argv[4]);
    case 4: dt = atof(argv[3]);
    case 3: N = atoi(argv[2]);
    case 2: method = atof(argv[1]);
  }

  if (dimension == 1) {
    PDEsolver problem = PDEsolver(N, dt, Time, method);
    problem.solve();
  }
  if (dimension == 2) {
    // int nProcs, myRank;
    // MPI_Init(&argc, &argv);
    // MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
    // MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    PDEsolver2D problem = PDEsolver2D(N, dt, Time, method);
    problem.solve();
    // MPI_Finalize();
  }



  // problem.analytical(Time);



  //snakket litt med morten ang implicit og crank. Implicit skal bare løses akkurat som prosjekt 1 (med tridiag),
  //mens crank er en kombinasjon av forward og tridiag. Så for crank må u(x,t) først itereres over av forward,
  //også av tridiag, akkurat som i python eksempelkoden i python.
  // Ligningen i crank er (2 + alpha B) V_{j} = (2 - alpha B) V_{j-1}. så man løser først høyre side med forward,
  //slik at ligningen kommer på samme form som implicit (altså formen Av = f, hvor v er eneste ukjente), og den videre kan løses
  //med tridiag.
  //
  //python koden:
  //def crank_nicolson(alpha,u,N,T):
    // """
    // Implents crank-nicolson scheme, reusing code from forward- and backward euler
    // """
    // for t in xrange(1,T):
    //     forward_step(alpha/2,u[t],u[t-1],N)
    //     tridiag(alpha/2,u[t],N)

  return 0;
}
