#include <iostream>
using namespace std;

int main()
{
    /*
    // a
    int* p1; int* p2;
    int n = 5;

    p1 = &n;
    p2 = p1;
    */


    // b
    int* p1 = new int; //apunta a una dirección que no tiene nada
    int* p2;
    int n = 5;

    delete(p1); // antes de asignarle un valor hay que borrarlo porque ya apuntaba a un sitio

    p1 = &n; // p1 = dirección de n (5)
    p2 = p1; // p2 = p1 = dirección de n (5)


}

