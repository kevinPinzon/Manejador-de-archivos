#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btn_salir_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
//falta hacer buscar----------------READY
//falta terminar de cruzar archivos
//falta arregalr tabla de buscar----------------READY
