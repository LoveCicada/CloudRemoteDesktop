#include "SMsgHandler.h"
#include <QScreen>

int screen_width = 0;
int screen_height = 0;
//int i = 0;

SMsgHandler::SMsgHandler()
{
}

QPoint SMsgHandler::transformCoordinate(QPoint p)
{
    int x = (int)((double)p.x() / screen_width * 65535);
    int y = (int)((double)p.y() / screen_height * 65535);
    return QPoint(x, y);
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
    keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
}

void SMsgHandler::keyReleased(uchar key)
{
    keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
