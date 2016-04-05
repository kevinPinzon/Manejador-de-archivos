#include "dver.h"
#include "campo.h"
#include "ui_dver.h"
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include <QFileDialog>
#include<QStandardItemModel>
#include <QMessageBox>
#include"operacionescampos.h"
#include"agregarregistro.h"
#include"modificarregistro.h"
#include "specialstack.h"
#include"eliminarregistro.h"
#include"cruzar.h"
#include"exportar.h"
#include"buscarrecord.h"



Dver::Dver(QString path,QWidget *parent):QDialog(parent),ui(new Ui::Dver){
    this->path = path;
    ui->setupUi(this);
    llenarTabla();
    cantidadDeRegistrosEnTabla=1000;
}

Dver::~Dver()
{
    delete ui;
}
void Dver::llenarTabla(){
    char str[100];
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    string linea, sublinea;
    int pos1=0, pos2, cantDeCampos;
    Campo field;
    if(fileLEER.is_open()){
        fileLEER.clear();
        fileLEER.getline(str, 30, ';');

        linea = str;
        pos2 = linea.find(',', 0);
        sublinea = linea.substr(pos1, pos2-pos1);
        cantDeCampos = atoi(sublinea.c_str());
        cout<<"cantidad de campos: "<<sublinea.c_str()<<endl;

        pos1=pos2+1;
        pos2 = linea.find(',', pos1);

        pos1 = pos2+1;
        pos2 = linea.find(',',pos1);

        pos1 = pos2+1;
        pos2 = linea.find(',',pos1);
        sublinea = linea.substr(pos1, pos2-pos1);
        cantidadRegistros = atoi(sublinea.c_str());
        cout<<"cantidad de registros: "<<sublinea.c_str()<<endl;


        for (int i = 0; i < cantDeCampos; i++){
            fileLEER >> field;
            estructura.push_back(field);
       // cout<<"CAMPO: "<<i<<" : "<<field.getName()<<endl;
       }
        for(int i=0; i<estructura.size(); i++)
            cout<<"CAMPO: "<<i<<" : "<<estructura.at(i).getName()<<endl;

    } else
        cerr << "No se abrio el archivo para leer en tabla"<<endl;
    QTableWidget* tabla=ui->tw_registros;
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
      //  cout<<"ENCABEZADOS: "<<tempCadena<<endl;
        QString str(tempCadena.c_str());
        encabezados.append(str);
    }
    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);

    offsetRegistros = fileLEER.tellg();//tomamos el offset de donde empiezan los registros!!
    cout<<"offset registro, tellg: "<<offsetRegistros<<endl;
    registro.setiarValor0(estructura.size());
    sizeRegistro = registro.toStringArchivo(estructura).size();//tomamos la longitud de un registro de olongitud fija (ARLF)
    registro.clear();
    cout << "Size de un registro de tamaño fijo: " << sizeRegistro << endl;
    availlist.setSizeRegistro(sizeRegistro);
    availlist.setOffsetRegistro(offsetRegistros);
    //cout<<"segun el availlist, el offset de registro empieza: "<<availlist.getOffsetRegistro()<<endl;

    //SE CARGAN REGISTROS
    int cont=0;
    if(fileLEER.is_open()){
        fileLEER.clear();
        fileLEER.seekg(availlist.getOffsetRegistro(),ios::beg);

        while (cont<1000 && registro.Leer(fileLEER, estructura)){
        //    cout << "ciclos en cargar registros: " << cont << endl;
            if (registro.esValido())
                VRegistros.push_back(registro);
            else {
                cerr << "CAYO UNo IVALIDO" << endl;
            }
            registro.clear();
            cont++;
        }
        NumregistrosAgregados=cont;
        cout<<"termino de cargar registros"<<endl;
        availlist.inicializar(fileLEER);
        cout<<"termino inicializar"<<endl;
        stringstream ss;
        ss<<"       "<<availlist.toString()<<"      ";
        QMessageBox::information(this," AvailList   ",ss.str().c_str());

        fileLEERIndice.open(nombreArchivoIndice().c_str(), ios::in | ios::out);

      //  cout<<"antes de indice chuco----------------------------"<<endl;

        if (indicechuco(fileLEER,fileLEERIndice)){
            cout << "Indice chuco = true ! " << endl;
            indice.indexar(fileLEER, estructura, offsetRegistros);
            fileLEERIndice.close();
        } else {
            cout << "Indice chuco = false ! " << endl;
            indice.Leer(fileLEERIndice);
            fileLEERIndice.close();
        }
        cout<<"indice:/n "<<indice.toString();
        fileLEER.close();//cierra el flujo de lectura
        //fileLEER.close();
   }else
        cerr<<"No se pudo abrir el archivo, para lectura de registros"<<endl;
    actualizarRegistro(0);

    tabla->setEnabled(true);
    fileLEER.close();
}


void Dver::on_btn_agregarRegistro_clicked(){
    cout<<"to string availlist: "<<availlist.toString()<<endl;
    AgregarRegistro add(cantidadRegistros, indice,availlist,path,estructura,VRegistros,this);
    add.exec();

        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
        if (fileESCRIBIR.is_open()){
            fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
            if(fileLEER.is_open()){
                fileLEER.clear();
                fileLEER.seekg(availlist.getOffsetRegistro(),ios::beg);
                int cont=0;
                VRegistros.clear();
                while (cont<1000 && registro.Leer(fileLEER, estructura)){
                    if (registro.esValido())
                        VRegistros.push_back(registro);
                    else {
                        cerr << "CAYO UNo IVALIDO" << endl;
                    }
                    registro.clear();
                    cont++;
                }
            }
            //VRegistros=add.actualizarRegistro();
            //for(int i=0; i<VRegistros.size(); i++)
             //   cout<<VRegistros.at(i).toString()<<endl;
            availlist=add.actualizarAvail();
            indice=add.actualizarIndice();
            cantidadRegistros=add.actualizarCantidadRegistros();
            actualizarRegistro(0);
            existenMasRegistros=true;
        }else
            QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura en dVer  ");

}

void Dver::actualizarRegistro(int empezar){

    ui->tw_registros->setRowCount(VRegistros.size());

    Registro registroTemp;
    string cadenaTemp;
    int cont=0;
    for(int i=empezar; i<VRegistros.size(); i++){
        registroTemp=VRegistros.at(i);
        for(int columnas=0; columnas<ui->tw_registros->columnCount(); columnas++){
            cadenaTemp=registroTemp.getDatos().at(columnas);
            ui->tw_registros->setItem(cont,columnas,new QTableWidgetItem(cadenaTemp.data()));
        }
        cont++;
    }
}

void Dver::on_tw_registros_itemClicked(QTableWidgetItem *item){
    row = item->row();

}

void Dver::on_pushButton_2_clicked(){
    for(int i=0; i<registro.getDatos().size(); i++){
        string temp=registro.getDatos().at(i);
        cout<<temp<<"en push cerrar"<<endl;
    }
    fileLEER.close();
    fileESCRIBIR.close();
    this->close();
}

void Dver::on_btn_modificarRegistro_clicked(){
    if(!VRegistros.empty()){
        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
        modificarRegistro modifRecord(indice,availlist,VRegistros,estructura,path,this);
        modifRecord.exec();
        VRegistros=modifRecord.actualizarRegistros();

        fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
        if(fileLEER.is_open()){
            fileLEER.clear();
            fileLEER.seekg(availlist.getOffsetRegistro(),ios::beg);
            int cont=0;
            VRegistros.clear();
            while (cont<1000 && registro.Leer(fileLEER, estructura)){
                if (registro.esValido())
                    VRegistros.push_back(registro);
                else {
                    cerr << "CAYO UNo IVALIDO" << endl;
                }
                registro.clear();
                cont++;
            }
        }


        actualizarRegistro(0);
    }else{
         QMessageBox::warning(this,"ERROR","       No existen registros que modificar  ");
    }
}

void Dver::on_btn_eliminarRegistro_clicked(){
   if(!VRegistros.empty()){
    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
    eliminarRegistro elimRecord(cantidadRegistros, indice,availlist,estructura,VRegistros,path,this);
    elimRecord.exec();
    availlist=elimRecord.actualizarAvaillist();

    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    if(fileLEER.is_open()){
        fileLEER.clear();
        fileLEER.seekg(availlist.getOffsetRegistro(),ios::beg);
        int cont=0;
        VRegistros.clear();
        while (cont<1000 && registro.Leer(fileLEER, estructura)){
            if (registro.esValido())
                VRegistros.push_back(registro);
            else {
                cerr << "CAYO UNo IVALIDO" << endl;
            }
            registro.clear();
            cont++;
        }
    }

    indice=elimRecord.actualizarIndice();
    cantidadRegistros=elimRecord.actualizarCantidadRegistros();
    actualizarRegistro(0);
   }else{
        QMessageBox::warning(this,"ERROR","       No existen registros que borrar  ");
   }

}

void Dver::on_btn_cruzar_clicked(){
            QMessageBox::warning(this,"ERROR","       En construccion......  ");
   /* try {
        QString path2(QFileDialog::getOpenFileName(this,tr("Abrir Archivo De Registro"), "./", tr("DAT Files (*.dat)")));
        QFile archivo(path2);
        if (!archivo.exists()){
            return;
        }
        if (archivo.isOpen()) {
            archivo.close();
        }
    Cruzar cruzar(estructura,VRegistros,path,path2,this);
    cruzar.exec();

    } catch (...) {
    }*/
}

void Dver::on_btn_operacionesCampos_clicked(){
    if(VRegistros.empty() && availlist.peek()==-1){
            OperacionesCampos operacionesC(path,estructura,this);
            operacionesC.exec();
            estructura=operacionesC.actualizarEstructura();
            actualizarEstructuraParaTabla(estructura);
    }else
        QMessageBox::warning(this," No se puede ejecutar esta opcion    "," Existen registros agregados en el archivo   ");
}

void Dver::actualizarEstructuraParaTabla(vector<Campo> estrucNueva){
    QTableWidget* tabla=ui->tw_registros;
    QStringList encabezados;
    Campo temp;
    string tempCadena;
    int posTemp;
    for (int cont = 0; cont < estrucNueva.size(); ++cont) {
        temp=estructura.at(cont);
        tempCadena=temp.getName();
        posTemp=tempCadena.find('-');
        tempCadena=tempCadena.substr(0,posTemp);
        cout<<"ENCABEZADOS: "<<tempCadena<<endl;
        QString str(tempCadena.c_str());
        encabezados.append(str);
    }
    tabla->setColumnCount(estrucNueva.size());
    tabla->setHorizontalHeaderLabels(encabezados);

    offsetRegistros = fileLEER.tellg();//tomamos el offset de donde empiezan los registros!!
    cout<<"offset registro, tellg: "<<offsetRegistros<<endl;
    registro.setiarValor0(estrucNueva.size());
    sizeRegistro = registro.toStringArchivo(estrucNueva).size();//tomamos la longitud de un registro de olongitud fija (ARLF)
    registro.clear();
    cout << "Size de un registro de tamaño fijo: " << sizeRegistro << endl;
    availlist.setSizeRegistro(sizeRegistro);
    availlist.setOffsetRegistro(offsetRegistros);
    cout<<"segun el availlist, el offset de registro empieza: "<<availlist.getOffsetRegistro()<<endl;

    availlist.inicializar(fileLEER);
    cout<<"termino inicializar"<<endl;
    stringstream ss;
    ss<<"       "<<availlist.toString()<<"      ";
    QMessageBox::information(this," AvailList   ",ss.str().c_str());
    actualizarRegistro(0);
    tabla->setEnabled(true);
    fileLEER.close();
}

void Dver::on_btn_masRegistros_clicked(){
   int tempCantidadAnteriorDeRegistros=cantidadDeRegistrosEnTabla;
    cantidadDeRegistrosEnTabla+=1000;
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    if(fileLEER.is_open()){
      //  fileLEER.clear();
        fileLEER.seekg(availlist.getOffsetRegistro(),ios::beg);
        int cont=0;
        while (cont<cantidadDeRegistrosEnTabla && registro.Leer(fileLEER, estructura)){
            if (registro.esValido())
                VRegistros.push_back(registro);
            else {
                cerr << "CAYO UNo IVALIDO" << endl;
            }
            registro.clear();
            cont++;
        }
    fileLEER.close();
    }


    actualizarRegistro(1000);
}

void Dver::on_btn_buscarRegistro_clicked(){
    if(!VRegistros.empty()){
        buscarRecord buscarR(path,estructura,cantDeCampos,indice,this);
        buscarR.exec();
    }else{
         QMessageBox::warning(this,"ERROR","       No existen registros  ");
    }
}


void Dver::on_btn_exportar_clicked(){
    exportar exp(estructura,VRegistros,availlist,path,this);
    exp.exec();
}

string Dver::nombreArchivoIndice(){
    string pathCadena=path.toStdString();
  //  cout<<"el path es: "<<pathCadena<<endl;
    bool hayplecas=true;
    int pos1=0,pos2=0;
    pos2=pathCadena.find('/',pos1);
    while(hayplecas){
        if(pos2==-1)
            hayplecas=false;
        else{
            pos1=pos2+1;
            pos2=pathCadena.find('/',pos1);
        }
    }
    pathCadena.erase(0,pos1);
    stringstream ss;
    ss<<"Indice"<<pathCadena;
    return ss.str();
}

bool Dver::indicechuco (ifstream& file, ifstream& fileInd){
    //cout << "Entró a indicechuco" << endl;
    char str[25];
    string linea;
    if (fileInd.is_open()){
        if (file.is_open()){//es el de registros
            file.clear();
            file.seekg(0, ios::beg);
        //    cout << "offset en indice chuco " << file.tellg() << endl;
            if (file.getline(str, 25, ';')){
                linea = str;
                cout << linea << endl;
                if (linea.at(11) == '0')
                    return false;
                else
                    return true;
            }

        }else {
            cerr << "ERROR: no se pudo abrir el archivo para lectura en indicechucho. " << endl;
        }
    } else {
        cerr << "No hay archivo de indices todavia" << endl;
    }
    return true;
}
