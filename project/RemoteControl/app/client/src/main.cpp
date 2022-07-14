#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");

    MainWindow w;
    w.show();
    
    return a.exec();
}
