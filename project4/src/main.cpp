/*=============================================================================
FYS3150 Project 4 by Erik Johannes B. L. G. Husom on 2018-10-25
Description:
- Periodic boundary conditions (PBC).
- Boltzmann constant = 1 -> temperature has dimension energy
- Coupling constant J = 1.
USAGE:
- Run executable with mpirun -n N ./runproject4.x, where N is the number of processes
=============================================================================*/
#include <chrono>
#include <sstream>
#include <mpi.h>
#include "metropolis.h"
#include "analytical.h"
using namespace std;
using namespace std::chrono;
ofstream outfile;

void output(int dim, double temperature, double *ExpecVal, int nCycles, double timing, int totalcounter);
void getEnergyAndMagnetization(double **Lattice, double ***PointerLattice, int dim, double *E, double *M);

int main(int argc, char *argv[]){

  int dim = 2;
  int state = 1; // 1: ordered initial state, else: random state
  int nCycles = 1000000;
  double temp_init = 2.0;
  double temp_final = 3.0;
  double temp_step = 0.1;

  switch (argc) {
    case 7: temp_step = atof(argv[6]);
    case 6: temp_final = atof(argv[5]);
    case 5: temp_init = atof(argv[4]);
    case 4: nCycles = atoi(argv[3]);
    case 3: state = atoi(argv[2]);
    case 2: dim = atoi(argv[1]);
  }

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0,1.0);

  double *ExpecVal = new double[5];
  double *TotalExpecVal = new double[5];
  for (int i = 0; i < 5; i++) TotalExpecVal[i] = 0;
  double timing; int counter; int totalcounter;
  high_resolution_clock::time_point t1;
  high_resolution_clock::time_point t2;

  double E, M;
  double **Lattice = new double*[dim+2];
  for (int i = 0; i < dim+2; i++){
    Lattice[i] = new double[dim+2];
  }
  double ***PointerLattice = new double**[dim+2];
  for (int i = 0; i < dim+2; i++){
    PointerLattice[i] = new double*[dim+2];
  }

  int nProcs, my_rank;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &nProcs);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  MPI_Bcast (&dim, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&temp_init, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast (&temp_final, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast (&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  int cycleInterval = nCycles/nProcs;
  int loopStart = my_rank*cycleInterval;
  int loopStop = (my_rank+1)*cycleInterval;

  if (my_rank == 0){
    outfile.open("Dim" + to_string(dim) + "State" + to_string(state) + "Cycles" + to_string(nCycles) + "T" + to_string(temp_init) + ".dat");
    outfile << setw(15) << setprecision(8) << "T";
    outfile << setw(15) << setprecision(8) << "E";
    outfile << setw(15) << setprecision(8) << "E2";
    outfile << setw(15) << setprecision(8) << "M";
    outfile << setw(15) << setprecision(8) << "M2";
    outfile << setw(15) << setprecision(8) << "M abs";
    outfile << setw(15) << setprecision(8) << "Chi";
    outfile << setw(15) << setprecision(8) << "C_V";
    outfile << setw(15) << setprecision(8) << "Run time";
    outfile << setw(15) << setprecision(8) << "Acceptations";
    outfile << setw(15) << setprecision(8) << "Cycle count" << endl;
  }
  for (double temperature = temp_init; temperature <= temp_final; temperature+=temp_step) {
    initializeLattice(Lattice, PointerLattice, dim, state, &E, &M, gen, distribution);
    for (int i = 0; i < 5; i++) ExpecVal[i] = 0;
    int counter = 0; int totalcounter = 0;
    if (my_rank==0) t1 = high_resolution_clock::now();
    metropolis(dim, state, loopStart, loopStop, temperature, &E, &M, ExpecVal, Lattice, PointerLattice, gen, distribution, &counter);
    for (int i=0; i<5; i++) MPI_Reduce(&ExpecVal[i], &TotalExpecVal[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&counter, &totalcounter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier (MPI_COMM_WORLD);
    if (my_rank==0) {
      t2 = high_resolution_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
      timing = time_span.count();
      output(dim, temperature, TotalExpecVal, nCycles, timing, totalcounter);
      cout << "T=" << temperature << " done...\n";
    }
  }
  outfile.close();

  // deallocate memory
  for (int i = 0; i < dim+2; i++){
    delete [] Lattice[i];
    delete [] PointerLattice[i];
  }
  delete [] Lattice;
  delete [] PointerLattice;
  delete [] ExpecVal;
  delete [] TotalExpecVal;

  printAnalytical();

  MPI_Finalize ();
  return 0;
} // end of main function

void output(int dim, double temperature, double *ExpecVal, int nCycles, double timing, int totalcounter){
  for (int i = 0; i < 5; i++) ExpecVal[i] /= nCycles;
  double E_variance = (ExpecVal[1] - ExpecVal[0]*ExpecVal[0])/dim/dim;
  double M_variance = (ExpecVal[3] - ExpecVal[4]*ExpecVal[4])/dim/dim;
  outfile << setw(15) << setprecision(8) << temperature;
  outfile << setw(15) << setprecision(8) << ExpecVal[0]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[1]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[2]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[3]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[4]/dim/dim;
  outfile << setw(15) << setprecision(8) << M_variance/temperature;
  outfile << setw(15) << setprecision(8) << E_variance/(temperature*temperature);
  outfile << setw(15) << setprecision(8) << timing;
  outfile << setw(15) << setprecision(8) << totalcounter;
  outfile << setw(15) << setprecision(8) << nCycles << endl;
}

void getEnergyAndMagnetization(double ***PointerLattice, int dim, double *E, double *M){
  *E = 0;
  *M = 0;
  for(int i=1 ; i < dim+1 ; i++) {
    for(int j=1 ; j < dim+1 ; j++) {
      *E -= *PointerLattice[i][j]*(*PointerLattice[i+1][j]+*PointerLattice[i][j+1]);
      *M += *PointerLattice[i][j];
    }
  }
}
