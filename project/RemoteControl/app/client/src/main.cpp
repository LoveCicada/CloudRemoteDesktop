#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "values.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");

    QDesktopWidget* deskWidget = a.desktop();
    QRect screenRect  = deskWidget->screenGeometry();
    screen_width = screenRect.width();
    screen_height = screenRect.height();

    MainWindow w;
    w.show();
    
    return a.exec();
}
