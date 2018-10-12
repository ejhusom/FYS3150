#include "VelocityVerlet.h"

VelocityVerlet::VelocityVerlet(){
  MeshPoints = 10000;
  TimeFinal = 10.0;
}

VelocityVerlet::VelocityVerlet(int n, double t_f, vector<AstronomicalObject> objects){
  MeshPoints = n;
  TimeFinal = t_f;
  AllObjects = objects;
}

void VelocityVerlet::solve(){
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStep*TimeStep/2;
  // Temporary acceleration values
  double xAcc; double yAcc; double xAccNew; double yAccNew; double zAcc; double zAccNew;
  // Open file for writing
  ofstream outfile;
  outfile.open ("SolarSystemPositionsVerlet.dat");
  // Integration loop
  for (int i = 0; i < MeshPoints; i++) {
    for (int obj = 0; obj < AllObjects.size(); obj++) {
      xAcc = yAcc = xAccNew = yAccNew = zAcc = zAccNew = 0;
      // Acceleration
      for (int obj2 = 0; obj2 < AllObjects.size(); obj2++){
        xAcc += AllObjects[obj].acceleration(AllObjects[obj2],0);
        yAcc += AllObjects[obj].acceleration(AllObjects[obj2],1);
        zAcc += AllObjects[obj].acceleration(AllObjects[obj2],2);
      }
      // Storing position
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[0];
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[1];
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[2];

      AllObjects[obj].position[0] = AllObjects[obj].position[0] + TimeStep*AllObjects[obj].velocity[0] + xAcc*TimeStepSqHalf;
      AllObjects[obj].position[1] = AllObjects[obj].position[1] + TimeStep*AllObjects[obj].velocity[1] + yAcc*TimeStepSqHalf;
      AllObjects[obj].position[2] = AllObjects[obj].position[2] + TimeStep*AllObjects[obj].velocity[2] + zAcc*TimeStepSqHalf;

      for (int obj2 = 0; obj2 < AllObjects.size(); obj2++){
        xAccNew += AllObjects[obj].acceleration(AllObjects[obj2],0);
        yAccNew += AllObjects[obj].acceleration(AllObjects[obj2],1);
        zAccNew += AllObjects[obj].acceleration(AllObjects[obj2],2);
      }

      AllObjects[obj].velocity[0] = AllObjects[obj].velocity[0] + TimeStepHalf*(xAccNew + xAcc);
      AllObjects[obj].velocity[1] = AllObjects[obj].velocity[1] + TimeStepHalf*(yAccNew + yAcc);
      AllObjects[obj].velocity[2] = AllObjects[obj].velocity[2] + TimeStepHalf*(zAccNew + zAcc);
    }
    outfile << endl;
  }
  outfile.close();

} // end of function solve
