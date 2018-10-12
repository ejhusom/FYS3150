#include "Integrator.h"

Integrator::Integrator(){
  MeshPoints = 10000;
  TimeFinal = 10.0;
}

Integrator::Integrator(int n, double t_f, vector<AstronomicalObject> objects,int m){
  MeshPoints = n;
  TimeFinal = t_f;
  AllObjects = objects;
  Method = m;
}

void Integrator::solve(){
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStep*TimeStep/2;
  // Temporary acceleration values
  double xAcc; double yAcc; double xAccNew; double yAccNew; double zAcc; double zAccNew;
  // Open file for writing
  string MethodName;
  if (this->Method == 1){
    MethodName = "TwoBodyProblemEuler";
  } else {
    MethodName = "SolarSystemVerlet";
  }
  ofstream outposition;
  outposition.open(MethodName + "Positions.dat");
  // Integration loop
  if (this->Method == 0) {
    for (int i = 0; i < MeshPoints; i++) {
      for (AstronomicalObject &current : AllObjects) {
        xAcc = yAcc = xAccNew = yAccNew = zAcc = zAccNew = 0;
        // Acceleration
        for (AstronomicalObject &other : AllObjects){
          xAcc += current.acceleration(other,0);
          yAcc += current.acceleration(other,1);
          zAcc += current.acceleration(other,2);
        }
        // Storing position
        outposition << setw(30) << setprecision(15) << current.position[0];
        outposition << setw(30) << setprecision(15) << current.position[1];
        outposition << setw(30) << setprecision(15) << current.position[2];

        current.position[0] = current.position[0] + TimeStep*current.velocity[0] + xAcc*TimeStepSqHalf;
        current.position[1] = current.position[1] + TimeStep*current.velocity[1] + yAcc*TimeStepSqHalf;
        current.position[2] = current.position[2] + TimeStep*current.velocity[2] + zAcc*TimeStepSqHalf;

        for (AstronomicalObject &other : AllObjects){
          xAccNew += current.acceleration(other,0);
          yAccNew += current.acceleration(other,1);
          zAccNew += current.acceleration(other,2);
        }

        current.velocity[0] = current.velocity[0] + TimeStepHalf*(xAccNew + xAcc);
        current.velocity[1] = current.velocity[1] + TimeStepHalf*(yAccNew + yAcc);
        current.velocity[2] = current.velocity[2] + TimeStepHalf*(zAccNew + zAcc);
      }
      outposition << endl;
    }
    outposition.close();
  } else {
    for (int i = 0; i < MeshPoints; i++) {
      xAcc = yAcc = zAcc = 0;

      for (AstronomicalObject &other : AllObjects){
        xAcc += AllObjects[1].acceleration(other,0);
        yAcc += AllObjects[1].acceleration(other,1);
        zAcc += AllObjects[1].acceleration(other,2);
      }

      AllObjects[1].velocity[0] = AllObjects[1].velocity[0] + TimeStep*xAcc;
      AllObjects[1].velocity[1] = AllObjects[1].velocity[1] + TimeStep*yAcc;
      AllObjects[1].velocity[2] = AllObjects[1].velocity[2] + zAcc;

      AllObjects[1].position[0] = AllObjects[1].position[0] + TimeStep*AllObjects[1].velocity[0];
      AllObjects[1].position[1] = AllObjects[1].position[1] + TimeStep*AllObjects[1].velocity[1];
      AllObjects[1].position[2] = AllObjects[1].position[2] + TimeStep*AllObjects[1].velocity[2];

      // Storing position
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[0];
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[1];
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[2];

      outposition << endl;
    }
    outposition.close();
  }

} // end of function solve
