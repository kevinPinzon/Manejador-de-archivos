#ifndef CRUZAR_H
#define CRUZAR_H

#include <QDialog>
#include<vector>
#include"campo.h"
#include"registro.h"
#include"specialstack.h"

using std::vector;

namespace Ui {
class Cruzar;
}

class Cruzar : public QDialog
{
    Q_OBJECT

public:
    explicit Cruzar(vector<Campo>,vector<Registro>,QString, QString , QWidget *parent = 0);
    ~Cruzar();
vector<Campo> estructura1;
vector<Campo> estructura2;
vector<Registro> VRegistro1;
vector<Registro> VRegistro2;

SpecialStack availlist;
QString path1;
QString path2;
ifstream fileLEER2;
int index1=-1,index2=-1;

vector<Campo> estructura3;
vector<Registro> VRegistro3;
void inicializarArchivo2();
void llenarComboBox1();
void llenarComboBox2();
void actualizarComboB3();
void actualizarRegistros();
int posicionAdd=0;
private slots:
void on_btn_addCampo1_clicked();

void on_cb_campos1_currentIndexChanged(int index);

void on_cb_campos2_currentIndexChanged(int index);

void on_btn_addCampo2_clicked();

void on_btn_terminar_clicked();

private:
    Ui::Cruzar *ui;
};

#endif // CRUZAR_H
