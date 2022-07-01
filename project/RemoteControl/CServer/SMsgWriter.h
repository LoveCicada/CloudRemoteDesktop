#ifndef MAPTHREAD_H
#define MAPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QColor>
#include <QImage>
#include <QPixmap>

class SMsgWriter : public QThread
{
    Q_OBJECT

private:

    int dest_width;           //客户端指定的宽度
    int dest_height;          //客户端指定的高度
    int send_width;           //发送图像的宽度
    int send_height;          //发送图像的高度
    int scaleby;              //缩放是依据目的图像的高度还是宽度

    uchar* sent_img_buf;   //buffer of the image that have been sent
    uchar* curt_img_buf;   //buffer of the current image
    uchar* send_data_buf;
    uchar cmd_buf[4];
    int   cmd_buf_fill;

    bool started;

    int          interval;         //帧间时间间隔
    QTcpSocket*  mapSocket;
    QTimer* timer;

public:
    SMsgWriter(QTcpSocket* socket, QObject *parent = 0);
    ~SMsgWriter();

    const static int SCALE_BY_WIDTH  = 1;
    const static int SCALE_BY_HEIGHT = 2;

    void setSendInterval(int i);
    
signals:
    
public slots:
    void sendFrame();
    void readSocketData();
    void readCommand();
    void quit();

protected:
    void run();
    
};

#endif // MAPTHREAD_H
