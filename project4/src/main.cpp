/*=============================================================================
FYS3150 Project 4 by Erik Johannes B. L. G. Husom on 2018-10-25
Description:
- Periodic boundary conditions (PBC).
- Boltzmann constant = 1 -> temperature has dimension energy
- Coupling constant J = 1.
USAGE:
- Run executable with mpirun -n 10 ./runproject4.x, where n is the number of processes
=============================================================================*/
#include "metropolis.h"
#include "analytical.h"
using namespace std;
ofstream outfile;

void output(int dim, double temperature, double *ExpecVal, int nCycles, double timing){
  for (int i = 0; i < 5; i++) ExpecVal[i] /= nCycles;
  double E_variance = (ExpecVal[1] - ExpecVal[0]*ExpecVal[0])/dim/dim;
  double M_variance = (ExpecVal[3] - ExpecVal[2]*ExpecVal[2])/dim/dim;
  outfile << setw(15) << setprecision(8) << temperature;
  outfile << setw(15) << setprecision(8) << ExpecVal[0]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[1]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[2]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[3]/dim/dim;
  outfile << setw(15) << setprecision(8) << ExpecVal[4]/dim/dim;
  outfile << setw(15) << setprecision(8) << M_variance/temperature;
  outfile << setw(15) << setprecision(8) << E_variance/(temperature*temperature);
  outfile << setw(15) << setprecision(8) << timing;
  outfile << setw(15) << setprecision(8) << nCycles << endl;
}

int main(int argc, char *argv[]){

  int dim = 2;
  int state = 1; // 1: ordered initial state, else: random state
  int nCycles = 1000000;
  double temp_init = 4.0;
  double temp_final = 2.0;
  double temp_step = 0.02;

  switch (argc) {
    case 7: temp_step = atof(argv[6]);
    case 6: temp_final = atof(argv[5]);
    case 5: temp_init = atof(argv[4]);
    case 4: nCycles = atoi(argv[3]);
    case 3: state = atoi(argv[2]);
    case 2: dim = atoi(argv[1]);
  }

  double *ExpecVal = new double[5];
  double *TotalExpecVal = new double[5];
  for (int i = 0; i < 5; i++) TotalExpecVal[i] = 0;
  double timing;

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
    outfile.open("Lattice" + to_string(dim) + "Cycles" + to_string(nCycles) + ".dat");
    outfile << setw(15) << setprecision(8) << "T";
    outfile << setw(15) << setprecision(8) << "E";
    outfile << setw(15) << setprecision(8) << "E2";
    outfile << setw(15) << setprecision(8) << "M";
    outfile << setw(15) << setprecision(8) << "M2";
    outfile << setw(15) << setprecision(8) << "M abs";
    outfile << setw(15) << setprecision(8) << "Chi";
    outfile << setw(15) << setprecision(8) << "C_V";
    outfile << setw(15) << setprecision(8) << "Run time";
    outfile << setw(15) << setprecision(8) << "No. of cycles" << endl;
  }
  double TimeStart, TimeEnd, TotalTime;
  TimeStart = MPI_Wtime();
  for (double temperature = temp_init; temperature <= temp_final; temperature+=temp_step) {
    metropolis(dim, state, loopStart, loopStop, temperature, ExpecVal, &timing);
    for (int i=0; i<5; i++) MPI_Reduce(&ExpecVal[i], &TotalExpecVal[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (my_rank==0) output(dim, temperature, TotalExpecVal, nCycles, timing);
    if (my_rank==0) cout << "T=" << temperature << " done...\n";
  }
  outfile.close();
  TimeEnd = MPI_Wtime();
  TotalTime = TimeEnd-TimeStart;
  if (my_rank==0) cout << "Time used: " << TotalTime << endl << "No. of processes: " << nProcs << endl;

  MPI_Finalize ();

  // double T = 1;
  // analyticalEnergy(T);
  // analyticalSpecificHeat(T);

  delete [] ExpecVal;
  delete [] TotalExpecVal;

  return 0;
} // end of main function
