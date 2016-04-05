#ifndef AGREGARREGISTRO_H
#define AGREGARREGISTRO_H
#include "campo.h"
#include"registro.h"
#include<vector>
#include <QFile>
#include"specialstack.h"
#include <QDialog>
#include "indice.h"
#include"entradaindice.h"

using std::vector;


namespace Ui {
class AgregarRegistro;
}

class AgregarRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarRegistro(int,Indice,SpecialStack, QString ,vector<Campo>,vector<Registro>, QWidget *parent = 0);
    ~AgregarRegistro();
    vector<Registro> VRegistros;
    vector<Campo> estructura;
    Registro registro;
    ofstream fileESCRIBIR;
    ifstream fileLEER;
    QString path;
    void hacerTabla();
    vector<Registro> actualizarRegistro();
    bool seAgrego=false;
    SpecialStack availlist;
    SpecialStack actualizarAvail();
    Indice indice;
    bool validacionDatos(int,string);
    Indice actualizarIndice();
    EntradaIndice entrada;
    ofstream fileESCRIBIRIndice;
    string nombreArchivoIndice();
    int cantidadRegistros;
    int actualizarCantidadRegistros();
private slots:
    void on_btn_agregarRegi_clicked();


    void on_btn_cerrar_clicked();

private:
    Ui::AgregarRegistro *ui;
};

#endif // AGREGARREGISTRO_H
