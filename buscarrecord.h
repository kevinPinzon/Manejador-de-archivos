#ifndef BUSCARRECORD_H
#define BUSCARRECORD_H
#include"indice.h"
#include"registro.h"
#include"campo.h"
#include <QDialog>

using namespace std;
namespace Ui {

class buscarRecord;
}

class buscarRecord : public QDialog
{
    Q_OBJECT

public:
    explicit buscarRecord(QString,vector<Campo>,int,Indice ,QWidget *parent = 0);
    ~buscarRecord();
    Indice indice;
    int cantDeRegistros;
    void hacerTabla();
    vector<Campo> estructura;
    QString path;
    ifstream fileLEER;

private slots:
    void on_btn_cerrar_clicked();

    void on_btn_buscar_clicked();

private:
    Ui::buscarRecord *ui;
};

#endif // BUSCARRECORD_H
