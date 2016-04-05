#include "agregarregistro.h"
#include "ui_agregarregistro.h"
#include <QFile>
#include <QTextStream>
#include<QItemSelection>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>
#include <QMessageBox>
#include <stdlib.h>
#include "campo.h"
#include"registro.h"

AgregarRegistro::AgregarRegistro(int cantidadRegistros,Indice indice,SpecialStack availlist,QString path,vector<Campo> estructura,vector<Registro> VRegistros,QWidget *parent) :
    QDialog(parent),ui(new Ui::AgregarRegistro){
    this->availlist=availlist;
    ui->setupUi(this);
    this->path=path;
    //fileESCRIBIR.open(this->path.toStdString().c_str(), ios::in | ios::out);
    this->estructura=estructura;
    this->VRegistros=VRegistros;
    hacerTabla();
    this->indice=indice;
    //EntradaIndice entrada;
    this->cantidadRegistros = cantidadRegistros;
}

void AgregarRegistro::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroAdd;
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
    ui->tw_registroAdd->setRowCount(ui->tw_registroAdd->rowCount()+1);

}

vector<Registro> AgregarRegistro::actualizarRegistro(){
    return VRegistros;
}

AgregarRegistro::~AgregarRegistro()
{
    delete ui;
}

void AgregarRegistro::on_btn_agregarRegi_clicked(){
    QTableWidgetItem *itemTabletTemporal;
    bool DatosCorrectos=true;
    int offset;
    //VALIDACIONES
    //para mejorar la validacion de llaves, se necesita indices.

    int posLLave;
    for(int i=0; i<estructura.size(); i++){
        if(estructura.at(i).getKeytype()==1)
            posLLave=i;
    }
    if(ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,posLLave)->text().isEmpty()){
        QMessageBox::critical(this,"No se ingreso el registro","     Necesita digitar una llave para el nuevo registro    ");
    }else{
        registro.clear();
        itemTabletTemporal = ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,posLLave);

        string valorTipoDatoRecivido=itemTabletTemporal->text().toStdString().c_str();

        if(valorTipoDatoRecivido[0]!='0'&&valorTipoDatoRecivido[0]!='1'&&valorTipoDatoRecivido[0]!='2'&&valorTipoDatoRecivido[0]!='3'&&valorTipoDatoRecivido[0]!='4'
            &&valorTipoDatoRecivido[0]!='5'&&valorTipoDatoRecivido[0]!='6'&&valorTipoDatoRecivido[0]!='7'&&valorTipoDatoRecivido[0]!='8'&&valorTipoDatoRecivido[0]!='9'){
            QMessageBox::critical(this,"No se ingreso el registro","     Necesita digitar un entero en el campo llave de Registro    ");
            itemTabletTemporal->setText(NULL);
        }else{
            int llaveNuevaAingresar= atoi(itemTabletTemporal->text().toStdString().c_str());

            if(indice.Buscar(llaveNuevaAingresar)==-1){
                for(int j=0; j<ui->tw_registroAdd->columnCount(); j++){
                    itemTabletTemporal = ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,j);
                    int datoEsperado=estructura.at(j).getFieldtype();
                    string datoResivido=itemTabletTemporal->text().toStdString();
                    bool continuar;
                    continuar=validacionDatos(datoEsperado,datoResivido);
                    if(continuar){
                        registro.agregarDato(itemTabletTemporal->text().toStdString());

                    }else{
                     QMessageBox::critical(this,"No se ingreso el registro","     datos incorrectos     ");
                      itemTabletTemporal->setText(NULL);
                     DatosCorrectos=false;
                    }
                }
                if(DatosCorrectos){
                //AVAILLIST
                    cout<<"Registro toString en agregar: "<<registro.toString()<<endl;
                    cout<<"Registro toStringArchivo en agregar: "<<registro.toStringArchivo(estructura)<<endl;

                    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);

                    if(availlist.peek()== -1 || availlist.peek()== 0000-1){//si el availlist devuelve -1, se agrega alfinal y listo
                        cout<<"availlist tiene -1"<<endl;                        
                        offset = availlist.getOffsetRegistro()+availlist.getSizeRegistro()*cantidadRegistros;//donde vamos a poner
                        if(VRegistros.empty()){
                            VRegistros.push_back(registro);
                        }else{
                            int posV=VRegistros.size()-1;
                            int posA= availlist.posicionArchivo(posV);
                            int offsetUltimo=(posA*availlist.getSizeRegistro())+availlist.getOffsetRegistro();

                            if((offsetUltimo + availlist.getSizeRegistro())== offset){//agrega en el siguiente del vector
                                VRegistros.push_back(registro);
                                cout<<"agrego en el registro---------------------------"<<endl;
                            }else{
                                cout<<"offsetUltimo es "<<offsetUltimo+availlist.getSizeRegistro()<<endl;
                                cout<<"offset es: "<<offset<<endl;
                            }

                        }
                    }else{//si el availist devuelve distinto a -1
                        cout<<"availlist tiene distinto a -1"<<endl;
                        cout << "La posicion que sale peek del availlist: "<<availlist.peek()<<endl;
                        int sigPosDisponibleArchivo=availlist.peek();
                        offset=availlist.getOffsetRegistro()+sigPosDisponibleArchivo*availlist.getSizeRegistro();//donde vamos a poner
                        int posV=VRegistros.size()-1;
                        int posA= availlist.posicionArchivo(posV);
                        int offsetUltimo=posA*availlist.getSizeRegistro()+availlist.getOffsetRegistro();
                        if(offsetUltimo+availlist.getSizeRegistro()<= offset){

                            if(offsetUltimo+availlist.getSizeRegistro()== offset){//si esto
                                VRegistros.push_back(registro);
                            } else {
                                int posAntes = availlist.buscarVIP(sigPosDisponibleArchivo)-1;//retorna las posiciones borradas antes
                                int posVector = sigPosDisponibleArchivo - posAntes;
                                VRegistros.insert(VRegistros.begin()+posVector,registro);//agrega en una posicion de en medio
                            }
                        }
                        availlist.pop();
                        cout << "La posicion con la que se trabaja del availlist: "<<sigPosDisponibleArchivo<<endl;

                        if (fileESCRIBIR.is_open()){//actualizar hed availlist

                            fileESCRIBIR.clear();
                            fileESCRIBIR.seekp(4);
                            fileESCRIBIR<< availlist.headAvaillistArchivo(availlist.peek());
                         }else
                            QMessageBox::critical(this,"ERROR","     No se pudo abrir el archivo para escritura en agregarRegistro    ");
                    }
                    if (fileESCRIBIR.is_open()){
                        fileESCRIBIR.clear();
                        fileESCRIBIR.seekp(offset);
                        registro.Escribir(fileESCRIBIR, estructura);
                        EntradaIndice entrada (atoi(registro.getUnDato(indice.campoLlave(estructura)).c_str()), offset);//hacemos la nueva entrada para incluirla en el indice
                        indice.Agregar(entrada);
                        fileESCRIBIR.seekp(11);
                        fileESCRIBIR << '1';
                        fileESCRIBIR.seekp(13);
                        cantidadRegistros++;
                        fileESCRIBIR << availlist.cantDeRegistroHeader(cantidadRegistros);

                    } else {
                        cerr << "ERROR: no se pudo abrir el archivo para escritura de registro en agregar registro." << endl;
                    }
                    registro.clear();
                    fileESCRIBIRIndice.open(nombreArchivoIndice().c_str(), ios::in | ios::out | ios::trunc);
                    if (fileESCRIBIRIndice.is_open()){
                        indice.Escribir(fileESCRIBIRIndice);
                        fileESCRIBIRIndice.close();
                        //aqui que NO SE VAYA LA LUZ!!
                        fileESCRIBIR.seekp(11);
                        fileESCRIBIR << '0';
                        fileESCRIBIR.close();
                        QMessageBox::information(this," BRILLANTE   "," Se agrego el registro    ");
                        this->close();
                    } else {
                        cerr << "ERROR: no se pudo abrir el archivo para escritura de indices" << endl;
                    }
                }
            }else{
                QMessageBox::critical(this,"No se ingreso el registro","     La llave que desea ingresar ya esta siendo utilizada por otro registro    ");
                itemTabletTemporal->setText(NULL);
            }
        }
    }
}




void AgregarRegistro::on_btn_cerrar_clicked(){
    if (fileESCRIBIR.is_open())
        fileESCRIBIR.close();
    //seAgrego=false;
    this->close();
}

SpecialStack AgregarRegistro::actualizarAvail(){
    return availlist;
}

bool AgregarRegistro::validacionDatos(int esperado,string recivido){
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
Indice AgregarRegistro::actualizarIndice(){
    return indice;
}
string AgregarRegistro::nombreArchivoIndice(){
    string pathCadena=path.toStdString();
    cout<<"el path es: "<<pathCadena<<endl;
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
int AgregarRegistro::actualizarCantidadRegistros(){
    return cantidadRegistros;
}
