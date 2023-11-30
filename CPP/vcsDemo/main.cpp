#include "widget.h"

#include <QApplication>
#include "formlogin.h"
#include <QDebug>


#include <iostream>



int main(int argc, char *argv[])
{
    std::string dev ="Microphone (High Definition Audio Device) #1";

    std::string dev_true = "";
    int dev_index = 0;

    int ret = dev.find(" #");
    if(ret > 0){
        dev_true = dev.substr(0,ret);
        dev_index = atoi(dev.substr(ret+2,1).c_str());
    }else{
        dev_true = dev;
        dev_index = 0;
    }

    qDebug()<<__func__<<ret<<dev_true.c_str()<<dev_index;
return 0;
    QApplication a(argc, argv);
    FormLogin w;
    w.show();
    return a.exec();
}
