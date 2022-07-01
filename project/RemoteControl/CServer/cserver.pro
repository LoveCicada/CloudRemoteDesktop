#-------------------------------------------------
#
# Project created by QtCreator 2013-10-13T13:31:08
#
#-------------------------------------------------

QT       += core gui widgets
QT       += network

TARGET = cserver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Command.cpp \
    SMsgHandler.cpp \
    SControler.cpp \
    SMsgReader.cpp \
    SMsgWriter.cpp \
    RWSocket.cpp

HEADERS  += mainwindow.h \
    Command.h \
    SMsgHandler.h \
    SControler.h \
    SMsgReader.h \
    SMsgWriter.h \
    RWSocket.h



