#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QMainWindow>
#include <QRect>
#include <QTcpSocket>
#include <QHostAddress>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

#include "CMsgReader.h"
#include "CMsgWriter.h"

class CControlWnd : public QWidget
{
    Q_OBJECT

private:
    QImage* image;
    CMsgReader* m_pCMsgReader;
    CMsgWriter* m_pCMsgWriter;
    int frame_width;
    int frame_height;
    int server_screen_width;
    int server_screen_height;

    uchar translateKey(int key);

public:
    CControlWnd(QRect rect, QWidget *parent = 0);
    ~CControlWnd();

signals:
    void mouseMoveTo(int, int);

public slots:
    void frameChanged(QImage*);
    void changeFrameSize(int, int);
    void gotServerScreenSize(int, int);

    void keyPressSlot(QKeyEvent *);
    void keyReleaseSlot(QKeyEvent *);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
};

#endif // CONTROLPANEL_H
