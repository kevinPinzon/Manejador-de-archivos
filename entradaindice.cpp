#include "entradaindice.h"
#include "sstream"

using namespace std;

EntradaIndice::EntradaIndice(){
}

EntradaIndice::EntradaIndice(int llave, int offset){
    this->key = llave;
    this->offset = offset;
}//constructor con parámetros

EntradaIndice:: ~EntradaIndice(){
}//destructor ready

string EntradaIndice::toString(){
    stringstream ss;
    ss << "KEY: " << key << "\tOffset: " << offset;
    return ss.str();
}//fin toString común

string EntradaIndice::toStringArchivo(){
    stringstream ss;
    ss << key << "," << offset << "\t";
    return ss.str();
}// fin de toStringArchivo : 1,0

istream& operator>>(istream& input, EntradaIndice& entrada){
    cout << "Ingrese llave:"<< endl;
    cin>> entrada.key;
    cout << "Ingrese offset:"<< endl;
    cin >> entrada.offset;
    return input;
}// fin operados sobrecargado de cin >>

void EntradaIndice::Escribir(ofstream& archivo){
    if (archivo.is_open()){
        archivo << toStringArchivo();
    } else {
        cerr << "ERROR: No se pudo abrir el archivo para escritura en EntradaIndice::Escribir . " << endl;
    }
}//fin metodo Escribir que manda el stringArchivo al file

bool EntradaIndice::Leer(ifstream& file){
    char str[40];
    string linea, sublinea;
    int pos1;

    if (file.is_open()){
        if (file.getline(str, 20, '\t')){
            linea = str;
            pos1 = linea.find(',', 0);
            sublinea = linea.substr(0, pos1);
            key = atoi(sublinea.c_str());
            pos1++;
            sublinea = linea.substr(pos1, linea.size()-pos1);
            offset = atoi(sublinea.c_str());
        } else {
            return false;
        }
        return true;
    } else {
        cerr << "ERROR: no se pudo abrir el archivo para lectura en EntradaIndice::leer ." << endl;
        return false;
    }
}//fin operador sobrecargado file >> entrada

int EntradaIndice::getKey(){
    return this->key;
}
void EntradaIndice::setKey(int llave){
    key = llave;
}
int EntradaIndice::getOffset(){
    return this->offset;
}
void EntradaIndice::setOffset(int offset){
    this->offset = offset;
}
