#ifndef EXPORTAR_H
#define EXPORTAR_H
#include <QDialog>
#include "campo.h"
#include"registro.h"
#include<vector>
#include"specialstack.h"

using std::vector;

namespace Ui {
class exportar;
}

class exportar : public QDialog
{
    Q_OBJECT

public:
    explicit exportar(vector<Campo>,vector<Registro>,SpecialStack,QString,QWidget *parent = 0);
    ~exportar();
    Registro registro;
    vector<Registro> VRegistros;
    vector<Campo> estructura;
    QString path;
    SpecialStack availlist;
    ifstream fileLEER;//para leer el archivo
    ofstream fileESCRIBIRExportar;//para escribir el archivo json

private slots:
    void on_btn_cerrar_clicked();

    void on_btn_json_clicked();

    void on_btn_xml_clicked();

    void on_btn_excel_clicked();

private:
    Ui::exportar *ui;
};

#endif // EXPORTAR_H
