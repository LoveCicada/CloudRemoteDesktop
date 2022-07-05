#ifndef CMDTHREAD_H
#define CMDTHREAD_H

/*
@brief SMsgReader - class for reading client command messages on the server side
        (i.e. messages from client to server).
        command msg: mouse, keyboard
*/

#include <QThread>
#include <QTcpSocket>

class SMsgReader : public QThread
{
    Q_OBJECT

private:
    QTcpSocket*  m_pCmdSocket;

    qint64  cmdMsgOffset;
    qint64  clientMsgLength;
    uchar   clientMsgData[8];             //client command msg use 8 byte

public:
    explicit SMsgReader(QTcpSocket* socket, QObject *parent = 0);
    ~SMsgReader();
signals:
    
public slots:
    void readSocketData();
    void readClientMsg();

    void cmdMouseMoveTo();
    void cmdMouseLeftDown();
    void cmdMouseLeftUp();
    void cmdMouseRightDown();
    void cmdMouseRightUp();
    void cmdMouseWheel();
    void cmdScreenSize();
    void cmdMouseDoubleClick();

    void cmdKeyPressed();
    void cmdKeyReleased();

protected:
    void run();
    
};

#endif // CMDTHREAD_H
