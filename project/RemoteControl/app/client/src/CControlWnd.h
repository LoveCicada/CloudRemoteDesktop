#pragma once

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
#include <memory>
#include <QOpenGLWidget>

#include "CMsgReader.h"
#include "CMsgWriter.h"
#include "CImgReader.h"
#include "CRenderHelper.h"
#include "ClientParams.h"
#include "ServerParams.h"
#include "ClientData.h"
#include "CKeyAssistant.h"

using std::shared_ptr;
using std::make_shared;

class CControlWnd : public QOpenGLWidget
{
    Q_OBJECT

private:
    typedef shared_ptr<CRenderHelper> CRenderHelperPtr;
    typedef shared_ptr<CMsgReader> CMsgReaderPtr;
    typedef shared_ptr<CMsgWriter> CMsgWriterPtr;
    typedef shared_ptr<CImgReader> CImgReaderPtr;
    typedef shared_ptr<CKeyAssistant> CKeyAssistantPtr;
private:
    QRect m_rect;
    QImage* image;
    CMsgReaderPtr m_pCMsgReader;
    CImgReaderPtr m_pCImgReader;
    CMsgWriterPtr m_pCMsgWriter;
    int frame_width;
    int frame_height;
    int m_nServerScreenWidth;
    int m_nServerScreenHeight;

    //! client params
    ClientParams m_clientParams;

    //! server params
    ServerParmas m_serverParams;

    //!
    ClientData m_clientData;


private:
    CRenderHelperPtr m_pCRenderHelper;
    CKeyAssistantPtr m_pCKeyAssistant;
public:
    explicit CControlWnd(QRect rect, ClientData data, QWidget *parent = 0);
    ~CControlWnd();
    void Init();
    void InitData();
    void InitKeyAssistantCb();

public:

    void GetClientParams(ClientParams& cp);
    void SetClientParams(const ClientParams& cp);
    void UpdateControlWndRect();
signals:
    void mouseMoveTo(int, int);

public slots:
    void receiveServerParams(const ServerParmas& sp);
    void frameChanged(QImage*);
    void changeFrameSize(int, int);
    void getServerScreenSize(int, int);

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
    int translateKey(int key);

protected:
    static void SendKbMsg(void* pOwner, void* cmdData);
};

