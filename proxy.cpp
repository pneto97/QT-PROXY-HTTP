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

/*void Proxy::doWork(){
    stopFlag = false;
    QString testReq = "TESTE REQUISICAO";

    this->thread()->quit();
}*/

void Proxy::doWork(){
    stopFlag = false;
    QString testReq = "TESTE REQUISICAO";

    for (int i = 0; i < 100; i++) {

        //qDebug() << "proxy " << i;
        testReq = "proxy ";
        testReq.append( QString::number(i));
        emit textReceived(testReq);


        qDebug() << testReq;

        QThread::msleep(30);


        if(this->stopFlag == true) {
            stopFlag = false;
            break;
        }

    }
    this->thread()->quit();
}
