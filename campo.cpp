#include "campo.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <QString>
#include <QFile>

using namespace std;

Campo::Campo(){
}

Campo::Campo (const char* name, int fieldtype, int size, int sizedecimal, int keytype){
    strcpy(this->name, name);
    this-> fieldtype = fieldtype;
    this-> size = size;
    this-> sizedecimal = sizedecimal;
    this-> keytype = keytype;
}

string Campo::toString()const{
        stringstream ss;
        ss << "Name: " << name << "\tfieldtype: " << fieldtype << "\tsize: " << size << "\tsizedecimal: " << sizedecimal << "\tkeytype: " << keytype;
        return ss.str();
}

string Campo::inttoString(int num, bool edilson) const{
    stringstream ss;
    if (edilson){//edilson es true todo lo que no sea ID
        if(num < 10){
            ss << "00" << num;
        } else if (num <100){
            ss<<"0"<<num;
        } else {
            ss<<num;
        }
    } else {//edilson es false y para ID
        if(num < 10){
            ss << "00000" << num;
        } else if (num <100){
            ss<<"0000"<<num;
        } else if (num < 1000){
            ss<<"000"<<num;
        } else if (num < 10000){
            ss<<"00"<<num;
        } else if (num < 100000){
            ss<<"0"<<num;
        } else {
            ss<<num;
        }
    }
    return ss.str();
}

string Campo::toStringArchivo() const{
    bool bandera=true;
    stringstream ss;
    //ss<<name<<";"<<fieldtype<<";"<<size<<";"<<sizedecimal<<";"<<keytype<<"\n";
    for (int i =0; i<30; i++){
        if (name[i] == '\0')
            bandera = false;
        if (bandera){
            ss << name[i];
        } else {
            ss<<'-';
        }
    }
    ss << ",";

    ss << inttoString(fieldtype, true) << ",";
    ss << inttoString(size, true) << ",";
    ss << inttoString(sizedecimal, true) << ",";
    ss << inttoString(keytype, true) << "\t";

    return ss.str();
}

istream& operator>>(istream& input, Campo& campo){
    input.ignore();
    cout << "char: Nombre de campo" << endl;
    input.getline(campo.name, 30);
    cout << "int: fieldtype donde 0- entero 1- texto 2- decimal 3- ID" << endl;
    input >> campo.fieldtype;
    cout << "int: size para longitud de cadena de texto" << endl;
    input >> campo.size;
    cout << "int: size para digitos decimales" << endl;
    input >> campo.sizedecimal;
    cout << "int: tipo de llave 0- nada 1- primaria 2- secundaria" << endl;
    input >> campo.keytype;
    return input;
}

ofstream& operator<<(ofstream& output, const Campo& campo){
    //std::string registro = toStringArchivo();
    output << campo.toStringArchivo();//registro.c_str();

    return output;
}

ifstream& operator >> (ifstream& input, Campo& campo){
    string linea, sublinea;
    char str[100];
    if (!input.getline(str, 100, '\t'))
        return input;
    //cout << str << endl;
    linea = str;

    int pos1=0, pos2;
    pos2 = linea.find('-');
    sublinea = linea.substr(pos1, pos2-pos1);
    strcpy(campo.name, sublinea.c_str());

    pos1 = linea.find(',');
    pos2 = linea.find(',', pos1+1);
    pos1++;
    sublinea = linea.substr(pos1, pos2-pos1);
    campo.fieldtype = atoi(sublinea.c_str());

    pos1 = pos2+1;
    pos2 = linea.find(',', pos1);
    sublinea = linea.substr(pos1, pos2-pos1);
    campo.size = atoi(sublinea.c_str());

    pos1 = pos2+1;
    pos2 = linea.find(',', pos1);
    sublinea = linea.substr(pos1, pos2-pos1);
    campo.sizedecimal = atoi(sublinea.c_str());

    pos1 = pos2+1;
    pos2 = linea.find(',', pos1);
    sublinea = linea.substr(pos1, pos2-pos1);
    campo.keytype = atoi(sublinea.c_str());

    return input;
}

void Campo::setFieldtype(int valor){
    this->fieldtype = valor;
}

int Campo::getFieldtype()const{
    return this->fieldtype;
}
void Campo::setName(const char* name){
    strcpy(this->name, name);
}
const char* Campo::getName()const{
    //string str = name;
    return this->name;
}
void Campo::setSize(int size){
    this-> size = size;
}
int Campo::getSize()const{
    return this->size;
}
void Campo::setSizedecimal(int sizedecimal){
    this->sizedecimal = sizedecimal;
}
int Campo::getSizedecimal()const{
    return this->sizedecimal;
}
void Campo::setKeytype(int keytype){
    this-> keytype = keytype;
}
int Campo::getKeytype()const{
    return this->keytype;
}
