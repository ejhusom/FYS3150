#include <cmath>
using namespace std;

// Function to update matrix elements
void rotate(double **A, double **R, int k, int l, int n){
  double tau, t, c, s;
  if (A[k][l] != 0.0){
    tau = (A[l][l]-A[k][k])/(2*A[k][l]);
    if (tau>=0){
      t = 1.0/(tau + sqrt(1.0 + tau*tau));
    } else {
      t = -1.0/(-tau + sqrt(1.0 + tau*tau));
    }

    c = 1/sqrt(1+t*t);
    s = t*c;
  } else {
    c = 1.0; s = 0.0;
  }

  double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
  a_kk = A[k][k];
  a_ll = A[l][l];
  A[k][k] = a_kk*c*c - 2*A[k][l]*c*s + a_ll*s*s;
  A[l][l] = a_ll*c*c + 2*A[k][l]*c*s + a_kk*s*s;
  A[k][l] = 0.0;
  A[l][k] = 0.0;
  for (int i=0; i<n; i++){
    if (i != k && i != l){
      a_ik = A[i][k];
      a_il = A[i][l];
      A[i][k] = a_ik*c - a_il*s;
      A[k][i] = A[i][k];
      A[i][l] = a_il*c + a_ik*s;
      A[l][i] = A[i][l];
    }
  // Compute new eigenvectors
  r_ik = R[i][k];
  r_il = R[i][l];
  R[i][k] = r_ik*c - r_il*s;
  R[i][l] = r_il*c + r_ik*s;
  }
} // end of function rotate
