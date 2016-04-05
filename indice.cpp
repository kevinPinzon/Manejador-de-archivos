#include "indice.h"
#include <vector>
#include <cstdlib>

using namespace std;

Indice::Indice(){
}

Indice::~Indice(){
}// fin destructor

string Indice::toString(){
    stringstream ss;
    if (!indice.empty()){
        for (int i=0; i<indice.size(); i++)
            ss << indice.at(i).toString() << "\n";
    } else {
        cerr << "Vector indice esta vacío en Indice::toString()" << endl;
    }
    return ss.str();
}// fin tostring()

bool Indice::isEmpty(){
    if (indice.empty())
        return true;
    return false;
}// fin isEmpty()

void Indice::Agregar (EntradaIndice entrada){
    //cout << "Entra en agregar" << endl;
    if (indice.empty()){//vector índice vacío
        indice.push_back(entrada);
    } else {//cuando el vector de indice no esta vacío
        if (indice.size() == 1){//cuando solamente tiene una entrada en el índice
            if (indice.at(0).getKey() <= entrada.getKey())
                indice.push_back(entrada);
            else {
                indice.insert(indice.begin()+0, entrada);
            }
        } else {//cuando tiene mas de una entrada en el índice
            //cout << "tiene mas de uno el indice"<<endl;
            for (int i=0; i<indice.size(); i++){
                //cout << "ciclo: " << i << endl;
                if (indice.at(i).getKey() <= entrada.getKey()){
                    if (i == indice.size()-1){
                        indice.push_back(entrada);
                        break;
                    }
                } else {
                    indice.insert(indice.begin()+i, entrada);
                    break;
                }
            }// fin for
        }// fin else para cuando indice.size() > 1
    }
}// mètodo agregar

int Indice::Buscar (int llave){//BUSQUEDA BINARIA !!
    if (!indice.empty()){
        int centro, inf= 0, sup= indice.size()-1;
        while (inf<=sup){
                centro = ((sup-inf)/2)+inf;
                if (indice.at(centro).getKey() == llave)
                    return indice.at(centro).getOffset();
                else {
                    if (llave < indice[centro].getKey())
                        sup = centro -1;
                    else
                        inf = centro+1;
                }
        }
    } else {
        cerr << "ERROR: indice esta vacio en buscar." <<endl;
    }
    return -1;
}// fin buscar

int Indice::BuscarPosicion (int llave){//BUSQUEDA BINARIA !!
    if (!indice.empty()){
        int centro, inf= 0, sup= indice.size()-1;
        while (inf<=sup){
                centro = ((sup-inf)/2)+inf;
                if (indice.at(centro).getKey() == llave)
                    return centro;
                else {
                    if (llave < indice[centro].getKey())
                        sup = centro -1;
                    else
                        inf = centro+1;
                }
        }
    } else {
        cerr << "ERROR: indice esta vacio en buscar." <<endl;
    }
    return -1;
}// fin buscar



void Indice::Eliminar (int llave){
    int posicion = BuscarPosicion(llave);
    if (llave != -1){
        indice.erase(indice.begin()+posicion);
    } else{
        cout << "La llave ingresada no esta en el índice." << endl;
    }
}// cheque

void Indice::Escribir (ofstream& archivo){
    if (archivo.is_open()){
        for (int i=0; i<indice.size();i++)
            indice.at(i).Escribir(archivo);
    } else {
        cerr << "ERROR: no se pudo abrir el archivo para escritura en Indice::Escribir . " << endl;
    }
}// fin

void Indice::Leer (ifstream& file){
    EntradaIndice entrada;
    if (file.is_open()){
        while(entrada.Leer(file))
            indice.push_back(entrada);
    } else {
        cerr << "ERROR: no se pudo abrir el archivo para lectura en Indice::Leer . " << endl;
    }
}

void Indice::indexar(ifstream& file, vector<Campo> estructura, int offsetRegistros){//el archivo que recibe aqui es el de los registros
    cout << "dentro de indexar" << endl;
    Registro regisTemp;
    EntradaIndice entradaTemp;
    if (file.is_open()){
        int posllave=0;
        for (int i=0; i<estructura.size(); i++){
            if (estructura.at(i).getKeytype() == 1){
                posllave= i;
                break;
            }
        }
        string datoTemp;
        int offset = offsetRegistros;
        file.seekg(offsetRegistros);
        while(regisTemp.Leer(file, estructura)){
            if (regisTemp.esValido()){
                datoTemp = regisTemp.getUnDato(posllave);
                //cout << datoTemp << endl;
                entradaTemp.setKey(atoi(datoTemp.c_str()));
                entradaTemp.setOffset(offset);
                Agregar(entradaTemp);
            }
            regisTemp.clear();
            offset = file.tellg();
        }
    }else {
        cerr << "ERROR: no se pudo abrir el archivo para indexar." << endl;
    }
}

int Indice::campoLlave(vector <Campo> estructura){//retorna la posicon del campo llave
    int pos = -1;
    for (int i=0; i<estructura.size(); i++){
        if (estructura.at(i).getKeytype() == 1){
            pos = i;
            break;
        }
    }
    return pos;
}// fin campoLlav

