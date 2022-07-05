#pragma once

/*
@brief SImgWriter - class for server send messages on the server side.
        (i.e. messages send client from server).
        server --> client
        command msg: mouse, keyboard
*/

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QColor>
#include <QImage>
#include <QPixmap>

#include "ServerParams.h"

class SImgWriter : public QThread
{
    Q_OBJECT

private:

    ServerParmas m_serverParmas;

    unsigned short dest_width;           //客户端指定的宽度
    unsigned short dest_height;          //客户端指定的高度
    unsigned short send_width;           //发送图像的宽度
    unsigned short send_height;          //发送图像的高度
    int scaleby;              //缩放是依据目的图像的高度还是宽度

    uchar* sent_img_buf;   //buffer of the image that have been sent
    uchar* curt_img_buf;   //buffer of the current image
    uchar* send_data_buf;
    uchar cmd_buf[4];
    int   cmd_buf_fill;

    bool started;

    int         interval;         //帧间时间间隔

    //! send server desk img to client
    QTcpSocket* m_imgSocket;
    
    QTimer* timer;

public:
    SImgWriter(QTcpSocket* imgSocket, ServerParmas sp, QObject *parent = 0);
    ~SImgWriter();

    const static int SCALE_BY_WIDTH  = 1;
    const static int SCALE_BY_HEIGHT = 2;

    void setSendInterval(int i);
    
public:
    void sendServerParams();
    bool checkConnect();
signals:
    
public slots:
    void sendFrame();
    void readDataFromClient();
    void readCommand();
    void quit();

protected:
    void run();
    
};

