#-------------------------------------------------
#
# Project created by QtCreator 2016-01-01T12:36:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EnjambreDeParticulas
TEMPLATE = app

LIBS += -lqwtplot3d -lGLU

SOURCES += main.cpp\
        mainwindow.cpp \
    plot.cpp \
    particulas.cpp

HEADERS  += mainwindow.h \
    funciones.h \
    particulas.h \
    plot.h

FORMS    += mainwindow.ui \
    plot.ui
