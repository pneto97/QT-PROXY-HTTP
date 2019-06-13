#include "proxy.h"
#include <QMutex>

Proxy::Proxy(QObject *parent) : QObject(parent)
{
}

void Proxy::doSetup(QThread &cThread){

    disconnect(&cThread, SIGNAL(started()),this, SLOT(doWork()));
    connect(&cThread, SIGNAL(started()),this, SLOT(doWork()));
}

void Proxy::doWork(){
    for (int i = 0; i < 100; i++) {

        qDebug() << i;
        QThread::msleep(500);

        if(this->stop == true) {
            stop = false;
            break;
        }

    }
    this->thread()->quit();
}
