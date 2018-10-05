#ifndef ODESOLVER_H
#define ODESOLVER_H

class odesolver{

public:
  odesolver() {}

  void initialize(int MeshPoints, double TimeFinal);
  void VelocityVerlet(int MeshPoints, double TimeFinal);
  void ForwardEuler(int MeshPoints, double TimeFinal);

};

#endif
