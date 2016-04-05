#include "cruzar.h"
#include "ui_cruzar.h"
#include <QMessageBox>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Cruzar::Cruzar(vector<Campo> estructura1,vector<Registro> VRegistro1,QString path1,QString path2,QWidget *parent) :
    QDialog(parent),ui(new Ui::Cruzar){
    this->estructura1=estructura1;
    this->VRegistro1=VRegistro1;
    this->path1=path1;
    this->path2=path2;
    //availlist;
    cout<<"comenzo a inicializar"<<endl;
    inicializarArchivo2();
    ui->setupUi(this);
}

Cruzar::~Cruzar(){
    delete ui;
}

void Cruzar::inicializarArchivo2(){//solo puede haber 1campo repetido para que funcione
    fileLEER2.open(path2.toStdString().c_str(), ios::in | ios::out);
    char str[100];
    string linea, sublinea;
    int pos1=0, pos2, cantDeCampos;
    Campo field;
    if(fileLEER2.is_open()){
        fileLEER2.getline(str, 30, ';');
        linea = str;
        pos2 = linea.find(',', 0);
        sublinea = linea.substr(pos1, pos2-pos1);
        cantDeCampos = atoi(sublinea.c_str());
        for (int i = 0; i < cantDeCampos; i++){
            fileLEER2 >> field;
            estructura2.push_back(field);
       // cout<<"CAMPO: "<<i<<" : "<<field.getName()<<endl;
       }
        for(int i=0; i<estructura2.size(); i++)
            cout<<"CAMPO: "<<i<<" : "<<estructura2.at(i).getName()<<endl;

        if(VRegistro1.size()>VRegistro2.size()){
            for(int i=0; i>VRegistro1.size(); i++)
                    VRegistro3.push_back(VRegistro1.at(i));
        }else
            for(int i=0; i>VRegistro2.size(); i++)
                    VRegistro3.push_back(VRegistro2.at(i));

        //Validaciones
        cout<<"empieza a buscar las llaves-----------------------------------------------------"<<endl;
        string nameTemp;
        int pos1=-1,pos2=-1,posLLaveP=-1;
        for(int i=0; i<estructura1.size(); i++){
            cout<<"la llave es: "<<estructura1.at(i).getKeytype()<<endl;
            if(estructura1.at(i).getKeytype()==1){
                posLLaveP=i;
                cout<<"tiene la pos de la llave primaria y es: "<<posLLaveP<<endl;
                estructura3.push_back(estructura1.at(posLLaveP));
            }
            if(estructura1.at(i).getKeytype()==2){
                pos1=i;
                nameTemp=estructura1.at(pos1).getName();
                cout<<"tiene la pos de la llave secundaria y es: "<<pos1<<endl;
            }
                for(int j=0; j<estructura2.size(); j++){
                    if(nameTemp.compare(estructura2.at(j).getName())==0){
                        if(estructura2.at(j).getKeytype()==1)
                            estructura3.push_back(estructura1.at(pos1));
                            pos2=j;
                }
            }
        }
        cout<<"termino del foor"<<endl;
            for(int i=0; i<VRegistro3.size(); i++){
                string data=VRegistro1.at(i).getDatos().at(posLLaveP);
                VRegistro3.at(i).getDatos().insert(VRegistro3.at(i).getDatos().begin()+0,data);
            }


            for(int i=0; i<VRegistro3.size(); i++){
                string data=VRegistro1.at(i).getDatos().at(pos1);
                VRegistro3.at(i).getDatos().insert(VRegistro3.at(i).getDatos().begin()+0,data);
            }


        if(estructura3.empty()){
            QMessageBox::critical(this," No Puede cruzar archivos   ","    No se encontro campos para cruzar con el 2do archivo    ");
        }else{
            llenarComboBox1();
            llenarComboBox2();
            actualizarComboB3();
            int pos01;
            string linea12=path1.toStdString();
            pos01=linea12.find('/',85);
            string sublinea=linea12.substr(pos01,linea12.size()-pos01+4);
            ui->lb_nombre1->setText(sublinea.c_str());

            pos01=0;
            linea12=path2.toStdString();
            pos01=linea12.find('/',85);
            sublinea=linea12.substr(pos01,linea12.size()-pos01+4);
            ui->lb_nombre2->setText(sublinea.c_str());

        }
    } else
        cerr << "No se abrio el archivo para leer en tabla"<<endl;
}
void Cruzar::llenarComboBox1(){
    string temp;
    for(int i=0; i<estructura1.size(); i++){
        temp=estructura1.at(i).getName();
        ui->cb_campos1->addItem(temp.c_str());
    }

}
void Cruzar::llenarComboBox2(){
    string temp;
    for(int i=0; i<estructura2.size(); i++){
        temp=estructura2.at(i).getName();
        ui->cb_campos2->addItem(temp.c_str());
    }

}


void Cruzar::on_btn_addCampo1_clicked(){
    string nameTemp;
    bool campoValido=true;
    if(index1!=-1){
        for(int i=0; i<estructura3.size(); i++){
            nameTemp=estructura3.at(i).getName();
            if(nameTemp.compare(estructura1.at(index1).getName())==0)
                campoValido=false;
        }
        if(campoValido){
            estructura3.push_back(estructura1.at(index1));

            index1=-1;
            actualizarComboB3();
        }else
            QMessageBox::warning(this," No se agrego campo nuevo   ","    el campo seleccionado ya fue agregado anteriormente    ");
    }
}

void Cruzar::on_cb_campos1_currentIndexChanged(int index){
    this->index1=index;
}

void Cruzar::on_cb_campos2_currentIndexChanged(int index){
    this->index2=index;
}

void Cruzar::on_btn_addCampo2_clicked(){
    string nameTemp;
    bool campoValido=true;
    if(index2!=-1){
        for(int i=0; i<estructura3.size(); i++){
            nameTemp=estructura3.at(i).getName();
            if(nameTemp.compare(estructura2.at(index2).getName())==0)
                campoValido=false;
        }
        if(campoValido){
            estructura3.push_back(estructura2.at(index2));
            index2=-1;
            actualizarComboB3();
        }else
            QMessageBox::warning(this," No se agrego campo nuevo   ","    el campo seleccionado ya fue agregado anteriormente    ");
    }
}

void Cruzar::actualizarComboB3(){
    string temp;
    for(int i=0; i<estructura3.size(); i++){
        temp=estructura3.at(i).getName();
        ui->cb_campos3->addItem(temp.c_str());
    }

}



void Cruzar::on_btn_terminar_clicked(){
    if(estructura3.size()>1){
        //se escribe Todo el head
        availlist.push(-1);
        string nombreArchivo=ui->txt_nombreArchivo->text().toStdString();
        stringstream nameA;
        nameA<<nombreArchivo<<".dat";
        ofstream archivo;
        Campo field;
        if(nombreArchivo.empty()){
            QMessageBox::warning(this,"Error","Es necesario que escriba un nombre para el archivo");
        }else{
            if(!estructura3.empty()){
                archivo.open(nameA.str().c_str(), ios::in | ios::out | ios::trunc);
                int cantidadCampos=estructura3.size();
                if(cantidadCampos>9)
                    archivo << 0<<cantidadCampos << ',' << availlist.headAvaillistArchivo(availlist.peek()) << ';';
                else
                    archivo << 00<<cantidadCampos << ',' << availlist.headAvaillistArchivo(availlist.peek()) << ';';
                for (int i = 0; i < estructura3.size(); ++i){
                        field = estructura3.at(i);
                       // cout << field.toString() << endl;
                        archivo << field;
                }
                //llenar registros



                archivo.close();
                this->close();
            }else{
                QMessageBox::warning(this,"Error","Necesita crear al menos un campo");
            }


        }
    }
}

void Cruzar::actualizarRegistros(){


}
/*
falta ir llenando vregistro3
*/
