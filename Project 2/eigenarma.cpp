#include <armadillo>
using namespace arma;

// Get eigenvectors and -values from Armadillo and writes them to file
void eigenarma(int n, double rho_n){
  // Determine parameters
  vec rho = zeros<vec>(n);
  vec V = zeros<vec>(n);
  double Diag; double NonDiag;
  if (rho_n != 0){
    double h = rho_n/double(n+1);
    Diag = 2.0/(h*h);
    NonDiag = -1.0/(h*h);
    for (int i=0; i<n; i++){
      rho(i) = (i+1)*h;
      V(i) = rho(i)*rho(i);
    }
  } else {
    Diag = 2.0;
    NonDiag = -1.0;
  }

  // Create matrix
  vec main = Diag*ones<vec>(n);
  main += V;
  vec off = NonDiag*ones<vec>(n-1);
  mat A = diagmat(main);
  mat B = diagmat(off,1);
  mat C = diagmat(off,-1);
  A = A+B+C;
  vec eigval;
  mat eigvec;
  eig_sym(eigval, eigvec, A);

  // Save results for plotting
  eigvec.save("eigvec.dat",raw_ascii);
  eigval.save("eigval.dat",raw_ascii);
  rho.save("rho.dat",raw_ascii);
}
