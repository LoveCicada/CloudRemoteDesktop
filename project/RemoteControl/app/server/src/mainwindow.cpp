#include "mainwindow.h"
#include "SMsgHandler.h"

//! write log
static void Log(void* pUser, const std::string& strLog, int level)
{
    static_cast<void>(level);
    MainWindow* p = static_cast<MainWindow*>(pUser);
    p->GetLabel()->setText(QString::fromStdString(strLog));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDesktopWidget* deskWidget = qApp->desktop();
    QRect screenRect = deskWidget->screenGeometry();
    int screenWidth = screenRect.width();
    int screenHeight = screenRect.height();

    this->setGeometry(QRect(screenWidth / 3, screenHeight / 3, screenWidth / 5, screenHeight / 5));
    m_pLabelInfo = new QLabel(this);
    m_pLabelInfo->setText("server run...");

    m_pControler = std::make_shared<SControler>();
    m_pControler->SetLogCb(Log, this, 0);
}

MainWindow::~MainWindow()
{
    qDebug() << __func__;
}

QLabel* MainWindow::GetLabel()
{
    return m_pLabelInfo;
}


