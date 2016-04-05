#ifndef ENTRADAINDICE_H
#define ENTRADAINDICE_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

/*
EntradaIndice.h
Esta clase representa solo una entrada del índice. Tiene dos atributos que son llave y offset.
Tiene métodos para guardarse en el archivo y también para leer del archivo.
*/

using namespace std;

class EntradaIndice{
    int key;
    int offset;

public:
    EntradaIndice();//aqui manda solo la llave y tiene que poner el offset hasta despues
    EntradaIndice(int, int);//aqui manda las dos cosas, llave y offset
    ~EntradaIndice();

    /* data */
    string toString();
    string toStringArchivo();

    friend istream& operator>>(istream&, EntradaIndice&);
    void Escribir(ofstream&);
    bool Leer(ifstream&);

    int getKey();
    void setKey(int);
    int getOffset();
    void setOffset(int);

    void clear();
};

#endif // ENTRADAINDICE_H
