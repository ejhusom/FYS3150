#ifndef ASTRONOMICALOBJECT_H
#define ASTRONOMICALOBJECT_H
#include <cmath>

class AstronomicalObject{
public:
  // Properties
  double mass;
  double position[3];
  double velocity[33];
  double KineticEnergy;
  double PotentialEnergy;
  double AngularMoment;
  // Initializers
  AstronomicalObject();
  AstronomicalObject(double m, double x, double y, double z, double vx, double vy, double vz);
  // Functions
  double distance(AstronomicalObject OtherObject);
  double acceleration(AstronomicalObject OtherObject, int axis);
  double GetKineticEnergy();
  double GetPotentialEnergy(AstronomicalObject OtherObject);
  // double GetAngularMoment();

};

#endif /* ASTRONOMICALOBJECT_H */
