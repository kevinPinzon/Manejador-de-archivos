#ifndef ELIMINARREGISTRO_H
#define ELIMINARREGISTRO_H
#include <QDialog>
#include "campo.h"
#include"registro.h"
#include<vector>
#include"specialstack.h"
#include "indice.h"
#include "listaordenada.h"

using std::vector;

namespace Ui {
class eliminarRegistro;
}

class eliminarRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit eliminarRegistro(int, Indice,SpecialStack,vector<Campo>,vector<Registro>,QString,QWidget *parent = 0);
    ~eliminarRegistro();
    vector<Registro> VRegistros;
    vector<Campo> estructura;
    QString path;
    SpecialStack availlist;
    ofstream fileESCRIBIR;//para marcar el registro y escribir el ultimo rrn
    ifstream fileLEER;//para escribir en el header el rrn del registro borrado
    int RRNaBorrar;
    string toStringArchivoD1RD(int);
    vector<Registro> actualizarRegistros();
    void hacerTabla();
    SpecialStack actualizarAvaillist();
    Indice indice;
    EntradaIndice entrada;
    Indice actualizarIndice();
    ofstream fileESCRIBIRIndice;
    string nombreArchivoIndice();
    int cantidadRegistros,offsetAborrar;
    Registro RegistroAborrar;
    int actualizarCantidadRegistros();
private slots:
    void on_btn_visualizar_clicked();

    void on_btn_borrarRecord_clicked();

    void on_pushButton_3_clicked();

    void on_btn_cancelar_clicked();

    void on_btn_borrarRecordLLAVE_clicked();

    void on_btn_borrarRecordFINAL_clicked();

private:
    Ui::eliminarRegistro *ui;
};

#endif // ELIMINARREGISTRO_H

