#include "mainwindow.h"
#include <QApplication>

//static QString myUser;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
