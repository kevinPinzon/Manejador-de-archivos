#include "dnuevo.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include "dver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
  Dnuevo a(this);
    a.exec();
}

void MainWindow::on_pushButton_2_clicked(){
    try {
        QString path(QFileDialog::getOpenFileName(this,tr("Abrir Archivo De Registro"), "./", tr("DAT Files (*.dat)")));
        QFile archivo(path);
        if (!archivo.exists()){
            return;
        }
        if (archivo.isOpen()) {
            archivo.close();
        }
    Dver a(path,this);
    a.exec();

    } catch (...) {

    }

}

void MainWindow::on_btn_salir_clicked(){
    this->close();

}
