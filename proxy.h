#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QString>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>

class Proxy : public QObject
{
    Q_OBJECT
public:
    explicit Proxy(QObject *parent = nullptr);
    void doSetup(QThread &cThread);
    void stop();
    void close_sockets();

    int fd_server, fd_client;


private:
    bool stopFlag;

signals:
    void textReceived(QString );

public slots:
    void doWork();
};

#endif // PROXY_H
