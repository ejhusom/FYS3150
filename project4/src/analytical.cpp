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
    return analyticalM2()- analyticalM()*analyticalM();
}

double analyticalCv() {
    return analyticalE2() - analyticalE()*analyticalE();
}

double analyticalMabs() {
    double Z = 12 + 4*cosh(8);
    return (exp(8) + 2 )*8/Z;
}

void printAnalytical(){
  ofstream outfile;
  outfile.open("analytical.dat");
  double d = 4.0;
  outfile << setw(15) << setprecision(8) << "E";
  outfile << setw(15) << setprecision(8) << "E2";
  outfile << setw(15) << setprecision(8) << "M";
  outfile << setw(15) << setprecision(8) << "M2";
  outfile << setw(15) << setprecision(8) << "abs M";
  outfile << setw(15) << setprecision(8) << "Cv";
  outfile << setw(15) << setprecision(8) << "chi" << endl;
  outfile << setw(15) << setprecision(8) << analyticalE()/d;
  outfile << setw(15) << setprecision(8) << analyticalE2()/d;
  outfile << setw(15) << setprecision(8) << analyticalM()/d;
  outfile << setw(15) << setprecision(8) << analyticalM2()/d;
  outfile << setw(15) << setprecision(8) << analyticalMabs()/d;
  outfile << setw(15) << setprecision(8) << analyticalCv()/d;
  outfile << setw(15) << setprecision(8) << analyticalchi()/d << endl;
  outfile.close();
}
