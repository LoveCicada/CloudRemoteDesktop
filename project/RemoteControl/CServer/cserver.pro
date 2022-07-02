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
    ClientParams.cpp \
    ServerParams.cpp \
    Command.cpp \
    SMsgHandler.cpp \
    SControler.cpp \
    SMsgReader.cpp \
    SMsgWriter.cpp \
    SImgWriter.cpp \
    RWSocket.cpp

HEADERS  += mainwindow.h \
    ClientParams.h \
    ServerParams.h \
    Command.h \
    SMsgHandler.h \
    SControler.h \
    SMsgReader.h \
    SMsgWriter.h \
    SImgWriter.h \
    RWSocket.h



