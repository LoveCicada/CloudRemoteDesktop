
#pragma once

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class CLoginWnd : public QDialog
{
	Q_OBJECT

public:
	explicit CLoginWnd(QDialog* parent = nullptr);
	~CLoginWnd();

	void Init();
	void InitData();
	void InitCtrl();
	void InitSignalSlot();
	void Layout();
protected:
	bool PermissionVerification();

signals:


public slots:
	void ConnectSlot();

private:
	//! ui
	//! grid layout, ip
	QHBoxLayout* m_pHBLayoutIp;
	QLabel* m_pLabelIp;
	QComboBox* m_pComBoxIp;

	//! grid layout, user
	QHBoxLayout* m_pHBLayoutUser;
	QLabel* m_pLabelUser;
	QLineEdit* m_pEditUser;

	//! grid layout, password
	QHBoxLayout* m_pHBLayoutPassword;
	QLabel* m_pLabelPassword;
	QLineEdit* m_pEditPassword;

	//! grid layout, connect
	QHBoxLayout* m_pHBLayoutConnect;
	QPushButton* m_pBtnConnect;

	//! vertical layout
	QVBoxLayout* m_pVBLayout;
	

};