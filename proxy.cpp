#include "proxy.h"
#include <QMutex>
#include <QCoreApplication>

Proxy::Proxy(QObject *parent) : QObject(parent){

    stopFlag = false;
    buttonFlag = false;
}


void Proxy::doSetup(QThread &cThread){

    disconnect(&cThread, SIGNAL(started()),this, SLOT(doWork()));
    connect(&cThread, SIGNAL(started()),this, SLOT(doWork()));
}


void Proxy::stop(){
    stopFlag = true;
}


void Proxy::waitButton(){

    /*
    QEventLoop loop;
    connect(this,  SIGNAL(stopSignal()), &loop, SLOT(quit()) );
    loop.exec();
    disconnect(this,  SIGNAL(stopSignal()), &loop, SLOT(quit()) );*/

    while(buttonFlag == false){
        QThread::msleep(500);
        QCoreApplication::processEvents();
    }
    buttonFlag = false;
}


int Proxy::initServerSocket(string host){

    int serverFd;
        struct addrinfo hints, *res;
    //    int https = 0;

        const char* port = "80";

        memset(&hints,0,sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(host.c_str(), port, &hints, &res) != 0) {
            fprintf (stderr," Erro no formato do endereco do servidor! \n");
            exit (1);
        }

        if ((serverFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
            fprintf (stderr," Erro ao criar socket para o servidor! \n");
            exit (1);
        }

        if (::connect(serverFd, res->ai_addr, res->ai_addrlen) < 0) {
            fprintf (stderr," Erro ao conectar com o servidor ! \n");
            exit (1);
        }

        freeaddrinfo(res);

        return serverFd;
}


void Proxy::doWork(){

    stopFlag = false;

    const char* port = "8228";
    int sockfd, clisockfd;
    int clilen = sizeof(struct sockaddr);
    int opt = 1;
    char buffer[MAX_BUFFER_SIZE];

//    const string ok_msg = "HTTP/1.0 200 OK\r\n\r\n";

    struct sockaddr_in serv_addr;
    struct sockaddr cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //cria o socket

    if(sockfd < 0){

        fprintf(stderr,"Socket não foi criado\n");
        exit(1);
    }

    // Set the socket options
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &opt, sizeof(opt))) {

        fprintf(stderr,"Erro na configuracao do socket\n");
        exit(1);
    }

    memset(&serv_addr , 0 , sizeof(serv_addr));

    int portno = atoi(port);
    serv_addr.sin_family = AF_INET;     // ip4 family
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,"Erro no binding");
        exit(1);
    }

    if(listen(sockfd, 100) < 0){

        fprintf(stderr,"Erro no listen\n");
        exit(1);
    }

    while(1){

        int received_bits = 0;
        int recvd = 0;
        request = "";
        reply = "";

        //proxy passa a aceitar mensagens do browser
        clisockfd = accept(sockfd, &cli_addr, (socklen_t*) &clilen);
        if(clisockfd < 0){
            fprintf(stderr,"Erro ao aceitar o request\n");
        }

        //recebe o request do browser e monta a string "request"
        while(request.find("\r\n\r\n") == std::string::npos){

            memset(buffer, 0 , sizeof(buffer));

            recvd = recv(clisockfd, buffer , MAX_BUFFER_SIZE, 0);

            if(recvd < 0){
                fprintf(stderr,"Erro ao receber");
                exit(1);
            } else if( recvd == 0){
                break;
            } else{
                received_bits += recvd;

                buffer[recvd] = '\0';
            }

            request.append(buffer);
        }

        //cria o parse do request
        Request myReq(request);

        //cria string do request que será mostrada na GUI
        QString GUIRequest = QString::fromStdString(myReq.getRequest());


        //se for https, ignora
        if(myReq.getMethod() == "CONNECT"){
            continue;
        }

        //Informa para a gui que o request foi recebido e o manda
        emit requestReceived(GUIRequest);

        //trava de execucao do thread ate apertar o botao
        waitButton();
        //A partir daqui o request será enviado do proxy ao servidor final

        //algo pode ter sido editado na GUI, o botão atualiza request e reply
        myReq.parse(this->request);

       // GUIRequest = QString::fromStdString(request);
        //qDebug() << GUIRequest;

        int serverFd = initServerSocket(myReq.getHost());
        sendData(myReq.getRequest(), serverFd);

        emit requestSent();

        int recvTotal = 0;
        int received = 0;
        char recvBuf[MAX_BUFFER_SIZE];
        memset(recvBuf, 0 , sizeof(recvBuf));


        while((received = recv(serverFd, recvBuf, MAX_BUFFER_SIZE, 0)) > 0){

            recvBuf[received] = '\0';
            reply.append(recvBuf);
            memset(recvBuf, 0 , sizeof(recvBuf));
        }

        if(received < 0){
            fprintf (stderr,"Erro ao receber do servidor. \n");
            exit (1);
        }

        //proxy recebeu o response
        emit replyReceived(reply);

        waitButton();

        //a partir daí o response volta pro client

        //parse pro response?
        //sendData(reply.replace("\n","\r\n");toStdString(),clisockfd);
        sendData(reply.toStdString(),clisockfd);

        emit replyRetrieved();
        qDebug() << reply.toStdString().c_str();

        close(clisockfd);
        close(serverFd);
    }

    ::close(sockfd);

    //waitButton();
    //qDebug() << "ASHDAUISDHUISA";


    this->thread()->quit();
}


void Proxy::on_buttonPressed(QString request, QString reply){

    this->buttonFlag = true;
    this->request = request.replace("\n","\r\n").toStdString();
    this->reply = reply;

}


/*void Proxy::doWork(){
    stopFlag = false;
    QString testReq = "TESTE REQUISICAO";

    this->thread()->quit();
}*/


/*void Proxy::close_sockets(){
    close(fd_client);
    close(fd_server);
}*/

