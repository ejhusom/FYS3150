#include <iostream>
using namespace std;

float sum_up(int N) {
    double sum;
    sum = 0;
    for (int i=1; i < N; i++){
        double n;
        n = i;
        sum += 1/n;
    }
    return sum;
}

int main ()
{
    int N;
    cout << "Insert N value";
    cin >> N;
    double result;
    result = sum_up(N)
    cout << result
    return 0;
}
