#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T15:23:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuFileStorage
TEMPLATE = app


SOURCES += main.cpp\
    DuDatabase.cpp \
    MainWidget.cpp \
    ShowFilesDialog.cpp \
    DuFileDialog.cpp \
    ExtractFileDialog.cpp

HEADERS  += \
    DuDatabase.h \
    MainWidget.h \
    ShowFilesDialog.h \
    DuFileDialog.h \
    ExtractFileDialog.h

FORMS    += \
    MainWidget.ui \
    ShowFilesDialog.ui \
    ExtractFileDialog.ui

QMAKE_CXXFLAGS += -std=gnu++14

RESOURCES += \
    res.qrc
