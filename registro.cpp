#include "registro.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "campo.h"

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;


Registro::Registro(){
}

Registro::Registro(vector<Campo> estructura){//constructor de un Registro cuando ya tenemos una estructura para mandarle
    string dato = "0";
    for (int i =0; i<estructura.size(); i++)
        datos.push_back(dato);
}

string Registro::toString()const{
    //cout << "size de vector datos " << datos.size() << endl;
    stringstream ss;
    for (int i=0; i<datos.size(); i++)
        ss<<datos.at(i)<<" ";
    return ss.str();
}

string Registro::inttoString(int num, bool edilson) const{
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


string Registro::toStringArchivo(vector<Campo> estructura)const{
    stringstream ss;
    //string valor; aqui pongo el string en datos.at(i)
    for (int i=0; i<datos.size(); i++){
        if (estructura.at(i).getFieldtype() == 0)//entero
            ss<<inttoString(atoi(datos.at(i).c_str()), true);
        if (estructura.at(i).getFieldtype() == 1){//texto
            bool bandera = true;
            int sizeTemp=estructura.at(i).getSize();
            for (int j = 0; j < sizeTemp; ++j){
                if (datos.at(i)[j] == '\0')
                    bandera = false;
                if (bandera){
                    ss << datos.at(i)[j];
                } else {
                    ss<<'-';
                }
            }
        }
        if (estructura.at(i).getFieldtype()== 2){//decimal
            string numerodecimal, parteEntero, parteDecimal;
            int tamanodecimal = estructura.at(i).getSizedecimal();
            numerodecimal = datos.at(i);
            int pos1=0;
            pos1 = numerodecimal.find('.');
            parteEntero = numerodecimal.substr(0, pos1);
            pos1++;
            parteDecimal = numerodecimal.substr(pos1, numerodecimal.size()-pos1);
            ss<< inttoString(atoi(parteEntero.c_str()), true);
            ss<<".";
            for (int j=0; j < tamanodecimal; j++){
                bool bandera = true;
                if (j >= parteDecimal.size())
                    bandera = false;
                if (bandera){
                    ss << parteDecimal[j];
                } else {
                    ss << "0";
                }
            }
        }
        if (estructura.at(i).getFieldtype() == 3)//para cuando es de tipo ID
            ss<<inttoString(atoi(datos.at(i).c_str()), false);
        if (i < datos.size()-1){
            ss << ",";
        } else {
            ss << "\t";
        }
    }
    //cout << "Tamaño del registro: " << sizeof(ss.str()) << endl;
    return ss.str();
}

void Registro::Escribir(ofstream& archivo, vector<Campo> estructura){
    string registry = toStringArchivo (estructura);
    cout<<toStringArchivo(estructura)<<endl;
    cout << "Se escribe un registro de tamaño = " << registry.size()  << endl;
    cout << "Voy a escribir en offset " << archivo.tellp() << endl;
    archivo << registry;
}

bool Registro::Leer(ifstream& archivo, vector<Campo> estructura){
    string linea, sublinea;
    char str[100];
    int pos1=0, pos2;
    cout << "Empezamos a leer desde offset " << archivo.tellg() << endl;
    if (!archivo.getline(str, 100, '\t')){
      //  cout << "NO pudo leer una linea" << endl;
        return false;
    }
    linea = str;
    cout << linea << "  y el size de linea: "<< linea.size() << endl;
    for (int i =0; i < estructura.size(); i++){
        pos2 = linea.find(',', pos1);
        sublinea = linea.substr(pos1, pos2-pos1);
        if (estructura.at(i).getFieldtype() == 0 || estructura.at(i).getFieldtype() == 2 || estructura.at(i).getFieldtype() == 3){
            //cout << "es de tipo entero o ID " << endl;
            while (sublinea[0] == '0'){
                //cout << sublinea.at(0) << endl;
                sublinea.erase(0,1);
            }
        }
        if (estructura.at(i).getFieldtype() == 1){
            pos1 = sublinea.find('-', 0);
            sublinea.erase(pos1, sublinea.size()-pos1);
        }
        pos1 = pos2+1;
        //cout << sublinea << endl;
        agregarDato(sublinea);
    }

    return true;

}


vector<string> Registro::getDatos(){
    return datos;
}

void Registro::agregarDato(string datoN){
    datos.push_back(datoN);
    //cout << "size de datos "<<datos.size()<< endl;
}

void Registro::clear(){
    datos.clear();
}

void Registro::setiarValor0(int cantCampos){
    string dato = "0";
    for (int i=0; i<cantCampos; i++)
        agregarDato(dato);
}//este metodo lo hice para que solo con la estructura pueda calcular la longitud fija que van a tener los registros ARLF

bool Registro::esValido(){
    /*
    este metodo revisa un registro recien levantado y si esta marcado indica que el registro no
    debería de ser incorporado a al vector donde se guardan el resto de registros validos
    */
    bool entonces = true;
    if(!datos.empty()){
        string str = datos.at(0);
        if (str.at(0) == '*')
            entonces = false;
    } else {
        cerr << "ERROR: El vector de datos en el registro actual esta vacío." << endl;
    }
    return entonces;
}

void Registro::setDatos(vector<string> registrosNuevos){
    datos=registrosNuevos;
}
string Registro::getUnDato(int pos){
    string valorRetorno = "-1";
    if (!datos.empty()){
        if (pos>=0 && pos<datos.size())
            valorRetorno = datos.at(pos);
    }
    return valorRetorno;
}// fin metodo getUnDato

bool Registro::setUnDato(int pos, string valor){
    if(datos.empty()){
        datos.push_back(valor);
        return true;
    } else {
        if (pos>=0 && pos<datos.size())
            datos.at(pos) = valor;
        return true;
    }
    return false;
}
