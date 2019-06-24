#ifndef VELOCITYVERLET_H
#define VELOCITYVERLET_H
#include "Integrator2.h"
using namespace std;

class VelocityVerlet: public Integrator2 {
public:
  // Functions
  void integrate();

};

#endif /* VELOCITYVERLET_H */
