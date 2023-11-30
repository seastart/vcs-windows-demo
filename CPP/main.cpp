#include "widget.h"

#include <QApplication>
#include "formlogin.h"
#include <QDebug>


#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormLogin w;
    w.show();
    return a.exec();
}
