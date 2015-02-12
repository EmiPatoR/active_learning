#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T16:56:38
#
#-------------------------------------------------


#Author : HRUSTIC Emir

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = active_learning
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    subwindow.cpp \
    wizard.cpp

HEADERS  += mainwindow.h \
    subwindow.h \
    wizard.h

TRANSLATIONS = al_fr.ts al_en.ts

FORMS    += mainwindow.ui \
    subwindow.ui \
    wizard.ui
