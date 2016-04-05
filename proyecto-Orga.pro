#-------------------------------------------------
#
# Project created by QtCreator 2015-11-14T10:15:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyecto-Orga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dnuevo.cpp \
    campo.cpp \
    dver.cpp \
    registro.cpp \
    operacionescampos.cpp \
    agregarregistro.cpp \
    modificarregistro.cpp \
    specialstack.cpp \
    eliminarregistro.cpp \
    cruzar.cpp \
    listaordenada.cpp \
    exportar.cpp \
    buscarrecord.cpp \
    entradaindice.cpp \
    indice.cpp

HEADERS  += mainwindow.h \
    dnuevo.h \
    campo.h \
    dver.h \
    registro.h \
    operacionescampos.h \
    agregarregistro.h \
    modificarregistro.h \
    specialstack.h \
    eliminarregistro.h \
    cruzar.h \
    listaordenada.h \
    exportar.h \
    buscarrecord.h \
    entradaindice.h \
    indice.h

FORMS    += mainwindow.ui \
    dnuevo.ui \
    dver.ui \
    operacionescampos.ui \
    agregarregistro.ui \
    modificarregistro.ui \
    eliminarregistro.ui \
    cruzar.ui \
    exportar.ui \
    buscarrecord.ui
