//Developed by Nicolai Vladimirski BSUIR group 821703 24.10.21
#include <QApplication>
#include "src/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}