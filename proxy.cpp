#include "proxy.h"
#include <QMutex>

Proxy::Proxy(QObject *parent) : QObject(parent)
{
    stopFlag = false;
}

void Proxy::doSetup(QThread &cThread){

    disconnect(&cThread, SIGNAL(started()),this, SLOT(doWork()));
    connect(&cThread, SIGNAL(started()),this, SLOT(doWork()));
}

void Proxy::stop(){
    stopFlag = true;
}

void Proxy::doWork(){
    for (int i = 0; i < 100; i++) {

        qDebug() << i;
        QThread::msleep(30);


        if(this->stopFlag == true) {
            stopFlag = false;
            break;
        }

    }
    this->thread()->quit();
}
