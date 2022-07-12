#pragma once

#include <QMainWindow>
#include <memory>
#include "SControler.h"
#include <QLabel>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLabel* GetLabel();

private:
    std::shared_ptr<SControler> m_pControler;
    
private:
    //! UI
    QLabel* m_pLabelInfo;
};

