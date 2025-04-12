#include <QApplication>
#include "mainwindow.h"

#include <iostream>

int main(int argc, char *argv[])
{
    qDebug() << "Bouncing Balls";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
