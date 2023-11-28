#include <iostream>
using namespace std;

struct Registro {
    int num;
    char car;
};

constexpr int N = 10;

struct Lista {
    Registro elementos[N];
    int cont;
};

struct ListaPtr { // Lista de punteros
    Registro* punt[N];
    int cont;
};

void porNum(const Lista& lista, ListaPtr& ord) 
{
    for (int i = 0; i < N; i++) {
        *ord.punt[i] = lista.elementos[i];
    }

    Registro* aux;
    for (int i = 1; i < N; i++) 
    {
        int j = i; 

        while (j > 0 && ord.punt[j]->num < ord.punt[j - 1]->num)
        {
            aux = ord.punt[j - 1];
            ord.punt[j - 1] = ord.punt[j]; 
            ord.punt[j] = aux;
            j--;
        }
    }
}

void porCar(const Lista& lista, ListaPtr& ord) 
{



}

void mostrar(const ListaPtr& ord) 
{
    for (int i = 0; i < N; i++) 
    {
        cout << ord.punt[i]->num;
    }
}


int main()
{
    Lista lista;
    ListaPtr listaptr;

    for (int i = 0; i < N; i++) 
    {
        lista.elementos[i] = N - i;
    }

    porNum(lista, listaptr);

    mostrar(listaptr);
}


