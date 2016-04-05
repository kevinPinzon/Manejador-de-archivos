#ifndef DNUEVO_H
#define DNUEVO_H

#include <QDialog>
#include <QFile>
#include <vector>
#include "campo.h"
#include <stack>
#include"specialstack.h"

namespace Ui {
    using std::vector;
    using std::stack;

    class Dnuevo;
}

class Dnuevo : public QDialog{
    Q_OBJECT

public:
    explicit Dnuevo(QWidget *parent = 0);
    ~Dnuevo();
     vector<Campo> estructura;
    bool llavePrimariaDisponible=true;
    int cantidadCampos=0;
    SpecialStack availlist;//declaración del availlist

private slots:
    void on_btn_agregarCampo_clicked();

    void on_btn_nuevoArchivo_clicked();

    void on_rb_int_clicked();

    void on_rb_char_clicked();

    void on_rb_decimal_clicked();

    void on_rb_ID_clicked();

    void on_rb_primaria_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dnuevo *ui;
};

#endif // DNUEVO_H
