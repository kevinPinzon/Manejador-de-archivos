#include "operacionescampos.h"
#include "ui_operacionescampos.h"
#include "campo.h"
#include<QStandardItemModel>
#include<QComboBox>
#include <QDebug>
#include <QFile>
#include <vector>
#include <sstream>
#include <QMessageBox>

using namespace std;

OperacionesCampos::OperacionesCampos(QString path,vector <Campo> estructura,QWidget *parent):QDialog(parent),ui(new Ui::OperacionesCampos){
    this->estructura=estructura;
    ui->setupUi(this);
    llenarComboBoxCampos();
    this->path=path;
    this->fileEscribir.open(path.toStdString().c_str(), ios::in | ios::out | ios::trunc);
}

OperacionesCampos::~OperacionesCampos(){
    delete ui;
}

void OperacionesCampos::llenarComboBoxCampos(){
    string temp;
    for(int i=0; i<estructura.size(); i++){
        temp=estructura.at(i).getName();
        ui->cb_campos->addItem(temp.c_str());
    }
}

void OperacionesCampos::on_btn_modificarCampo_clicked(){
    //VALIDACIONES
    bool camposLLenos=true;
    bool nombreDisponible=true;
    bool escribir=false;
    if(ui->txt_nameCampo->text().toStdString().empty())
        camposLLenos=false;

    if(index!=-1 && camposLLenos){
        for(int i=0; i<estructura.size(); i++){
            string temp=estructura.at(i).getName();
            if(temp.compare(ui->txt_nameCampo->text().toStdString())==0)
                nombreDisponible=false;
        }
    }
    if(nombreDisponible){
        estructura.erase(estructura.begin()+index);
        //estructura.at(index).setName(ui->txt_nameCampo->text().toStdString().c_str());
        escribir=true;
    }else
        QMessageBox::critical(this,"No se ha modificado el campo","     Ya se tiene un campo con el mismo nombre    ");
    if(escribir){
        string nombreCampo=ui->txt_nameCampo->text().toStdString();
        int tipoCampo=-1;//1-entero 2-char  3-decimal   4-ID
        if(ui->rb_int->isChecked())//ENTERO
            tipoCampo=0;
        if(ui->rb_char->isChecked())//CHAR
            tipoCampo=1;
        if (ui->rb_decimal->isChecked())//DECIMAL
            tipoCampo=2;
        if (ui->rb_ID->isChecked())//ID
            tipoCampo=3;

        int longitudCampo=ui->sp_longitud->value();
        int decimal=ui->sp_decimales->value();

        int llave=0;
        if(ui->rb_primaria->isChecked())
            llave=1;
        if (ui->rb_secundaria->isChecked())
            llave=2;

        Campo campoNuevo(nombreCampo.c_str(),tipoCampo,longitudCampo,decimal,llave);
        estructura.insert(estructura.begin()+index,campoNuevo);

        int cantidadCampos=estructura.size();
        if(fileEscribir.is_open()){
            if(cantidadCampos<10)
                fileEscribir << "00"<<cantidadCampos << ',' << "0000-1" << ';';
            else
                fileEscribir <<"0"<<cantidadCampos << ',' << "0000-1" << ';';

            for (int i = 0; i < estructura.size(); ++i){
                    fileEscribir << estructura.at(i);
            }
            fileEscribir.close();
            this->close();
            ui->txt_nameCampo->setText(NULL);
            ui->sp_longitud->setValue(1);

        }else
            QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura en opercaiones campos  ");
    }
}

void OperacionesCampos::on_btn_eliminarCampo_clicked(){
    if(index!=-1){
        if(fileEscribir.is_open()){
            if(estructura.at(index).getKeytype()!=1)
                estructura.erase(estructura.begin()+index);
            else
                QMessageBox::warning(this,"ERROR","       No puede borrar el campo que es llave primaria  ");

            int cantidadCampos=estructura.size();
            if(cantidadCampos<10)
                fileEscribir << "00"<<cantidadCampos << ',' << "0000-1" << ';';
            else
                fileEscribir <<"0"<<cantidadCampos << ',' << "0000-1" << ';';

            for (int i = 0; i < estructura.size(); ++i){
                    fileEscribir << estructura.at(i);
            }
            fileEscribir.close();
            this->close();
            ui->txt_nameCampo->setText(NULL);
            ui->sp_longitud->setValue(1);
            QMessageBox::information(this," BRILLANTE    ","       Se ha eliminado el campo exitosamente!  ");
        }else
            QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura en opercaiones campos  ");
    }else{
        cout<<"Algo raro paso con el index"<<endl;
    }


}

void OperacionesCampos::on_cb_campos_currentIndexChanged(int index){
    ui->sp_decimales->setValue(0);
    ui->sp_longitud->setValue(1);
    Campo temp;
    this->index=index;
    temp=estructura.at(index);
    ui->txt_nameCampo->setText(temp.getName());
    cout<<temp.getFieldtype()<<endl;
    if(temp.getFieldtype()==0){
       ui->rb_int->setChecked(true);
       ui->sp_decimales->setEnabled(false);
       ui->sp_longitud->setEnabled(false);
    }

    if(temp.getFieldtype()==1){
        ui->rb_char->setChecked(true);
        ui->sp_decimales->setEnabled(false);
        ui->sp_longitud->setEnabled(true);
        ui->sp_longitud->setValue(temp.getSize());
    }

    if(temp.getFieldtype()==2){
       ui->rb_decimal->setChecked(true);
       ui->sp_decimales->setEnabled(true);
       ui->sp_decimales->setValue(temp.getSizedecimal());
       ui->sp_longitud->setVisible(false);
    }

    if(temp.getFieldtype()==3){
       ui->rb_ID->setChecked(true);
       ui->sp_decimales->setEnabled(false);
       ui->sp_longitud->setEnabled(false);
    }

    if(temp.getKeytype()==0){
        ui->rb_noEsLLave->setChecked(false);
        ui->rb_noEsLLave->setEnabled(false);
        ui->rb_primaria->setEnabled(false);
        ui->rb_secundaria->setEnabled(false);
    }
    if(temp.getKeytype()==1){
        ui->rb_primaria->setChecked(false);
        ui->rb_primaria->setEnabled(false);
        ui->rb_secundaria->setEnabled(false);
        ui->rb_noEsLLave->setEnabled(false);
    }
    if(temp.getKeytype()==2){
        ui->rb_secundaria->setChecked(false);
        ui->rb_secundaria->setEnabled(false);
        ui->rb_primaria->setEnabled(false);
        ui->rb_noEsLLave->setEnabled(false);
    }
}

vector<Campo> OperacionesCampos::actualizarEstructura(){
    return estructura;
}









