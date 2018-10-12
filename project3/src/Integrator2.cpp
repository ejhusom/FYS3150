// #include "Integrator2.h"
//
// Integrator2::Integrator2(){
//   MeshPoints = 10000;
//   TimeFinal = 10.0;
// }
//
// Integrator2::Integrator2(int n, double t_f, vector<AstronomicalObject> objects,int m){
//   MeshPoints = n;
//   TimeFinal = t_f;
//   AllObjects = objects;
//   Method = m;
// }
//
// void Integrator2::solve(){
//   double TimeStep = TimeFinal/double(MeshPoints);
//   double TimeStepHalf = TimeStep/2;
//   double TimeStepSqHalf = TimeStep*TimeStep/2;
//   // Temporary acceleration values
//   double xAcc; double yAcc; double xAccNew; double yAccNew; double zAcc; double zAccNew;
//   // Open file for writing
//   string filename;
//   if (this->Method == 1){
//     filename = "SolarSystemPositionsEuler.dat";
//   } else {
//     filename = "SolarSystemPositionsVerlet.dat";
//   }
//   ofstream outfile;
//   outfile.open (filename);
//   // Integration loop
//   for (int i = 0; i < MeshPoints; i++) {
//     for (AstronomicalObject &current : AllObjects) {
//       // Storing position
//       outfile << setw(30) << setprecision(15) << current.position[0];
//       outfile << setw(30) << setprecision(15) << current.position[1];
//       outfile << setw(30) << setprecision(15) << current.position[2];
//
//       xAcc = yAcc = zAcc = 0;
//
//       integrate();
//
//     }
//     outfile << endl;
//   }
//   outfile.close();
//
// } // end of function solve
