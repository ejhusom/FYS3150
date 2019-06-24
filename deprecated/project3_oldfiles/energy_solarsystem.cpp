double AstronomicalObject::GetKineticEnergy(){
  double vv = this->velocity[0]*this->velocity[0] + this->velocity[1]*this->velocity[1] + this->velocity[2]*this->velocity[2];
  return 0.5*this->mass*vv;
}

double AstronomicalObject::GetPotentialEnergy(AstronomicalObject OtherObject){
  return -4*M_PI*M_PI*OtherObject.mass/(this->distance(OtherObject));
}

double AstronomicalObject::GetAngularMoment(){
  double x = this->position[0]; double y = this->position[0]; double z = this->position[0];
  double vx = this->velocity[0]; double vy = this->velocity[0]; double vz = this->velocity[0];
  return sqrt((y*vz - z*vy)*(y*vz - z*vy) + (x*vz-z*vx)*(x*vz-z*vx) + (x*vy-y*vx)*(x*vy-y*vx));
}


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
  double PotentialEnergySum;
  // Open file for writing
  string MethodName;
  if (this->Method == 1){
    MethodName = "TwoBodyProblemEuler";
  } else {
    MethodName = "SolarSystemVerlet";
  }
  ofstream outposition;
  outposition.open(MethodName + "Positions.dat");
  ofstream outenergy;
  outenergy.open(MethodName + "Energy.dat");
  // Integration loop
  if (this->Method == 0) {
    for (int i = 0; i < MeshPoints; i++) {
      for (AstronomicalObject &current : AllObjects) {
        xAcc = yAcc = xAccNew = yAccNew = zAcc = zAccNew = 0;
        PotentialEnergySum = 0;
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

        // Storing energy and angular moment
        outenergy << setw(30) << setprecision(15) << AllObjects[1].GetKineticEnergy();
        for (AstronomicalObject &other : AllObjects){
          PotentialEnergySum += AllObjects[1].GetPotentialEnergy(other)
        }
        outenergy << setw(30) << setprecision(15) << PotentialEnergySum;
        outenergy << setw(30) << setprecision(15) << AllObjects[1].GetAngularMoment();

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
      PotentialEnergySum = 0;

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

      // Storing energy and angular moment
      outenergy << setw(30) << setprecision(15) << AllObjects[1].GetKineticEnergy();
      for (AstronomicalObject &other : AllObjects){
        PotentialEnergySum += AllObjects[1].GetPotentialEnergy(other);
      }
      outenergy << setw(30) << setprecision(15) << AllObjects[1].GetPotentialEnergy(other);
      outenergy << setw(30) << setprecision(15) << AllObjects[1].GetAngularMoment();

      outposition << endl;
    }
    outposition.close();
  }

} // end of function solve
