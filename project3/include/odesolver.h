#ifndef ODESOLVER_H
#define ODESOLVER_H

class odesolver{
public:
  double mass;

  void VelocityVerlet(int meshpoints, double time_f);
};

#endif
