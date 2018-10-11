#ifndef ASTRONOMICALOBJECT_H
#define ASTRONOMICALOBJECT_H
#include <cmath>

class AstronomicalObject{
public:
  // Properties
  double mass;
  double position[3];
  double velocity[33];
  // Initializers
  AstronomicalObject();
  AstronomicalObject(double m, double x, double y, double z, double vx, double vy, double vz);
  // Functions
  double distance(AstronomicalObject OtherObject);
  double acceleration(AstronomicalObject OtherObject, int axis);


};

#endif /* ASTRONOMICALOBJECT_H */
