#include "analytical.h"

double analyticalE() {
    double Z = 12+4*cosh(8);
    return -32/Z*sinh(8);
}

double analyticalE2() {
    double Z = 12+4*cosh(8);
    return 256/Z*cosh(8);
}

double analyticalM() {
    return 0;
}

double analyticalM2() {
    double Z = 12+4*cosh(8);
    return (exp(8) + 1 )*32/Z;
}

double analyticalchi() {
    return M2()- M()*M();
}

double analyticalCv() {
    return E2() - E()*E();
}

double analyticalMabs() {
    double Z = 12 + 4*cosh(8);
    return (exp(8) + 2 )*8/Z;
}

void printAnalytical(){
  double d = 4.0;
  cout << setw(15) << setprecision(8) << "E";
  cout << setw(15) << setprecision(8) << "E2";
  cout << setw(15) << setprecision(8) << "M";
  cout << setw(15) << setprecision(8) << "M2";
  cout << setw(15) << setprecision(8) << "abs M";
  cout << setw(15) << setprecision(8) << "Cv";
  cout << setw(15) << setprecision(8) << "chi" << endl;
  cout << setw(15) << setprecision(8) << analyticalE()/d;
  cout << setw(15) << setprecision(8) << analyticalE2()/d;
  cout << setw(15) << setprecision(8) << analyticalM();
  cout << setw(15) << setprecision(8) << analyticalM2();
  cout << setw(15) << setprecision(8) << analyticalabsM();
  cout << setw(15) << setprecision(8) << analyticalCv();
  cout << setw(15) << setprecision(8) << analyticalchi() << endl;
}
