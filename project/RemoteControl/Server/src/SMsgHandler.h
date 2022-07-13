#pragma once

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

    static void keyPressed(int32_t key, int32_t scanCode, int32_t virtualKey, int32_t modifier);
    static void keyReleased(int32_t key, int32_t scanCode, int32_t virtualKey, int32_t modifier);
    static QPoint getCursorPos();
    static void setCursorPos(int, int);
    static QPixmap grapScreen();

    static QPoint transformCoordinate(QPoint);

    static void SetServerParmas(ServerParmas sp);
    static void GetServerParmas(ServerParmas& sp);

private:
    static ServerParmas m_ServerParams;
};

