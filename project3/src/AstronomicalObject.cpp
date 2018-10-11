#include "AstronomicalObject.h"

AstronomicalObject::AstronomicalObject(){
  mass = 1.;
  position[0] = 0.0;
  position[1] = 0.0;
  velocity[0] = 0.0;
  velocity[1] = 0.0;
}

AstronomicalObject::AstronomicalObject(double m, double x, double y, double vx, double vy){
  mass = m;
  position[0] = x;
  position[1] = y;
  velocity[0] = vx;
  velocity[1] = vy;
}

double AstronomicalObject::distance(AstronomicalObject OtherObject){
  double dx = this->position[0]-OtherObject.position[0];
  double dy = this->position[1]-OtherObject.position[1];
  return sqrt(dx*dx + dy*dy);
}

double AstronomicalObject::acceleration(AstronomicalObject OtherObject, int axis){
  double r = this->distance(OtherObject);
  return -(this->position[axis]-OtherObject.position[axis])*4*M_PI*M_PI*OtherObject.mass/(r*r*r);
}
