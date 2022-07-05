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

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    CControlWnd* m_pCControlWnd;
    QLineEdit* edAddr;
    QLineEdit* edWidth;
    QLineEdit* edHeight;
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
