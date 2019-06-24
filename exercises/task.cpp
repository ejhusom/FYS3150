#include <iostream>
#include <cmath>
#include <fstream>
#include <armadillo>
using namespace std;

double derivatives(double x, double harray[], int N) {
    ofstream dat3;
    dat3.open ("dat3.txt");
    double result1;
    double result2;
    for (int i=1; i<N; i++){
        result1 = (atan(x + harray[i]) - atan(x))/harray[i];
        result2 = (atan(x + harray[i]) - atan(x - harray[i]))/(2*harray[i]);
        dat3 << harray[i] << ", " << result1 << ", " << result2 << endl;
        cout << harray[i] << ", " << result1 << ", " << result2 << endl;
    }
    dat3.close();
    return 0;
}


int main()
{


    double x;
    x = sqrt(2);
    int N;
    N = 20;

    double *harray = new double[N];

    for (int i=1; i<N; i++){
        double h;
        h = pow(10, -i);
        harray[i] = h;
    }

    derivatives(x, harray, N);

    return 0;
}
