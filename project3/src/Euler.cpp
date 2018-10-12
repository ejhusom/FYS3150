#include "Euler.h"

Euler::Euler(){
  MeshPoints = 10000;
  TimeFinal = 10.0;
}

Euler::Euler(int n, double t_f, vector<AstronomicalObject> objects){
  MeshPoints = n;
  TimeFinal = t_f;
  AllObjects = objects;
}

void Euler::solve(){
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStep*TimeStep/2;
  double xAcc; double yAcc; double zAcc;
  // Open file for writing
  ofstream outfile;
  outfile.open ("SolarSystemPositionsEuler.dat");
  // Integration loop
  for (int i = 0; i < MeshPoints; i++) {
    for (int obj = 0; obj < AllObjects.size(); obj++) {
      xAcc = yAcc = zAcc = 0;

      for (int obj2 = 0; obj2 < AllObjects.size(); obj2++){
        xAcc += AllObjects[obj].acceleration(AllObjects[obj2],0);
        yAcc += AllObjects[obj].acceleration(AllObjects[obj2],1);
        zAcc += AllObjects[obj].acceleration(AllObjects[obj2],2);
      }

      AllObjects[obj].velocity[0] = AllObjects[obj].velocity[0] + TimeStep*xAcc;
      AllObjects[obj].velocity[1] = AllObjects[obj].velocity[1] + TimeStep*yAcc;
      AllObjects[obj].velocity[2] = AllObjects[obj].velocity[2] + zAcc;

      AllObjects[obj].position[0] = AllObjects[obj].position[0] + TimeStep*AllObjects[obj].velocity[0];
      AllObjects[obj].position[1] = AllObjects[obj].position[1] + TimeStep*AllObjects[obj].velocity[1];
      AllObjects[obj].position[2] = AllObjects[obj].position[2] + TimeStep*AllObjects[obj].velocity[2];

      // Storing position
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[0];
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[1];
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[2];
    }
    outfile << endl;
  }
  outfile.close();

} // end of function solve
