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

    //waitButton();

    int sockfd, newsockfd;
    int clilen = sizeof(struct sockaddr);
    int opt = 1;
    // int porta = 8228;
    char buffer[MAX_BUFFER_SIZE];
    const string ok_msg = "HTTP/1.0 200 OK\r\n\r\n";
    string request = "";
    string reply = "";


    //server socket
    int serverSock = 0;

    string uri = "/";
    string host = "www.linuxhowtos.org";
    //string host = "www.ba.gov.br";
    int depth = 2;


    //string response = sendGet(&serverSock, host , uri);
    //string response = sendGet(&serverSock, "linuxhowtos.org" , "/");
    string response = sendGet(&serverSock, host , "/");

    //cout << response << endl;

    vector<string> paths;

    findPaths(paths, response, host);

    for(int i = 1 ; i < depth ; i++){

       vector<string> pathsCpy(paths);

       for(int j = 0; j < pathsCpy.size(); j++){
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

    this->thread()->quit();

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
