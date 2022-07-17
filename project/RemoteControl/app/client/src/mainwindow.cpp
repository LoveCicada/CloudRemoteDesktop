#include "mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QHostInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_pCControlWnd = nullptr;

    Init();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::Init()
{
    InitCtrl();
    InitData();
    GetClientMachineInfo();
    InitWndSize();
}

void MainWindow::InitData()
{
    {
        //! for test
        m_pIpEdit->setText("172.16.169.26");
        m_pWidthEdit->setText("1680");
        m_pHeightEdit->setText("1050");
    }

}

void MainWindow::InitCtrl()
{
    m_pIpLabel     = new QLabel();
    m_pWidthLabel  = new QLabel();
    m_pHeightLabel = new QLabel();
    m_pIpLabel->setText("ip address:");
    m_pHeightLabel->setText("height:");
    m_pWidthLabel->setText("width:");

    m_pIpEdit       = new QLineEdit();
    m_pWidthEdit    = new QLineEdit();
    m_pHeightEdit   = new QLineEdit();

    QVBoxLayout* pMainLayout    = new QVBoxLayout();
    QHBoxLayout* pAddrLayout    = new QHBoxLayout();
    QHBoxLayout* pWidthLayout   = new QHBoxLayout();
    QHBoxLayout* pHeightLayout  = new QHBoxLayout();

    pAddrLayout->addWidget(m_pIpLabel);
    pAddrLayout->addWidget(m_pIpEdit);
    pAddrLayout->addStretch();

    pWidthLayout->addWidget(m_pWidthLabel);
    pWidthLayout->addWidget(m_pWidthEdit);
    pWidthLayout->addStretch();

    pHeightLayout->addWidget(m_pHeightLabel);
    pHeightLayout->addWidget(m_pHeightEdit);
    pHeightLayout->addStretch();

    pMainLayout->addLayout(pAddrLayout);
    pMainLayout->addLayout(pWidthLayout);
    pMainLayout->addLayout(pHeightLayout);

    QHBoxLayout* pBtLayout = new QHBoxLayout;
    QPushButton* bt = new QPushButton();
    bt->setText("connect");
    pBtLayout->addWidget(bt);
    pBtLayout->addStretch();
    pMainLayout->addLayout(pBtLayout);
    pMainLayout->addStretch();

    QWidget* pMw = new QWidget();
    pMw->setLayout(pMainLayout);
    this->setCentralWidget(pMw);

    connect(bt, SIGNAL(clicked()), this, SLOT(tryconnect()));
}

void MainWindow::InitWndSize()
{
    unsigned short usW = 0;
    unsigned short usH = 0;
    m_clientParams.GetScreenWidth(usW);
    m_clientParams.GetScreenHeight(usH);

    this->setGeometry(QRect(usW / 3, usH / 3, usW / 5, usH / 5));
}

void MainWindow::GetClientMachineInfo()
{
    QDesktopWidget* pDeskWidget = qApp->desktop();
    if (pDeskWidget) {
        qDebug() << __FUNCTION__ << " ok";

        QRect screenRect = pDeskWidget->screenGeometry();
        unsigned short usW = static_cast<unsigned short>(screenRect.width());
        unsigned short usH = static_cast<unsigned short>(screenRect.height());
        m_clientParams.SetScreenWidth(usW);
        m_clientParams.SetScreenHeight(usH);
    }

    QString hostName = QHostInfo::localHostName();
    string strHostName = hostName.toStdString();
    m_clientParams.SetServerName(strHostName);
}

void MainWindow::GetClientUIData(ClientData& clientData)
{
    m_clientData.height = m_pHeightEdit->text().toInt();
    m_clientData.width  = m_pWidthEdit->text().toInt();
    m_clientData.ip     = m_pIpEdit->text().toStdString();

    clientData          = m_clientData;
}

void MainWindow::tryconnect()
{
    GetClientUIData(m_clientData);

#if 0

    m_pScroll = new QScrollArea(this);
    //m_pScroll->setFixedSize(1680, 1050);
    m_pScroll->setWidgetResizable(true);
    QRect rt(0, 0, m_clientData.width, m_clientData.height);
    m_pCControlWnd = new CControlWnd(rt, m_clientData/*, m_pScroll*/);
    m_pScroll->setWidget(m_pCControlWnd);
    this->setCentralWidget(m_pScroll);


#else

    m_pScroll = nullptr;
    QRect rt(0, 0, m_clientData.width, m_clientData.height);
    m_pCControlWnd = new CControlWnd(rt, m_clientData, this);
    this->setCentralWidget(m_pCControlWnd);


#endif // 0

    connect(this, SIGNAL(keyPressed(QKeyEvent*)), m_pCControlWnd, SLOT(keyPressSlot(QKeyEvent*)));
    connect(this, SIGNAL(keyReleased(QKeyEvent*)), m_pCControlWnd, SLOT(keyReleaseSlot(QKeyEvent*)));
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    emit keyPressed(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    emit keyReleased(e);
}


