#include "listaordenada.h"

using namespace std;

ListaOrdenada::ListaOrdenada(){
}//cnostructor vacio

string ListaOrdenada::toString(){
    stringstream ss;
    for (int i=0; i < lista.size(); i++)
        ss <<""<< lista.at(i) << endl;
    return ss.str();
}//fin to string de ListaOrdenada que concatena todo el contenido del vecto lista

void ListaOrdenada::agregar(int valor){
    int posicion=0;
    //cout << "size de la lista: " << lista.size() << " valor a agregar: " << valor << endl;
    if (lista.empty()){
        //cout << "Entra a cuando lista esta vacia." << endl;
        lista.insert(lista.begin()+0, valor);
    } else {
        if (lista.size() == 1){
            //cout << "Entra a caundo size lista = 1." << endl;
            if (valor <= lista.at(0)){
                lista.insert(lista.begin()+0, valor);
            } else {
                lista.insert(lista.begin()+1, valor);
            }
        } else {//para cuando el size >1
            //cout << "Entra a caundo el size es mayor que 1." << endl;
            for (int i=0; i<lista.size(); i++){
                //cout << "En i = " << i << endl;
                if (valor > lista[i]){
                    posicion=i;
                    if (i == lista.size()-1)
                        posicion = lista.size();
                } else {// para cuando valor<=lista[i]
                    posicion=i;
                    break;
                }
            }
            lista.insert(lista.begin()+posicion, valor);
        }

    }

    //cout << "posicion donde va a agregar " << posicion << endl;
    //cout << "LISTA\n" << toString();
}// fin metodo agregar que agrega de forma ordenada

void ListaOrdenada::eliminarValor(int valor){
    if (!lista.empty()){
        //aqui deberiamos de incoporar una busqueda binaria para buscar el valor a borrar, ya que la lista esta ordenada.
        int posicion= buscar(valor);
        if (posicion>=0)//validacion porque si no encontró a valor regresa -1 y si hagp erase en -1 TRONAZON
            lista.erase(lista.begin()+posicion);
    } else{
        cerr << "La lista en ListaOrdenada esta vacia. No se puede eliminarValor." << endl;
    }
}// fin metodo de eliminar valir

int ListaOrdenada::buscar(int valor){
    //se debe buscar valor en la lista ordenada con busqueda binaria
    if (!lista.empty()){
        /*
        for (int i =0; i < lista.size(); i++){
            if (valor == lista[i])
                return i;
        }
        */
        int centro, inf= 0, sup= lista.size()-1;
        while (inf<=sup){
                centro = ((sup-inf)/2)+inf;
                if (lista.at(centro) == valor)
                    return centro;
                else {
                    if (valor < lista[centro])
                        sup = centro -1;
                    else
                        inf = centro+1;
                }
        }
    } else {
        cerr << "ListaOrdenada esta vacia en buscar" << endl;
    }
    return -1;//devuelve menos 1 porque no lo encontró OJO para que no estalle
}

bool ListaOrdenada::isEmpty(){
    if (lista.empty())
        return true;
    return false;
}//fin metodo

int ListaOrdenada::cantidadNumerosSeguidosDesde(int valor){
    /*
    En esta funcion se busca el valor en la lista, al encontrarlo se avanza desde ahi hasta el final de la lista
    que esta ordenada ascendentemente. Desde que encuentra valor debe ir contando cauntos dígitos estan en la lista que son
    consecutivos como 0 1 2 3 o como 7 8 9 10 por decir unos ejemplos
    PARA PROPOSITOS DE EL AVAILLIST ESTA FUNCION SIEMPRE DEBE RECIBIR 0 EN EL PARAMETRO VALOR
    */
    int contador=0;
    if (!lista.empty()){
        int posicion = buscar(valor);
        //cout << "Posicion de donde comeienza"
        if (posicion >= 0){
            for (int i = posicion; i < lista.size(); i++){
                if (lista.at(i) == valor)
                    contador++;
                else
                    break;
                valor++;
            }
        } else {
            //cerr << "ERROR: La posicion que busca en cantidadNumerosSeguidosDesde no esta en la lista." << endl;
            contador=-1;
        }
    } else {
        cerr << "ERROR: La lista esta vaica en cantidadNumerosSeguidosDesde. " << endl;
    }
    return contador;
}// fin de cantidadNumerosSeguidosDesde

int ListaOrdenada::posicionesAntesDe(int pos){//mETODO
    int contador =-1;//lo empiezo desde cero porque en el availist hay un -1
    for (int i=0; i< lista.size(); i++){
        if (lista.at(i) <= pos)
            contador++;
        else
            break;
    }
    //cout << "Contador en ListaOrdenada :: posicionesAntesDe " << contador << endl;
    return contador;
}// fin cPosicionesAntesDe
