#include <iostream>
#include <array>
using namespace std;

const int N = 5;

void MueveAlPrimerLugar(int *v) 
{
    int aux1;

    for (int i = 0; i < N; i++) 
    {
        aux1 = v[0];
        v[0] = v[i];
        v[i] = aux1;
    }
}


int main()
{
    int *v1 = new int[N]{ 1, 2, 3, 4, 5 };
    MueveAlPrimerLugar(v1);

    for (int i = 0; i < N; i++) {
        cout << v1[i];
    }

    delete[]v1;
}

