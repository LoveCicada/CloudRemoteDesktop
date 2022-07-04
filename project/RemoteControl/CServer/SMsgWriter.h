#ifndef MAPTHREAD_H
#define MAPTHREAD_H

/*
@brief SMsgWriter - class for server send messages on the server side.
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

class SMsgWriter : public QThread
{
    Q_OBJECT

private:

    ServerParmas m_serverParmas;

    int dest_width;           //�ͻ���ָ���Ŀ��
    int dest_height;          //�ͻ���ָ���ĸ߶�
    int send_width;           //����ͼ��Ŀ��
    int send_height;          //����ͼ��ĸ߶�
    int scaleby;              //����������Ŀ��ͼ��ĸ߶Ȼ��ǿ��

    uchar* sent_img_buf;   //buffer of the image that have been sent
    uchar* curt_img_buf;   //buffer of the current image
    uchar* send_data_buf;
    uchar cmd_buf[4];
    int   cmd_buf_fill;

    bool started;
    
    //! send server msg to client, like server parmas.
    QTcpSocket* m_msgSocket;

public:
    SMsgWriter(QTcpSocket* socket, /*QTcpSocket* msgSocket,*/ ServerParmas sp, QObject *parent = 0);
    ~SMsgWriter();
    void Init();
    void InitData();
public:
    bool checkConnect();
    void sendServerParams();
    void sendMsgToClient();
    
signals:
    
public slots:
    void readMsgFromClient();
    void quit();

protected:
    void run();
    
};

#endif // MAPTHREAD_H
