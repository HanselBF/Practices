#include <iostream>
using namespace std;

int main ()
{
    int x;
    string xy;
    string y;
    cout << "Cual es tu nombre? \n";
    cin >> y;
    do
    {
        cout << "Cuantas veces quieres oir 'Feliz Halloween' " << y << "?(Escribe 0 si quieres cerrar el programa) \n";
        cin >> x;
        for (int i = 0; i < x; i++)
        {
            cout << "Feliz Halloween " << y << "! \n";
        }
        cin.get();
        cout << "Que dulce quieres? \n";
        cin >> xy;
        cout << "Pues adivina que tengo en mi bolsa! Tengo un/a " << xy << " justo para ti "<< y << "! \n \n";
    } while (x != 0);
}