#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QEventLoop>

#include <stdio.h>
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
#include <unistd.h>
#include "httputils.h"

#define MAX_BUFFER_SIZE 10000

class Proxy : public QObject
{
    Q_OBJECT
public:
    explicit Proxy(QObject *parent = nullptr);
    void doSetup(QThread &cThread);
    void stop();
    void close_sockets();

    //int fd_server, fd_client;


private:
    bool stopFlag;
    bool buttonFlag;
    string request = "";
    QString reply = "";
    //string reply = "";

    void waitButton();




    int initServerSocket(string);
    int sendData(string, int);


signals:
    void textReceived(QString );
    void requestReceived(QString);
    void requestSent();
    void replyReceived(QString);
    void replyRetrieved();
    //void stopSignal();

public slots:
    void doWork();
    void on_buttonPressed(QString, QString);
};

#endif // PROXY_H
