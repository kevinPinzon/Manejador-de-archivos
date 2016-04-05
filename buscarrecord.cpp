#include "buscarrecord.h"
#include "ui_buscarrecord.h"
#include <QFile>
#include <QTextStream>
#include<QItemSelection>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>
#include <QMessageBox>

buscarRecord::buscarRecord(QString path,vector<Campo>estructura,int cantDeRegistros,Indice indice,QWidget *parent) :
    QDialog(parent),ui(new Ui::buscarRecord){
    ui->setupUi(this);
    this->cantDeRegistros=cantDeRegistros;
    this->indice=indice;
    ui->sp_elimRecord->setMinimum(1);
    this->estructura=estructura;
    this->path=path;
    hacerTabla();
    fileLEER.open(this->path.toStdString().c_str(), ios::in | ios::out);
}

buscarRecord::~buscarRecord()
{
    delete ui;
}

void buscarRecord::on_btn_cerrar_clicked(){
    this->close();
}

void buscarRecord::on_btn_buscar_clicked(){
    int llaveBuscar=ui->sp_elimRecord->value();
    int offset=indice.Buscar(llaveBuscar);

    ui->tw_registroBuscar->setRowCount(ui->tw_registroBuscar->rowCount());
    Registro registroTemp;
    string cadenaTemp;
    if(fileLEER.is_open()){
        if(offset!=-1){
            fileLEER.seekg(offset);
            registroTemp.Leer(fileLEER,estructura);
            ui->tw_registroBuscar->setEnabled(true);

            for(int columnas=0; columnas<ui->tw_registroBuscar->columnCount(); columnas++){
                cadenaTemp=registroTemp.getDatos().at(columnas);
                cout<<registroTemp.getDatos().at(columnas)<<endl;
                ui->tw_registroBuscar->setItem(0,columnas,new QTableWidgetItem(cadenaTemp.data()));
            }
            ui->tw_registroBuscar->setEnabled(false);

        }else{
            QMessageBox::critical(this,"ERROR","    no se encontro la llave ingresada ");
            cerr<<"no se encontro la llave ingresada"<<endl;
        }

    }else{
        cerr<<"no se pudo abrir el archivo en buscar"<<endl;
    }
}

void buscarRecord::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroBuscar;
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
        ui->tw_registroBuscar->setRowCount(ui->tw_registroBuscar->rowCount()+1);
        ui->tw_registroBuscar->setEnabled(false);
}
