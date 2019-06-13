#include "webtools.h"

WebTools::WebTools(QObject *parent) : QObject(parent)
{
    stopFlag = false;
}

void WebTools::doSetup(QThread &cThread, Operation op){

    disconnect(&cThread, SIGNAL(started()),this, SLOT(runSpider()));
    disconnect(&cThread, SIGNAL(started()),this, SLOT(runDump()));

    switch(op){

        case Operation::SPIDER:
            connect(&cThread, SIGNAL(started()),this, SLOT(runSpider()));
            //qDebug("SPIDER");
            break;

        case Operation::DUMP :
            connect(&cThread, SIGNAL(started()),this, SLOT(runDump()));
            //qDebug("DUMP");
            break;
    }

}

void WebTools::stop(){
    stopFlag = true;
}

void WebTools::runSpider(){
    stopFlag = false;

    for (int i = 0; i < 100; i++) {

        qDebug() << "spider " << i;
        QThread::msleep(30);


        if(this->stopFlag == true) {
            stopFlag = false;
            break;
        }

    }
    this->thread()->quit();
}

void WebTools::runDump(){
    stopFlag = false;

    for (int i = 0; i < 100; i++) {

        qDebug() << "dump " << i;
        QThread::msleep(30);


        if(this->stopFlag == true) {
            stopFlag = false;
            break;
        }

    }
    this->thread()->quit();
}



