#include "littlegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LittleGui w;
    w.show();

    return a.exec();
}
