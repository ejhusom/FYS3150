#include "AstronomicalObject.h"

AstronomicalObject::AstronomicalObject(){
  mass = 1.;
  position[0] = 0.0;
  position[1] = 0.0;
  velocity[0] = 0.0;
  velocity[1] = 0.0;
}

AstronomicalObject::AstronomicalObject(double m, double x, double y, double z, double vx, double vy, double vz){
  mass = m;
  position[0] = x;
  position[1] = y;
  position[2] = z;
  velocity[0] = vx;
  velocity[1] = vy;
  velocity[2] = vz;
}

double AstronomicalObject::distance(AstronomicalObject OtherObject){
  double dx = this->position[0]-OtherObject.position[0];
  double dy = this->position[1]-OtherObject.position[1];
  double dz = this->position[2]-OtherObject.position[2];
  return sqrt(dx*dx + dy*dy + dz*dz);
}

double AstronomicalObject::acceleration(AstronomicalObject OtherObject, int axis){
  double r = this->distance(OtherObject);
  if (r!=0) return -(this->position[axis]-OtherObject.position[axis])*4*M_PI*M_PI*OtherObject.mass/(r*r*r);
  else return 0;
}

double AstronomicalObject::GetKineticEnergy(){
  double vv = this->velocity[0]*this->velocity[0] + this->velocity[1]*this->velocity[1] + this->velocity[2]*this->velocity[2];
  return 0.5*this->mass*vv;
}

double AstronomicalObject::GetPotentialEnergy(AstronomicalObject OtherObject){
  double r = this->distance(OtherObject);
  if (r!=0) return -4*M_PI*M_PI*OtherObject.mass*this->mass/r;
  else return 0;
}

double AstronomicalObject::GetAngularMoment(){
  double x = this->position[0]; double y = this->position[0]; double z = this->position[0];
  double vx = this->velocity[0]; double vy = this->velocity[0]; double vz = this->velocity[0];
  return sqrt((y*vz - z*vy)*(y*vz - z*vy) + (x*vz-z*vx)*(x*vz-z*vx) + (x*vy-y*vx)*(x*vy-y*vx));
}

double AstronomicalObject::accelerationRelativistic(AstronomicalObject OtherObject, int axis){
  double r = this->distance(OtherObject);
  double l = this->GetAngularMoment();
  double c = 3e8;
  if (r!=0) return -(1+3*l*l/(r*r*c*c))*(this->position[axis]-OtherObject.position[axis])*4*M_PI*M_PI*OtherObject.mass/(r*r*r);
  else return 0;
}
