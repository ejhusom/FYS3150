#include "TwoBodyProblemClass.h"

TwoBodyProblemClass::TwoBodyProblemClass(){
  MeshPoints = 10000;
  TimeFinal = 10.0;
}

TwoBodyProblemClass::TwoBodyProblemClass(int n, double t_f, vector<AstronomicalObject> objects,int m){
  MeshPoints = n;
  TimeFinal = t_f;
  AllObjects = objects;
  Method = m;
}

void TwoBodyProblemClass::solve(){
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
    MethodName = "TwoBodyProblemVerlet";
  }
  ofstream outposition;
  outposition.open(MethodName + ".dat");
  // Integration loop
  if (this->Method == 0) {
    for (int i = 0; i < MeshPoints; i++) {
      xAcc = yAcc = xAccNew = yAccNew = zAcc = zAccNew = 0;
      // Acceleration
      xAcc += AllObjects[1].acceleration(AllObjects[0],0);
      yAcc += AllObjects[1].acceleration(AllObjects[0],1);
      zAcc += AllObjects[1].acceleration(AllObjects[0],2);
      // Storing position
      outposition << setw(30) << setprecision(15) << i*TimeStep;
      outposition << setw(30) << setprecision(15) << AllObjects[1].GetKineticEnergy();
      outposition << setw(30) << setprecision(15) << AllObjects[1].GetPotentialEnergy(AllObjects[0]);
      outposition << setw(30) << setprecision(15) << AllObjects[1].GetAngularMoment();
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[0];
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[1];
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[2];
      outposition << endl;

      AllObjects[1].position[0] = AllObjects[1].position[0] + TimeStep*AllObjects[1].velocity[0] + xAcc*TimeStepSqHalf;
      AllObjects[1].position[1] = AllObjects[1].position[1] + TimeStep*AllObjects[1].velocity[1] + yAcc*TimeStepSqHalf;
      AllObjects[1].position[2] = AllObjects[1].position[2] + TimeStep*AllObjects[1].velocity[2] + zAcc*TimeStepSqHalf;

      xAccNew += AllObjects[1].acceleration(AllObjects[0],0);
      yAccNew += AllObjects[1].acceleration(AllObjects[0],1);
      zAccNew += AllObjects[1].acceleration(AllObjects[0],2);

      AllObjects[1].velocity[0] = AllObjects[1].velocity[0] + TimeStepHalf*(xAccNew + xAcc);
      AllObjects[1].velocity[1] = AllObjects[1].velocity[1] + TimeStepHalf*(yAccNew + yAcc);
      AllObjects[1].velocity[2] = AllObjects[1].velocity[2] + TimeStepHalf*(zAccNew + zAcc);
    }
    outposition.close();
  } else {
    for (int i = 0; i < MeshPoints; i++) {
      xAcc = yAcc = zAcc = 0;

      xAcc += AllObjects[1].acceleration(AllObjects[0],0);
      yAcc += AllObjects[1].acceleration(AllObjects[0],1);
      zAcc += AllObjects[1].acceleration(AllObjects[0],2);

      AllObjects[1].velocity[0] = AllObjects[1].velocity[0] + TimeStep*xAcc;
      AllObjects[1].velocity[1] = AllObjects[1].velocity[1] + TimeStep*yAcc;
      AllObjects[1].velocity[2] = AllObjects[1].velocity[2] + TimeStep*zAcc;

      AllObjects[1].position[0] = AllObjects[1].position[0] + TimeStep*AllObjects[1].velocity[0];
      AllObjects[1].position[1] = AllObjects[1].position[1] + TimeStep*AllObjects[1].velocity[1];
      AllObjects[1].position[2] = AllObjects[1].position[2] + TimeStep*AllObjects[1].velocity[2];

      // Storing position
      outposition << setw(30) << setprecision(15) << i*TimeStep;
      outposition << setw(30) << setprecision(15) << AllObjects[1].GetKineticEnergy();
      outposition << setw(30) << setprecision(15) << AllObjects[1].GetPotentialEnergy(AllObjects[0]);
      outposition << setw(30) << setprecision(15) << AllObjects[1].GetAngularMoment();
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[0];
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[1];
      outposition << setw(30) << setprecision(15) << AllObjects[1].position[2];
      outposition << endl;
    }
    outposition.close();
  }

} // end of function solve
