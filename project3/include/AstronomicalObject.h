#ifndef ASTRONOMICALOBJECT_H
#define ASTRONOMICALOBJECT_H
#include <cmath>

class AstronomicalObject{
public:
  // Properties
  double mass;
  double position[3];
  double velocity[3];
  // Initializers
  AstronomicalObject();
  AstronomicalObject(double m, double x, double y, double z, double vx, double vy, double vz);
  // Functions
  double distance(AstronomicalObject OtherObject);
  double acceleration(AstronomicalObject OtherObject, int axis);
  double GetKineticEnergy();
  double GetPotentialEnergy(AstronomicalObject OtherObject);
  double GetAngularMoment();
  double accelerationRelativistic(AstronomicalObject OtherObject, int axis);

};

#endif /* ASTRONOMICALOBJECT_H */
