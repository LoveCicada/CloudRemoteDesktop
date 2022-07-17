#include <QApplication>
#include "CLoginWnd.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");

#if 0

    //! login dialog
    CLoginWnd loginWnd;
    loginWnd.exec();

#else 0

    MainWindow w;
    w.show();
    
#endif // 0

    return a.exec();
}
