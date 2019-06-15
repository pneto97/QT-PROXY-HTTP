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

/*
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
*/

void Proxy::close_sockets(){
    close(fd_client);
    close(fd_server);
}

void Proxy::doWork(){
    stopFlag = false;


    QString testReq = "";

    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);
    //int fd_server, fd_client;
    char buf[2048];
    int on =1;

    fd_server = socket(AF_INET, SOCK_STREAM, 0);

    if(fd_server < 0){
        perror("socket");
        exit(1);
    }


    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8228);

    if(bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        perror("bind");
        close(fd_server);
        exit(1);
    }


    if(listen(fd_server, 10) == -1){
        perror("listen");
        close(fd_server);
        exit(1);
    }

    fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);

    if(fd_client == -1){
        perror("Connection failed");
    }

   // printf("Got client connection \n");

 //   if(!fork()){

//    close(fd_server);
    memset(buf,0,2048);
    read(fd_client, buf, 2047);
    testReq.append(buf);
    emit textReceived(testReq);

//    printf("%s\n",buf);

   // close (fd_client);
        //exit(0);
   // }
    close(fd_client);

    while(1){
        qDebug() << "TESTE";
        QThread::msleep(30);
        if(this->stopFlag == true) {
            stopFlag = false;
            break;
        }
    }
    this->thread()->quit();
}
