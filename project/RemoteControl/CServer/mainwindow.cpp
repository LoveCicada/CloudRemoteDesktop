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
    this->setGeometry(QRect(screen_width / 3, screen_height / 3, screen_width / 5, screen_height / 5));
    m_pLabelInfo = new QLabel(this);
    m_pLabelInfo->setText("server run...");
    //Interface::mouse(100, 100);
    //new Controler;
    m_pControler = std::make_shared<SControler>(new SControler);
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


