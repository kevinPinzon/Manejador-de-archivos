#include "modificarregistro.h"
#include "ui_modificarregistro.h"
#include <QFile>
#include <QTextStream>
#include <QItemSelection>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>
#include <stdlib.h>

modificarRegistro::modificarRegistro(Indice indice,SpecialStack availlist,vector<Registro> VRegistros,vector<Campo> estructura,QString path,QWidget *parent) :
    QDialog(parent),ui(new Ui::modificarRegistro){
    ui->setupUi(this);
    this->estructura=estructura;
    this->VRegistros=VRegistros;
    this->path=path;
    this->availlist=availlist;
    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    ui->sp_modifRecord->setMinimum(1);
    this->indice= indice;
    hacerTabla();

}

modificarRegistro::~modificarRegistro(){
    delete ui;
}

void modificarRegistro::on_btn_modifRegistro_clicked(){
   QTableWidgetItem *itemTabletTemporal;
    if(fileESCRIBIR.is_open()){
        int posLLave;
        for(int i=0; i<estructura.size(); i++){
            if(estructura.at(i).getKeytype()==1)
                posLLave=i;
        }
        itemTabletTemporal = ui->tw_registroMod->item(ui->tw_registroMod->rowCount()-1,posLLave);
        string valorTipoDatoRecivido=itemTabletTemporal->text().toStdString().c_str();
        int llaveRecivida=atoi(valorTipoDatoRecivido.c_str());
        if(llaveRecivida==llaveDelRegistro){
            bool DatosCorrectos=true;
            if(valorTipoDatoRecivido[0]!='0'&&valorTipoDatoRecivido[0]!='1'&&valorTipoDatoRecivido[0]!='2'&&valorTipoDatoRecivido[0]!='3'&&valorTipoDatoRecivido[0]!='4'
                &&valorTipoDatoRecivido[0]!='5'&&valorTipoDatoRecivido[0]!='6'&&valorTipoDatoRecivido[0]
                    !='7'&&valorTipoDatoRecivido[0]!='8'&&valorTipoDatoRecivido[0]!='9'){

                QMessageBox::critical(this,"No se ingreso el registro","     Necesita digitar un entero en el campo llave de Registro    ");
                itemTabletTemporal->setText(NULL);

            }else{
                for(int j=0; j<ui->tw_registroMod->columnCount(); j++){
                    itemTabletTemporal = ui->tw_registroMod->item(ui->tw_registroMod->rowCount()-1,j);
                    int datoEsperado=estructura.at(j).getFieldtype();
                    string datoResivido=itemTabletTemporal->text().toStdString();
                    bool continuar;
                    continuar=validacionDatos(datoEsperado,datoResivido);
                    if(continuar){
                        registro.agregarDato(itemTabletTemporal->text().toStdString());
                    }else{
                     DatosCorrectos=false;
                    }
                }
                if(DatosCorrectos){
                    fileESCRIBIR.seekp(offsetModificar);
                    registro.Escribir(fileESCRIBIR,estructura);
                    fileESCRIBIR.close();
                    QMessageBox::information(this," BRILLANTE   "," Se agrego el registro    ");
                    this->close();
                }else{
                    QMessageBox::critical(this,"No se ingreso el registro","     datos incorrectos     ");
                     itemTabletTemporal->setText(NULL);
                }

            }
        }else{
            QMessageBox::critical(this,"No se ingreso el registro","     Necesita digitar la misma llave del Registro    ");
        }

    }else{
        cerr<<"No se pudo abrir el archivo de escritura en el boton terminar de modificar "<<endl;
    }
}


void modificarRegistro::on_btn_cerrar_clicked(){
    this->close();
}

void modificarRegistro::on_btn_visualizar_clicked(){
    llaveModificar=ui->sp_modifRecord->value();
    cout<<" esta es la llave a borrar"<<llaveModificar<<endl;
    if (indice.Buscar(llaveModificar)==-1){
        QMessageBox::critical(this,"ERROR","    La llave que ha ingresado es invalida ");
    }else{
        offsetModificar=indice.Buscar(llaveModificar);
        if(fileLEER.is_open()){
            fileLEER.seekg(offsetModificar);
            Registro registroTemp;
            if(registroTemp.Leer(fileLEER,estructura)){
                ui->tw_registroMod->setRowCount(ui->tw_registroMod->rowCount());
                string cadenaTemp;
                ui->tw_registroMod->setEnabled(true);

                llaveDelRegistro=atoi(registroTemp.getUnDato(indice.campoLlave(estructura)).c_str());

                for(int columnas=0; columnas<ui->tw_registroMod->columnCount(); columnas++){
                    cadenaTemp=registroTemp.getDatos().at(columnas);
                    cout<<registroTemp.getDatos().at(columnas)<<endl;
                    ui->tw_registroMod->setItem(0,columnas,new QTableWidgetItem(cadenaTemp.data()));
                }
                ui->tw_registroMod->setEnabled(true);
            }else{
                cerr<<"No se pudo leer el registro a modificar"<<endl;
            }
        }else{
            cerr<<"no se pudo abrir el archivo de lectura en modificar registro"<<endl;
        }
    }
}

void modificarRegistro::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroMod;
        do{
            tabla->removeRow(0);
        }while(tabla->rowCount());
        QStringList encabezados;
        Campo temp;
        string tempCadena;
        int posTemp;
        for (int cont = 0; cont < estructura.size(); ++cont) {
            temp=estructura.at(cont);
            tempCadena=temp.getName();
            posTemp=tempCadena.find('-');
            tempCadena=tempCadena.substr(0,posTemp);
            QString str(tempCadena.c_str());
            encabezados.append(str);
        }
        tabla->setColumnCount(estructura.size());
        tabla->setHorizontalHeaderLabels(encabezados);
        tabla->setRowCount(tabla->rowCount()+1);
        tabla->setEnabled(true);
}
vector<Registro> modificarRegistro::actualizarRegistros(){
    return VRegistros;
}

bool modificarRegistro::validacionDatos(int esperado,string recivido){
    if(esperado==0 || esperado==2|| esperado==3){
        if(recivido[0]!='0'&&recivido[0]!='1'&&recivido[0]!='2'&&recivido[0]!='3'&&recivido[0]!='4'
                &&recivido[0]!='5'&&recivido[0]!='6'&&recivido[0]!='7'&&recivido[0]!='8'&&recivido[0]!='9'){
            return false;
        }else
            return true;
    }
    if(esperado==1){
            if(!(recivido[0]!='0'&&recivido[0]!='1'&&recivido[0]!='2'&&recivido[0]!='3'&&recivido[0]!='4'
                    &&recivido[0]!='5'&&recivido[0]!='6'&&recivido[0]!='7'&&recivido[0]!='8'&&recivido[0]!='9'&&recivido[0]!='*')){
                return false;
        }else
                return true;
    }
}

