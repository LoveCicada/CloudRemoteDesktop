#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T14:17:15
#
#-------------------------------------------------

QT       += core gui widgets
QT       += network

TARGET = cclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
	Config.cpp \	
    values.cpp \
    ClientParams.cpp \
    ServerParams.cpp \
    RWSocket.cpp \
	Command.cpp \
    CMsgWriter.cpp \
    CMsgReader.cpp \
    CImgReader.cpp \
    CRenderHelper.cpp \
    CControlWnd.cpp

HEADERS  += mainwindow.h \
	Config.h \
    values.h \
    ClientParams.h \
    ServerParams.h \
    RWSocket.h \
    Command.h \
	consts.h \
    CMsgWriter.h \
    CMsgReader.h \
    CImgReader.h \
    CRenderHelper.h \
    CControlWnd.h
