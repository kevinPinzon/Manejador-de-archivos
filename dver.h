#ifndef DVER_H
#define DVER_H

#include <QDialog>
#include "campo.h"
#include <QFile>
#include <vector>
#include"registro.h"
#include <QTableWidget>
#include"specialstack.h"
#include"indice.h"
#include"entradaindice.h"

using std::vector;

namespace Ui {
class Dver;
}

class Dver : public QDialog
{
    Q_OBJECT

public:
    explicit Dver(QString path,QWidget *parent = 0);
    ~Dver();
    void leerHeader();
    char str[80];
    int NumregistrosAgregados;
    bool existenMasRegistros=true;
    int cantDeCampos,cantidadRegistros;
    vector <Campo> estructura;
    vector <Registro> VRegistros;
    Registro registro;
    QFile archivo;
    QString path;
    int cantidadDeRegistrosEnTabla;
    void llenarTabla();
    ifstream fileLEER;
    ofstream fileESCRIBIR;
    ifstream fileLEERIndice;
    ofstream fileESCRIBIRIndice;
    int row;
    void actualizarRegistro(int);
    int offsetRegistros, sizeRegistro;
    SpecialStack availlist; //declaración de availlist
    string toStringArchivoD1RD(int);
    vector <Campo>cargarHeader(ifstream&);
    void actualizarEstructuraParaTabla(vector<Campo>);
    string nombreArchivoIndice();
    Indice indice;
    EntradaIndice entrada;
    bool indicechuco(ifstream&, ifstream&);
private slots:
    void on_pushButton_clicked();
    
    void on_btn_agregarRegistro_clicked();

    void on_tw_registros_itemClicked(QTableWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_btn_modificarRegistro_clicked();

    void on_btn_eliminarRegistro_clicked();

    void on_pushButton_3_clicked();

    void on_btn_cruzar_clicked();

    void on_btn_operacionesCampos_clicked();

    void on_btn_masRegistros_clicked();

    void on_btn_buscarRegistro_clicked();

    void on_btn_exportar_clicked();

private:
    Ui::Dver *ui;
};

#endif // DVER_H
