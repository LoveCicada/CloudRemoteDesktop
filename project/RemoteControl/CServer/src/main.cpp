#include <QApplication>
#include "SMsgHandler.h"
#include "SControler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
#if 0   

    MainWindow w;
    w.show();
    
#else 

    std::shared_ptr<SControler> m_pControler;
    m_pControler = std::make_shared<SControler>();

#endif // 0

    return a.exec();
}
