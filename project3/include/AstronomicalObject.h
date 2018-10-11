#ifndef ASTRONOMICALOBJECT_H
#define ASTRONOMICALOBJECT_H
#include <cmath>

class AstronomicalObject{
public:
  // Properties
  double mass;
  double position[2];
  double velocity[2];
  // Initializers
  AstronomicalObject();
  AstronomicalObject(double m, double x, double y, double vx, double vy);
  // Functions
  double distance(AstronomicalObject OtherObject);
  double acceleration(AstronomicalObject OtherObject, int axis);


};

#endif /* ASTRONOMICALOBJECT_H */
