#-------------------------------------------------
#
# Project created by QtCreator 2017-07-07T23:06:53
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialCOM
TEMPLATE = app

RC_ICONS += icon.png

SOURCES += main.cpp\
        mainwindow.cpp \
    portselect.cpp

HEADERS  += mainwindow.h \
    portselect.h

FORMS    += mainwindow.ui \
    portselect.ui

RESOURCES += \
    resource.qrc
