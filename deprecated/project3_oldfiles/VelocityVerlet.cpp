// #include "VelocityVerlet.h"
//
// void VelocityVerlet::integrate(){
//   for (AstronomicalObject &other : AllObjects){
//     xAcc += current.acceleration(other,0);
//     yAcc += current.acceleration(other,1);
//     zAcc += current.acceleration(other,2);
//   }
//   // Storing position
//   outposition << setw(30) << setprecision(15) << current.position[0];
//   outposition << setw(30) << setprecision(15) << current.position[1];
//   outposition << setw(30) << setprecision(15) << current.position[2];
//
//   current.position[0] = current.position[0] + TimeStep*current.velocity[0] + xAcc*TimeStepSqHalf;
//   current.position[1] = current.position[1] + TimeStep*current.velocity[1] + yAcc*TimeStepSqHalf;
//   current.position[2] = current.position[2] + TimeStep*current.velocity[2] + zAcc*TimeStepSqHalf;
//
//   for (AstronomicalObject &other : AllObjects){
//     xAccNew += current.acceleration(other,0);
//     yAccNew += current.acceleration(other,1);
//     zAccNew += current.acceleration(other,2);
//   }
//
//   current.velocity[0] = current.velocity[0] + TimeStepHalf*(xAccNew + xAcc);
//   current.velocity[1] = current.velocity[1] + TimeStepHalf*(yAccNew + yAcc);
//   current.velocity[2] = current.velocity[2] + TimeStepHalf*(zAccNew + zAcc);
// }
