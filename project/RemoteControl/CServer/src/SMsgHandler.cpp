#include "SMsgHandler.h"
#include <QScreen>
#include <QDebug>

ServerParmas SMsgHandler::m_ServerParams;

SMsgHandler::SMsgHandler()
{
}

QPoint SMsgHandler::transformCoordinate(QPoint p)
{
    unsigned short usW = 0;
    unsigned short usH = 0;
    m_ServerParams.GetScreenWidth(usW);
    m_ServerParams.GetScreenHeight(usH);

    if (usW == 0 || usH == 0) {
        qDebug() << __func__ << " error, screen Width or Height is zero *****";
    }

    int x = (int)((double)p.x() / usW * 65535);
    int y = (int)((double)p.y() / usH * 65535);
    return QPoint(x, y);
}

void SMsgHandler::SetServerParmas(ServerParmas sp)
{
    m_ServerParams = sp;
}

void SMsgHandler::GetServerParmas(ServerParmas& sp)
{
    sp = m_ServerParams;
}

void SMsgHandler::mouseMoveTo(int x, int y)
{
    QPoint p = transformCoordinate(QPoint(x, y));
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, p.x(), p.y(), 0, 0);
}

void SMsgHandler::mouseLeftDown(int x, int y)
{
    QPoint p;
    if(x < 0 || y < 0)
    {
        p = getCursorPos();
    }
    else
    {
        p = transformCoordinate(QPoint(x, y));
    }
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, p.x(), p.y(), 0, 0);
}

void SMsgHandler::mouseLeftUp(int x, int y)
{
    QPoint p;
    if(x < 0 || y < 0)
    {
        p = getCursorPos();
    }
    else
    {
        p = transformCoordinate(QPoint(x, y));
    }
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, p.x(), p.y(), 0, 0);
}

void SMsgHandler::mouseRightDown(int x, int y)
{
    QPoint p;
    if(x < 0 || y < 0)
    {
        p = getCursorPos();
    }
    else
    {
        p = transformCoordinate(QPoint(x, y));
    }
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, p.x(), p.y(), 0, 0);
}

void SMsgHandler::mouseRightUp(int x, int y)
{
    QPoint p;
    if(x < 0 || y < 0)
    {
        p = getCursorPos();
    }
    else
    {
        p = transformCoordinate(QPoint(x, y));
    }
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, p.x(), p.y(), 0, 0);
}

void SMsgHandler::mouseWheel(int delta, int x, int y)
{
    QPoint p;
    if(x < 0 || y < 0)
    {
        p = getCursorPos();
    }
    else
    {
        p = transformCoordinate(QPoint(x, y));
    }
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL, p.x(), p.y(), delta, 0);
}

QPoint SMsgHandler::getCursorPos()
{
    return QCursor::pos();
}

QPixmap SMsgHandler::grapScreen()
{
    return QPixmap::grabWindow(QApplication::desktop()->winId());
}

void SMsgHandler::setCursorPos(int x, int y)
{
    QCursor::setPos(x, y);
}

void SMsgHandler::keyPressed(uchar key)
{
    short sVkCode = VkKeyScan(key);

    //! virtual key code must between 1 and 254, [1, 254]
    if ( sVkCode < 1 || sVkCode > 254) {
        sVkCode = key;
    }

    BYTE bScan = MapVirtualKey(sVkCode, 0);
    keybd_event(sVkCode, bScan, KEYEVENTF_EXTENDEDKEY, 0);
}

void SMsgHandler::keyReleased(uchar key)
{
    short sVkCode = VkKeyScan(key);

    //! virtual key code must between 1 and 254, [1, 254]
    if (sVkCode < 1 || sVkCode > 254) {
        sVkCode = key;
    }

    BYTE bScan = MapVirtualKey(sVkCode, 0);
    keybd_event(sVkCode, bScan, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
