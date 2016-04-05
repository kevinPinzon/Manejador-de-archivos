#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
/*
ListaOrdenada.h
Esta clase mantiene una lista de enteros ordenada de manera ascendente 0 1 2 3 4 5 7 8 11
esta clase tiene metodos especiales que cumplen funciones especificas que ayudan para pasar de posicion en vector
a posicion correspondiente en el archivo
int cantidadNumerosSeguidosDesde(int x) ->  x = 0 casi siempre entonces numeros seguis desede 0
int cantidadNumerosEnIntervalo(int, int)
*/
using namespace std;

class ListaOrdenada{
    vector <int> lista;

public:
    ListaOrdenada();
    string toString();
    void agregar(int);//recibe un valor para insertar en forma ordenada
    void eliminarValor(int);//recibe de parámetro un valor que si esta en la lista debe ser eliminado
    int buscar(int);
    bool isEmpty();

    int cantidadNumerosSeguidosDesde(int);//esta funcion regresa la cantidad de numeros sucesivos que aparecen en la lista desde el parametro
    int posicionesAntesDe(int);//esta funcion regresa cuantos numeros hay en un itervalo donde los parametros son los extremos


};

#endif // LISTAORDENADA_H
