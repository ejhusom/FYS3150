#ifndef ASTRONOMICALOBJECT_H
#define ASTRONOMICALOBJECT_H
#include <cmath>

class AstronomicalObject{
public:
  // Properties
  double mass;
  double position[3];
  double velocity[3];
  double acceleration[3];
  double accelerationNew[3];
  // Initializers
  AstronomicalObject();
  AstronomicalObject(double m, double x, double y, double z, double vx, double vy, double vz);
  // Functions
  double GetDistance(AstronomicalObject OtherObject);
  double GetAcceleration(AstronomicalObject OtherObject, int axis);
  double GetKineticEnergy();
  double GetPotentialEnergy(AstronomicalObject OtherObject);
  double GetAngularMoment();
  double GetAccelerationRelativistic(AstronomicalObject OtherObject, int axis);
  double GetPerihelionPrecession2D();

};

#endif /* ASTRONOMICALOBJECT_H */
