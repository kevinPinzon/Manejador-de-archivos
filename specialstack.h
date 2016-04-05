#ifndef SPECIALSTACK_H
#define SPECIALSTACK_H
#include "listaordenada.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class SpecialStack{
    vector <int> availlist;
    ListaOrdenada VIPList;
    /*
    todas las posiciones que metemos al availlist son en base a i del vector
    osea que empiezan desde 0, y llegan hasta size -1
    */
    int offsetRegistro;
    int sizeRegistro;
    int offsetAvaillist;//el offset justo donde comienza el availlist en el header
public:
    SpecialStack();
    SpecialStack(int);


    string toString();
    int pop();//SE MODIFICÓ EL CODIGO DE ESTE METODO AL INCORPORAR LA LISTAORDENADA
    void push(int);//SE MODIFICÓ EL CODIGO DE ESTE METODO AL INCORPORAR LA LISTAORDENADA
    int peek();
    int posicionArchivo(int);//CAMBIO DE NOMBRE Y SE MODIFICÓ EL CODIGO DE ESTE METODO AL INCORPORAR LA LISTAORDENADA
    bool isEmpty();
    void inicializar(ifstream&);
    /*parametros de inicializar	:
    ifstream& file, int pos(que toma del header), int offsetRegistros, int sizeRegistro(es el tamaño del registro fijo ARLF)
    */
    int siguientePosicionDisponible(string);
    int cadena2Int(string);
    int buscarVIP(int);
    string headAvaillistArchivo(int);//este metodo es para poner el head del avillist en el archio con formato de 6digitos

    int getOffsetRegistro();
    int getSizeRegistro();
    void setOffsetRegistro(int);
    void setSizeRegistro(int);
    void setoffsetAvaillist(int);
    void actualizarAvaillist(vector<int>);

    string cantDeRegistroHeader(int);
};

#endif // SPECIALSTACK_H
