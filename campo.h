#ifndef CAMPO_H
#define CAMPO_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <QString>
#include <QFile>

using namespace std;

class Campo{
    char name[30];
    int fieldtype;//0-texto 1-entero 2-decimal 3-ID
    int size;
    int sizedecimal;
    int keytype;//0- nada 1- llave primiaria 2- llave secundaria

public:
    Campo();
    Campo(const char*, int, int, int, int);
    string toString()const;
    string inttoString(int, bool) const;
    string toStringArchivo() const;
    friend istream& operator>>(istream&, Campo&);
    friend ofstream& operator << (ofstream&, const Campo&);
    friend ifstream& operator >> (ifstream&, Campo&);

    void setFieldtype(int);
    int getFieldtype()const;
    void setName(const char*);
    const char* getName()const;
    void setSize(int);
    int getSize()const;
    void setSizedecimal(int);
    int getSizedecimal()const;
    void setKeytype(int);
    int getKeytype()const;

    //podriamos poner gets y sets para cambiar cosas acerca de los campos
};
#endif // CAMPO_H
