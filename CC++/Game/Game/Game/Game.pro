#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T11:34:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    tableinterface.cpp \
    path.cpp \
    player.cpp \
    keypress.cpp

HEADERS  += dialog.h \
    tableinterface.h \
    path.h \
    player.h \
    keypress.h

FORMS    += dialog.ui \
    tableinterface.ui

RESOURCES += \
    resource.qrc
