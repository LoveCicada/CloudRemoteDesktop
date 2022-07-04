#include "CControlWnd.h"
#include "mainwindow.h"
#include "values.h"
#include "Command.h"

CControlWnd::CControlWnd(QRect rect, QWidget *parent)
    : m_rect(rect), QWidget(parent)
{
    setGeometry(m_rect);
    setMouseTracking(true);

    Init();
}

CControlWnd::~CControlWnd()
{
    qDebug() << __func__;
}

void CControlWnd::Init()
{
    InitData();
}

void CControlWnd::InitData()
{
    server_screen_width = -1;
    server_screen_height = -1;
    image = 0;
    frame_width = -1;
    frame_height = -1;

    m_pCMsgReader = new CMsgReader(addr, MAP_SERVER_IMG_PORT, m_rect.width(), m_rect.height());
    connect(m_pCMsgReader, SIGNAL(frameGot(QImage*)), this, SLOT(frameChanged(QImage*)));
    connect(m_pCMsgReader, SIGNAL(frameSizeChanged(int, int)), this, SLOT(changeFrameSize(int, int)));
    m_pCMsgReader->start();

    m_pCMsgWriter = new CMsgWriter(addr, CMD_SERVER_PORT);
    connect(m_pCMsgWriter, SIGNAL(setServerScreenSize(int, int)), this, SLOT(gotServerScreenSize(int, int)));
    m_pCMsgWriter->run();
}

void CControlWnd::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    if(!control)
        return;

    if(server_screen_width < 0 || m_pCMsgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCMsgReader->received_frame_width || y >= m_pCMsgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCMsgReader->received_frame_width;
    double off_y = (double)y / m_pCMsgReader->received_frame_height;
    x = (int)(server_screen_width * off_x);
    y = (int)(server_screen_height * off_y);
    m_pCMsgWriter->cmdMouseMoveTo(x, y);
}

void CControlWnd::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    if(!control)
        return;

    if(server_screen_width < 0 || m_pCMsgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCMsgReader->received_frame_width || y >= m_pCMsgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCMsgReader->received_frame_width;
    double off_y = (double)y / m_pCMsgReader->received_frame_height;
    x = (int)(server_screen_width * off_x);
    y = (int)(server_screen_height * off_y);
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
    if(!control)
        return;

    if(server_screen_width < 0 || m_pCMsgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCMsgReader->received_frame_width || y >= m_pCMsgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCMsgReader->received_frame_width;
    double off_y = (double)y / m_pCMsgReader->received_frame_height;
    x = (int)(server_screen_width * off_x);
    y = (int)(server_screen_height * off_y);
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
    if(!control)
        return;

    if(server_screen_width < 0 || m_pCMsgReader->received_frame_width < 0)
        return;
    int x = e->pos().x();
    int y = e->pos().y();
    if(x >= m_pCMsgReader->received_frame_width || y >= m_pCMsgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCMsgReader->received_frame_width;
    double off_y = (double)y / m_pCMsgReader->received_frame_height;
    x = (int)(server_screen_width * off_x);
    y = (int)(server_screen_height * off_y);
    m_pCMsgWriter->cmdMouseDoubleClick(x, y);
}

void CControlWnd::wheelEvent(QWheelEvent *e)
{
    QWidget::wheelEvent(e);
    if(!control)
        return;

    if(server_screen_width < 0 || m_pCMsgReader->received_frame_width < 0)
        return;
    int x = e->globalX();
    int y = e->globalY();
    if(x >= m_pCMsgReader->received_frame_width || y >= m_pCMsgReader->received_frame_height)
        return;
    double off_x = (double)x / m_pCMsgReader->received_frame_width;
    double off_y = (double)y / m_pCMsgReader->received_frame_height;
    x = (int)(server_screen_width * off_x);
    y = (int)(server_screen_height * off_y);
    int d = e->delta();
    m_pCMsgWriter->cmdMouseWheel(d, x, y);
}

void CControlWnd::paintEvent(QPaintEvent *e)
{
    qDebug() << "*** paintEvent ***";
    if(image != 0)
    {
        QPainter p(this);
        p.drawImage(QRect(0, 0, frame_width, frame_height), *image);
    }
    QWidget::paintEvent(e);
}

uchar CControlWnd::translateKey(int key)
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
    if(!control)
        return;

    int k = translateKey(e->key());
    if(k == 0)
        return;
    m_pCMsgWriter->cmdKeyPress(k);
    e->ignore();
}

void CControlWnd::keyReleaseEvent(QKeyEvent *e)
{
    if(!control)
        return;

    int k = translateKey(e->key());
    if(k == 0)
        return;
    m_pCMsgWriter->cmdKeyRelease(k);
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

void CControlWnd::gotServerScreenSize(int w, int h)
{
    server_screen_width  = w;
    server_screen_height = h;
}
