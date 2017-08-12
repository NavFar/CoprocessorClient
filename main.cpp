#include "mainwindow.h"
#include "portselect.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PortSelect p;
    MainWindow w;
    p.show();
   if(p.exec()==QDialog::Accepted){

        w.connectToPort(p.getSelectedPort());
        w.show();
   }

    return a.exec();
}
