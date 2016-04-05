#ifndef OPERACIONESCAMPOS_H
#define OPERACIONESCAMPOS_H

#include <QDialog>
#include <vector>
#include "campo.h"

using std::vector;

namespace Ui {
class OperacionesCampos;
}

class OperacionesCampos : public QDialog
{
    Q_OBJECT

public:
    explicit OperacionesCampos(QString,vector <Campo>,QWidget *parent = 0);
    ~OperacionesCampos();
    vector <Campo> estructura;
    Campo field;
    QString path;
    void llenarComboBoxCampos();
    ofstream fileEscribir;
    int index=-1;
    bool llavePrimariaDisponible=false;
    vector<Campo> actualizarEstructura();

private slots:
    void on_btn_modificarCampo_clicked();

    void on_btn_eliminarCampo_clicked();

    void on_btn_cerrar_clicked();

    void on_cb_campos_currentIndexChanged(int index);

private:
    Ui::OperacionesCampos *ui;
};

#endif // OPERACIONESCAMPOS_H
