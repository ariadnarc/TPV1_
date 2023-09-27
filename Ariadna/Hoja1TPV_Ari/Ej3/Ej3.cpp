#include <iostream>
#include <array>
using namespace std;


const int N = 3;

void EscribeMat(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }
}

void SumaMatrices(int mat1[N][N], int mat2[N][N])
{
    int matResult[N][N] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matResult[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    EscribeMat(matResult);
}

void RestaMatrices(int mat1[N][N], int mat2[N][N])
{
    int matResult2[N][N] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matResult2[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
    EscribeMat(matResult2);
}

void MultiplicaMatrices(int mat1[N][N], int mat2[N][N])
{
    int matResult3[N][N] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
    int aux1 = 0, aux2 = 0, aux3 = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                matResult3[i][j] += mat1[i][(i + k) % N] * mat2[(i + k) % N][j];
            }
        }
    }
    EscribeMat(matResult3);
}

void TrasponerMatriz(int mat[N][N])
{
    int matResult4[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matResult4[i][j] = mat[j][i];
        }
    }

    EscribeMat(matResult4);
}

void PuntosDeSilla(int mat[N][N])
{
    int i = 0, k = 0, indiceMenor, indFila, puntosSilla = 0;
    int* x = new int[N];
    int* y = new int[N];
    bool hayMayor = false;


    while (i < N) // recorre filas
    {
        indiceMenor = 0;
        for (int k = 0; k < N; k++) //recorre la fila 
        {
            if (mat[i][indiceMenor] > mat[i][k]) // asumo que el primer elemento es el menor
            {
                indiceMenor = k; // le asigno el menor
            } // si no era el menor avanzo al siguiente elemento de la fila
        }

        indFila = 0;

        hayMayor = false;

        while (indFila < N && !hayMayor) // recorre columnas
        {
            if (mat[indFila][indiceMenor] > mat[i][indiceMenor]) {
                hayMayor = true;
            }
            indFila++;
        }

        if (!hayMayor) {
            x[puntosSilla] = i;
            y[puntosSilla] = indiceMenor;
            puntosSilla++;

        }



        i++;
    }

    cout << "La matriz tiene " << puntosSilla << " puntos de silla en las coordenadas: ";

    for (int i = 0; i < puntosSilla; i++) {
        cout << " (" << x[i] << ", " << y[i] << ")   ";
    }

}

int main()
{
    int mat1[N][N] = {  {1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9} };

    int mat2[N][N] = {  {4, 8, 1},
                        {2, 9, 3},
                        {7, 5, 6} };

}
