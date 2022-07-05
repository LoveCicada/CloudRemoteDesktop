#ifndef INTERFACE_H
#define INTERFACE_H

#include "windows.h"
#include "Winuser.h"

#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QCursor>
#include <QPoint>
#include "ServerParams.h"

typedef void (*pfnLog)(void* pUser, const std::string& str, int level);

class SMsgHandler
{
public:
    //static QPoint currentCursorPos;
    SMsgHandler();
    static void mouseMoveTo(int x, int y);
    static void mouseLeftDown(int x = -1, int y = -1);
    static void mouseLeftUp(int x = -1, int y = -1);
    static void mouseRightDown(int x = -1, int y = -1);
    static void mouseRightUp(int x = -1, int y = -1);
    static void mouseWheel(int delta, int x = -1, int y = -1);

    static void keyPressed(uchar key);
    static void keyReleased(uchar key);
    static QPoint getCursorPos();
    static void setCursorPos(int, int);
    static QPixmap grapScreen();

    static QPoint transformCoordinate(QPoint);

    static void SetServerParmas(ServerParmas sp);
    static void GetServerParmas(ServerParmas& sp);

private:
    static ServerParmas m_ServerParams;
};

#endif // INTERFACE_H
