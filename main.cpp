#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // change window icon
    w.setWindowIcon(QIcon(":/images/WindowImage.png"));

    w.show();
    return a.exec();
}
