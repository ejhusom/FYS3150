#include "analytical.h"

void analyticalEnergy(){
  double E;
  E = 8*(exp(-8)-exp(8))/(6+exp(8)-exp(-8));
  cout << "Analytical 2x2 case, expectation value for energy: " << E << endl;
}

void analyticalSpecificHeat(){
  double CV, Z;
  Z = 12 + 2*exp(8) + 2*exp(-8);
  CV = 256*(Z*cosh(8)-2*sinh(8)*sinh(8))/(Z*Z);
  cout << "Analytical 2x2 case, specific heat: " << CV << endl;
}
