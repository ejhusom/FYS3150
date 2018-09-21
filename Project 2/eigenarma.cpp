#include <armadillo>
using namespace arma;

// Get eigenvectors and -values from Armadillo
void eigenarma(){
  // vec rho(n);
  // vec V(n);
  // for (int i=0; i<n; i++){
  //   rho(i) = i*h;
  //   V(i) = i*i*hh;
  // }
  // rho.save("rho.dat",raw_ascii);
  //
  // vec main = (2/hh)*ones<vec>(n);
  // main += V;
  // vec off = (-1/hh)*ones<vec>(n-1);
  // mat A_ = diagmat(main);
  // mat B = diagmat(off,1);
  // mat C = diagmat(off,-1);
  // A_ = A_+B+C;
  // vec eigval;
  // mat eigvec;
  // eig_sym(eigval, eigvec, A_);
  // eigvec.save("eigvec.dat",raw_ascii);
  // eigval.save("eigval.dat",raw_ascii);
}
