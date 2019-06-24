// #include "Euler.h"
//
// void Euler::integrate(){
//   for (AstronomicalObject &other : AllObjects){
//     xAcc += current.acceleration(other,0);
//     yAcc += current.acceleration(other,1);
//     zAcc += current.acceleration(other,2);
//   }
//
//   current.velocity[0] = current.velocity[0] + TimeStep*xAcc;
//   current.velocity[1] = current.velocity[1] + TimeStep*yAcc;
//   current.velocity[2] = current.velocity[2] + zAcc;
//
//   current.position[0] = current.position[0] + TimeStep*current.velocity[0];
//   current.position[1] = current.position[1] + TimeStep*current.velocity[1];
//   current.position[2] = current.position[2] + TimeStep*current.velocity[2];
// }
