#-------------------------------------------------
#
# Project created by QtCreator 2017-11-13T07:57:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaperDraw
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    calibrationdialog.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    calibrationdialog.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    calibrationdialog.ui \
    settingsdialog.ui

LIBS += `pkg-config opencv --libs`

DISTFILES += \
    ../../../../../../home/luisa/Downloads/Designcontest-Outline-Eraser.ico \
    ../../../../../../home/luisa/Downloads/Iconsmind-Outline-Pen.ico
