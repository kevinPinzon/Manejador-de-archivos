#ifndef INDICE_H
#define INDICE_H
/*
Indice.h
esta clase representa el indice lineal para un ARLF
*/
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "entradaindice.h"
#include "registro.h"
#include "campo.h"

using namespace std;

class Indice{
    vector <EntradaIndice> indice;
public:
    Indice();
    ~Indice();
    int campoLlave(vector <Campo>);//regresa la posicion del campo llave en la estructura
    string toString();
    bool isEmpty();
    int BuscarPosicion (int);
    /* data */
    void Agregar (EntradaIndice);
    int Buscar (int);
    void Eliminar (int);

    void Escribir (ofstream&);
    void Leer (ifstream&);

    void indexar(ifstream&, vector<Campo>, int);


};

#endif // INDICE_H
