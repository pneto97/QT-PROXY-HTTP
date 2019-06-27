#ifndef WEBTOOLS_H
#define WEBTOOLS_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>*/
#include "httputils.h"

enum class Operation{
    SPIDER = 0,
    DUMP = 1
};


class WebTools : public QObject
{
    Q_OBJECT
public:
    explicit WebTools(QObject *parent = nullptr);
    void doSetup(QThread &cThread, Operation op);
    void stop();

private:
    bool stopFlag;
    bool buttonFlag;

    //int depth;
    //string url;

    void waitButton();


signals:

    void nodeSpider(QString);

public slots:
    void runSpider();
    void runDump();
    void on_buttonPressed();
};

#endif // WEBTOOLS_H
