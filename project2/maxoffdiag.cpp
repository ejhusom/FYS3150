#include <cmath>
using namespace std;

// Function for finding maximum off-diagonal element
double maxoffdiag(double **A, int *k, int *l, int n){
  double max = 0.0;
  for (int i=0; i<n; i++){
    for (int j=i+1; j<n; j++){
      if (fabs(A[i][j])>max){
        max = fabs(A[i][j]); *k = i; *l = j;
      }
    }
  }
  return max;
} // end of maxoffdiag function
