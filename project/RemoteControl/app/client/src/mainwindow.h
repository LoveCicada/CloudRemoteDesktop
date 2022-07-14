#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QTcpSocket>
#include <QHostAddress>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "CMsgReader.h"
#include "CMsgWriter.h"
#include "CControlWnd.h"
#include "ClientData.h"
#include "ClientParams.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    CControlWnd*    m_pCControlWnd;

private:

    //! ui
    QLabel*         m_pIpLabel;
    QLabel*         m_pWidthLabel;
    QLabel*         m_pHeightLabel;
    QLineEdit*      m_pIpEdit;
    QLineEdit*      m_pWidthEdit;
    QLineEdit*      m_pHeightEdit;
    
    //ui data
    ClientData      m_clientData;

    //! client params
    ClientParams    m_clientParams;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Init();
    void InitData();
    void InitCtrl();
    void InitWndSize();

    void GetClientMachineInfo();
    void GetClientUIData(ClientData& clientData);

signals:
    void keyPressed(QKeyEvent *);
    void keyReleased(QKeyEvent *);

public slots:
    void tryconnect();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

};

#endif // MAINWINDOW_H
