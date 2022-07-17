
#include "CLoginWnd.h"
#include <QDebug>

CLoginWnd::CLoginWnd(QDialog* parent) : QDialog(parent)
{
	Init();
}

CLoginWnd::~CLoginWnd()
{

}

void CLoginWnd::Init()
{
	InitCtrl();
	InitData();
}

void CLoginWnd::InitData()
{
	setWindowTitle("RemoteControl Viewer");
	m_pComBoxIp->addItem("172.16.169.26");
	m_pLabelIp->setText("Ip:");
	m_pLabelUser->setText("User:");
	m_pEditUser->setText("vnc");
	m_pLabelPassword->setText("Password:");
	m_pBtnConnect->setText("Connect");
}

void CLoginWnd::InitCtrl()
{
	//! ip
	m_pLabelIp = new QLabel();
	m_pLabelIp->setText("Ip:");
	m_pComBoxIp = new QComboBox();
	m_pComBoxIp->setEditable(true);
	m_pHBLayoutIp = new QHBoxLayout();
	m_pHBLayoutIp->addWidget(m_pLabelIp);
	m_pHBLayoutIp->addWidget(m_pComBoxIp);

	//! user
	m_pLabelUser = new QLabel();
	m_pLabelUser->setText("User:");
	m_pEditUser = new QLineEdit();
	m_pHBLayoutUser = new QHBoxLayout();
	m_pHBLayoutUser->addWidget(m_pLabelUser);
	m_pHBLayoutUser->addWidget(m_pEditUser);

	//! password
	m_pLabelPassword = new QLabel();
	m_pLabelPassword->setText("Password:");
	m_pEditPassword = new QLineEdit();
	m_pHBLayoutPassword = new QHBoxLayout();
	m_pHBLayoutPassword->addWidget(m_pLabelPassword);
	m_pHBLayoutPassword->addWidget(m_pEditPassword);

	//! connect
	m_pBtnConnect = new QPushButton();
	m_pBtnConnect->setText("Connect");
	m_pHBLayoutConnect = new QHBoxLayout();
	m_pHBLayoutConnect->addWidget(m_pBtnConnect);

	//! 
	m_pVBLayout = new QVBoxLayout(this);
	m_pVBLayout->addLayout(m_pHBLayoutIp);
	m_pVBLayout->addLayout(m_pHBLayoutUser);
	m_pVBLayout->addLayout(m_pHBLayoutPassword);
	m_pVBLayout->addLayout(m_pHBLayoutConnect);


}

void CLoginWnd::InitSignalSlot()
{
	QObject::connect(m_pBtnConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectSlot()));
	//QObject::connect(m_pBtnConnect, &QPushButton::clicked, this, &CLoginWnd::ConnectSlot);
	
}

void CLoginWnd::Layout()
{

}

bool CLoginWnd::PermissionVerification()
{

	return true;
}

void CLoginWnd::ConnectSlot()
{
	qDebug() << "Connecting...";
}