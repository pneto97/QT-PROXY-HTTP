#include "webtools.h"
#include <QCoreApplication>

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


void WebTools::waitButton(){

    while(buttonFlag == false){
        QThread::msleep(500);
        QCoreApplication::processEvents();
    }
    buttonFlag = false;
}


void WebTools::stop(){
    stopFlag = true;
}


void WebTools::runSpider(){

    waitButton();

    int sockfd, newsockfd;
    int clilen = sizeof(struct sockaddr);
    int opt = 1;
    // int porta = 8228;
    char buffer[MAX_BUFFER_SIZE];
    const string ok_msg = "HTTP/1.0 200 OK\r\n\r\n";
    string request = "";
    string reply = "";


    struct sockaddr_in serv_addr;
    struct sockaddr cli_addr;
    /*
    if(argc<2){
       fprintf(stderr,"Insira uma porta!\n");
       exit(1);
    }*/

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

    //int portno = atoi(argv[1]);
    int portno = 8228;
    serv_addr.sin_family = AF_INET;     // ip4 family
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
       fprintf(stderr,"Erro no binding");
       exit(1);
    }

    //client estabelecido

    string uri = "/";
    string host = "www.linuxhowtos.org";
    //string host = "www.ba.gov.br";
    int deep = 1;
    //server socket
    int serverSock = 0;

    //string response = sendGet(&serverSock, host , uri);
    //string response = sendGet(&serverSock, "linuxhowtos.org" , "/");
    string response = sendGet(&serverSock, host , "/");

    //cout << response << endl;

    vector<string> paths;

    findPaths(paths, response, host);
    int tst = 0;

    // for(vector<string>::iterator it = paths.begin() ; it != paths.end() ; it ++){
    //     cout << *it << endl;
    // }

    for(int i = 1 ; i < deep ; i++){

       vector<string> pathsCpy(paths);

       // for(vector<string>::iterator it = pathsCpy.begin() ; it != pathsCpy.end() ; it ++){
       //     cout << *it << endl;
       // }

       for(int j = 0 ; j < pathsCpy.size() ; j++){
           if(pathsCpy[j][0] == '/'){
               if( (pathsCpy[j].find(".") == std::string::npos) || (pathsCpy[j].find(".htm") != std::string::npos) || (pathsCpy[j].find(".php") != std::string::npos)){

                  // printf("entrou\n");
                   response = sendGet(&serverSock, host , pathsCpy[j]);
                   findPaths(paths, response, host);
               }
               //cout << tst++ << endl;
           }

           //cout << pathsCpy[j][0] << endl;
           // printf("%c\n", pathsCpy[i][0]);
       }
    }



    sort(paths.begin(), paths.end());
    cout << endl;

    for(vector<string>::iterator it = paths.begin() ; it != paths.end() ; it ++){
    //   *it = fixUrl(*it, host);
        //ui->plainTextEdit->setPlainText3("");
       string string_it = *it;
       QString GUIit = QString::fromStdString(string_it);
       emit nodeSpider(GUIit);
       //cout << *it << endl;
    }


    ::close(serverSock);
    ::close(sockfd);
    /*stopFlag = false;

    for (int i = 0; i < 100; i++) {

    qDebug() << "spider " << i;
    QThread::msleep(30);


    if(this->stopFlag == true) {
        stopFlag = false;
        break;
    }

    }
    this->thread()->quit();*/
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


void WebTools::on_buttonPressed(){

    this->buttonFlag = true;
}
