#include "CControlWnd.h"
#include "Command.h"


CControlWnd::CControlWnd(QRect rect, ClientData data, QWidget *parent)
    : m_rect(rect), m_clientData(data), QOpenGLWidget(parent)
{
    setGeometry(m_rect);
    setMouseTracking(true);

    Init();
}

CControlWnd::~CControlWnd()
{
    qDebug() << __FUNCTION__;
}

void CControlWnd::Init()
{
    InitData();
}

void CControlWnd::InitData()
{
    m_nServerScreenWidth  = -1;
    m_nServerScreenHeight = -1;
    image = 0;
    frame_width  = -1;
    frame_height = -1;

    m_CRenderHelper = make_shared<CRenderHelper>();
    m_CRenderHelper->SetWindowHanlde(this);

    QString ip = QString::fromStdString(m_clientData.ip);
    int w = static_cast<int>(m_clientData.width);
    int h = static_cast<int>(m_clientData.height);

    m_pCMsgReader = make_shared<CMsgReader>(ip, MAP_SERVER_MSG_PORT, w, h);
    connect(m_pCMsgReader.get(), SIGNAL(readServerParams(const ServerParmas&)), this, SLOT(receiveServerParams(const ServerParmas&)));
    m_pCMsgReader->start();

    m_pCImgReader = make_shared<CImgReader>(ip, MAP_SERVER_IMG_PORT, w, h);
    connect(m_pCImgReader.get(), SIGNAL(frameGot(QImage*)), this, SLOT(frameChanged(QImage*)));
    connect(m_pCImgReader.get(), SIGNAL(frameSizeChanged(int, int)), this, SLOT(changeFrameSize(int, int)));
    m_pCImgReader->start();

    m_pCMsgWriter = make_shared<CMsgWriter>(ip, CMD_SERVER_PORT);
    m_pCMsgWriter->start();
}

void CControlWnd::GetClientParams(ClientParams& cp)
{
    cp = m_clientParams;
}

void CControlWnd::SetClientParams(const ClientParams& cp)
{
    m_clientParams = cp;
}

void CControlWnd::UpdateControlWndRect()
{
    this->setGeometry(m_rect);
    this->update();
}

void CControlWnd::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);

    bool bControl = true;
    m_clientParams.GetControlState(bControl);
    if(!bControl)
        return;

    if(m_nServerScreenWidth < 0 || m_pCImgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCImgReader->received_frame_width || y >= m_pCImgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCImgReader->received_frame_width;
    double off_y = (double)y / m_pCImgReader->received_frame_height;
    x = (int)(m_nServerScreenWidth * off_x);
    y = (int)(m_nServerScreenHeight * off_y);
    m_pCMsgWriter->cmdMouseMoveTo(x, y);
}

void CControlWnd::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);

    bool bControl = true;
    m_clientParams.GetControlState(bControl);

    if(!bControl)
        return;

    if(m_nServerScreenHeight < 0 || m_pCImgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCImgReader->received_frame_width || y >= m_pCImgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCImgReader->received_frame_width;
    double off_y = (double)y / m_pCImgReader->received_frame_height;
    x = (int)(m_nServerScreenWidth * off_x);
    y = (int)(m_nServerScreenHeight * off_y);
    if(e->button() == Qt::LeftButton)
    {
        m_pCMsgWriter->cmdMouseLeftDown(x, y);
    }
    else if(e->button() == Qt::RightButton)
    {
        m_pCMsgWriter->cmdMouseRightDown(x, y);
    }

}

void CControlWnd::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);

    bool bControl = true;
    m_clientParams.GetControlState(bControl);

    if (!bControl)
        return;

    if(m_nServerScreenWidth < 0 || m_pCImgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCImgReader->received_frame_width || y >= m_pCImgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCImgReader->received_frame_width;
    double off_y = (double)y / m_pCImgReader->received_frame_height;
    x = (int)(m_nServerScreenWidth * off_x);
    y = (int)(m_nServerScreenHeight * off_y);
    if(e->button() == Qt::LeftButton)
    {
        m_pCMsgWriter->cmdMouseLeftUp(x, y);
    }
    else if(e->button() == Qt::RightButton)
    {
        m_pCMsgWriter->cmdMouseRightUp(x, y);
    }
}

void CControlWnd::mouseDoubleClickEvent(QMouseEvent *e)
{
    QWidget::mouseDoubleClickEvent(e);

    bool bControl = true;
    m_clientParams.GetControlState(bControl);

    if (!bControl)
        return;

    if(m_nServerScreenWidth < 0 || m_pCImgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCImgReader->received_frame_width || y >= m_pCImgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCImgReader->received_frame_width;
    double off_y = (double)y / m_pCImgReader->received_frame_height;
    x = (int)(m_nServerScreenWidth * off_x);
    y = (int)(m_nServerScreenHeight * off_y);
    m_pCMsgWriter->cmdMouseDoubleClick(x, y);
}

void CControlWnd::wheelEvent(QWheelEvent *e)
{
    QWidget::wheelEvent(e);

    bool bControl = true;
    m_clientParams.GetControlState(bControl);

    if (!bControl)
        return;

    if(m_nServerScreenWidth < 0 || m_pCImgReader->received_frame_width < 0)
        return;
    int x = e->globalX();
    int y = e->globalY();
    if(x >= m_pCImgReader->received_frame_width || y >= m_pCImgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCImgReader->received_frame_width;
    double off_y = (double)y / m_pCImgReader->received_frame_height;
    x = (int)(m_nServerScreenWidth * off_x);
    y = (int)(m_nServerScreenHeight * off_y);
    int d = e->delta();
    m_pCMsgWriter->cmdMouseWheel(d, x, y);
}

void CControlWnd::paintEvent(QPaintEvent *e)
{
#if 0
    qDebug() << "*** paintEvent ***";
#endif // 0
    
    if(image != 0)
    {
        QPainter p(this);
        p.drawImage(QRect(0, 0, frame_width, frame_height), *image);
    }
    QWidget::paintEvent(e);
}

int CControlWnd::translateKey(int key)
{
    int k = key;
    bool legal = true;
    if(k >= Qt::Key_0 && k <= Qt::Key_9)
    {
    }
    else if(k >= Qt::Key_A && k <= Qt::Key_Z)
    {

    }
    else if(k >= Qt::Key_F1 && k <= Qt::Key_F24)
    {
        k &= 0x000000ff;
        k += 0x40;
    }
    else if(k == Qt::Key_Tab)
    {
        k = 0x09;
    }
    else if(k == Qt::Key_Backspace)
    {
        k = 0x08;
    }
    else if(k == Qt::Key_Return)
        k = 0x0d;
    else if(k <= Qt::Key_Down && k >= Qt::Key_Left)
    {
        int off = k - Qt::Key_Left;
        k = 0x25 + off;
    }
    else if(k == Qt::Key_Shift)
        k = 0x10;
    else if(k == Qt::Key_Control)
        k = 0x11;
    else if(k == Qt::Key_Alt)
        k = 0x12;
    else if(k == Qt::Key_Meta)
        k = 0x5b;
    else if(k == Qt::Key_Insert)
        k = 0x2d;
    else if(k == Qt::Key_Delete)
        k = 0x2e;
    else if(k == Qt::Key_Home)
        k = 0x24;
    else if(k == Qt::Key_End)
        k = 0x23;
    else if(k == Qt::Key_PageUp)
        k = 0x21;
    else if(k == Qt::Key_PageDown)
        k = 0x22;
    else if(k == Qt::Key_CapsLock)
        k = 0x14;
    else if(k == Qt::Key_NumLock)
        k = 0x90;
    else if(k == Qt::Key_Space)
        k = 0x20;
    else
        legal = false;
    /*if(legal == false)
        return 0;*/
    return k;
}

void CControlWnd::keyPressEvent(QKeyEvent *e)
{

    bool bControl = true;
    m_clientParams.GetControlState(bControl);

    if (!bControl)
        return;

    int keyVal = e->key();
    quint32 quNativeScanCode = e->nativeScanCode();
    quint32 quNativeVirtualKey = e->nativeVirtualKey();
    quint32 quNativeModifiers = e->nativeModifiers();
    Qt::KeyboardModifiers kModifier = e->modifiers();
    QString str = e->text();

    qDebug() <<"key: " << str
        << "key: " << keyVal
        << "nativeScanCode: " << quNativeScanCode
        << " nativeVirtualKey: " << quNativeVirtualKey
        << " nativeModifiers: " << quNativeModifiers
        << " modifiers: " << static_cast<int32_t>(kModifier);

    int k = translateKey(e->key());
    if(k == 0)
        return;
    m_pCMsgWriter->cmdKeyPress(k, quNativeScanCode, quNativeVirtualKey, kModifier);
    e->ignore();
}

void CControlWnd::keyReleaseEvent(QKeyEvent *e)
{

    bool bControl = true;
    m_clientParams.GetControlState(bControl);

    if (!bControl)
        return;

    int keyVal = e->key();
    quint32 quNativeScanCode = e->nativeScanCode();
    quint32 quNativeVirtualKey = e->nativeVirtualKey();
    quint32 quNativeModifiers = e->nativeModifiers();
    Qt::KeyboardModifiers kModifier = e->modifiers();
    QString str = e->text();

    qDebug() << "key: " << str
        << "key: " << keyVal
        << "nativeScanCode: " << quNativeScanCode
        << " nativeVirtualKey: " << quNativeVirtualKey
        << " nativeModifiers: " << quNativeModifiers
        << " modifiers: " << static_cast<int32_t>(kModifier);

    int k = translateKey(e->key());
    if(k == 0)
        return;
    m_pCMsgWriter->cmdKeyRelease(k, quNativeScanCode, quNativeVirtualKey, kModifier);
    e->ignore();
}

void CControlWnd::keyPressSlot(QKeyEvent *e)
{
    keyPressEvent(e);
}

void CControlWnd::keyReleaseSlot(QKeyEvent *e)
{
    keyReleaseEvent(e);
}

void CControlWnd::receiveServerParams(const ServerParmas& sp)
{
    m_serverParams = sp;
    
    unsigned short usW;
    unsigned short usH;
    m_serverParams.GetScreenWidth(usW);
    m_serverParams.GetScreenHeight(usH);

    getServerScreenSize(usW, usH);

    if (usW != m_rect.width() || usH != m_rect.height())
    {
        QRect rt(0, 0, usW, usH);
        m_rect = rt;
        UpdateControlWndRect();
    }
}

void CControlWnd::frameChanged(QImage* i)
{
    image = i;
    update();
}

void CControlWnd::changeFrameSize(int w, int h)
{
    frame_width  = w;
    frame_height = h;
}

void CControlWnd::getServerScreenSize(int w, int h)
{
    m_nServerScreenWidth = w;
    m_nServerScreenHeight = h;
}
