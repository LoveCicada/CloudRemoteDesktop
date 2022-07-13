#pragma once

/*
@brief CImgReader - class for client read img on the client side.
        (i.e. read img from server to client).
        server params, and img.
*/

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QImage>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class CImgReader : public QThread
{
    Q_OBJECT

private:
    typedef shared_ptr<QTcpSocket> QTcpSocketPtr;
private:
    QTcpSocketPtr m_msgSocket;
    QString     m_address;
    int         m_port;
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

public:

    CImgReader(QString add, int p, int w, int h, QObject *parent = 0);
    ~CImgReader();

    void sendRequestSize(int width, int height);
    void getSubWindow();
    void parseCommand();
    void updateFrame();
    
signals:
    void frameGot(QImage*);
    void frameSizeChanged(int, int);
    
public slots:
    void connectError(QAbstractSocket::SocketError);
    void readDataFromServer();
    void hostConnected();

protected:
    void run();
    
};

