#include "analytical.h"

void analyticalEnergy(double T){
  double E;
  E = 8*(exp(-8/T)-exp(8/T))/(6+exp(8/T)-exp(-8/T));
  cout << "Analytical 2x2 case, expectation value for energy: " << E << endl;
}

void analyticalSpecificHeat(double T){
  double CV, Z;
  Z = 12 + 2*exp(8/T) + 2*exp(-8/T);
  CV = 256*(Z*cosh(8/T)-2*sinh(8/T)*sinh(8/T))/(T*T*Z*Z);
  cout << "Analytical 2x2 case, specific heat: " << CV << endl;
}
