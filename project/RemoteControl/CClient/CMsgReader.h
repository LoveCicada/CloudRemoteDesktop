#ifndef MAPTHREAD_H
#define MAPTHREAD_H

/*
@brief CMsgReader - class for client read messages on the client side.
        (i.e. read messages from server to client).
        server params, and other.
*/


#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QImage>

class CMsgReader : public QThread
{
    Q_OBJECT

private:
    QTcpSocket* mapSocket;
    QString     address;
    int         port;
    bool socketConnected;

    int request_width;
    int request_height;

    uchar* recv_buf;
    uchar* frame_buf;
    int    frame_buf_fill;
    int    frame_bytes;
    uchar  cmd_buf[8];
    int    cmd_buf_fill;

    bool cmd_got;
    bool frame_size_setted;

    bool cmd_parsed;
    int subX;
    int subY;
    int subWidth;
    int subHeight;
    int subSize;
    int subFill;

public:
    int received_frame_width;
    int received_frame_height;
    QImage*  image;

    CMsgReader(QString add, int p, int w, int h, QObject *parent = 0);
    void sendRequestSize(int width, int height);
    void getSubWindow();
    void parseCommand();
    void updateFrame();
    
signals:
    void frameGot(QImage*);
    void frameSizeChanged(int, int);
    
public slots:
    void readDataFromServer();
    void hostConnected();

protected:
    void run();
    
};

#endif // MAPTHREAD_H
