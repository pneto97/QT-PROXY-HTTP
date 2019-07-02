#include "webtools.h"
#include <QCoreApplication>

WebTools::WebTools(QObject *parent) : QObject(parent)
{
    stopFlag = false;
    buttonFlag = false;
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


void WebTools::spider(vector<string>& paths, string url, int depth){
    //qDebug("entrou spider");
     //server socket
    int serverSock = 0;

    // string response = sendGet(&serverSock, extractHost(url) , extractPath(url));
    vector<char> response_bytes;

    try{
        response_bytes = sendGet(&serverSock, extractHost(url) , extractPath(url));

    } catch(const char* e){
        throw e;
        exit(1);
    }

    string response(response_bytes.begin() , response_bytes.end());
    //cout << response;

    findPaths(paths, response, extractHost(url));

    // for(int i = 0 ; i < paths.size() ; i++){
    //     cout << paths[i] << endl;
    // }

    for(int i = 1 ; i < depth ; i++){

        vector<string> pathsCpy(paths);

        for(int j = 0 ; j < pathsCpy.size() ; j++){
         //   if(pathsCpy[j][0] == '/'){ //apenas os locais

            string host = extractHost(pathsCpy[j]);
            string uri = extractPath(pathsCpy[j]);

            cout << host << " " << uri << endl;

            if( (uri.find(".") == std::string::npos) || (uri.find(".htm") != std::string::npos) || (uri.find(".php") != std::string::npos)){

                //response = sendGet(&serverSock, host , uri);

                try{
                    response_bytes = sendGet(&serverSock, host , uri);
                } catch(const char* erro){
                    cout << "Resolução DNS falhou" << endl;
                    continue;
                }
                string response(response_bytes.begin() , response_bytes.end());
                findPaths(paths, response, host);

            }

        }
    }

    sort(paths.begin(), paths.end());

    close(serverSock);
}


void WebTools::runSpider(){
    //string url = this->getUrl();
    //int depth = this->getDepth();
    waitButton();

    qDebug() << QString::fromStdString(this->url);
    qDebug() << this->depth;

  //  this->url = "http://www.linuxhowtos.org/";
    //string url = "http://www.ba.gov.br/";
  //  this->depth = 1;


    vector<string> paths;

    spider(paths, url, depth);

    for(vector<string>::iterator it = paths.begin(); it != paths.end(); it ++){
       string string_it = *it;
       QString GUIit = QString::fromStdString(string_it);
       emit nodeSpider(GUIit);
       //cout << *it << endl;
    }

    this->thread()->quit();
}


void WebTools::dumpURL(string url){

    string create_dir = "mkdir -p ./" + extractHost(url) + extractDirectory(url);

    system(create_dir.c_str());

    try{
         downloadPage(url, "./"+ extractHost(url) + extractDirectory(url) + "/" + extractFileName(url));
    } catch(const char* e){
        throw "Não foi possível baixar a página";
    }
}


bool WebTools::downloadPage(string url, string fileName){

     //server socket
    int serverSock = 0;
    vector<char> response;
    //vector<char> response = sendGet(&serverSock, "" , url);
    try{
        response = sendGet(&serverSock, extractHost(url) , extractPath(url) );
    } catch(const char* e){
        throw "Não foi possível baixar a página";
        return false;
    }

    // cout << "get ok" << endl;

    if(serverSock == -1) return false;

    //para achar onde começa os dados
    std::string str_response( response.begin(), response.end() );
    //cout << str_response << endl;


    int data_start = str_response.find("\r\n\r\n") + 4;



    int data_end = 0;
    vector<char>::iterator data_end_it = response.end();


    if(str_response.find("<html") != string::npos){ //se for html, corrige os hrefs e srcs
        data_start = str_response.find("<",data_start);
        data_end = str_response.find("</html>",data_start);
        data_end_it = response.begin() + data_end + 7;




        string response_data_str(response.begin() + data_start, data_end_it);


        response_data_str = fixLinks(response_data_str);

        unsigned int respDataSize = response_data_str.size();
        const char* respDataCstr = response_data_str.data();
        if(fileName.find(".htm") == string::npos){
            fileName += ".html";
        }
        cout << respDataSize << endl;
        cout << fileName.c_str() << endl;

        FILE * fp = fopen(fileName.c_str(),"w+");

        for (unsigned int i = 0; i < respDataSize; i++){
            fwrite(&respDataCstr[i], 1, sizeof(char), fp);
        }

        fclose(fp);

        close(serverSock);

    } else{ //se for binário, apenas escreve


        // vector<char> response_data(response.begin() + data_start, response.end());
        vector<char> response_data(response.begin() + data_start, response.end());

        //vector<char> respData;
        unsigned int respDataSize = response_data.size();
        char* respDataCstr = response_data.data();

        FILE * fp = fopen(fileName.c_str(),"wb");

        for (unsigned int i = 0; i < respDataSize; ++i){
            //Some calculations to fill a[]
            fwrite(&respDataCstr[i], 1, sizeof(char), fp);
        }
        fclose(fp);

        close(serverSock);
    }

    return true;
}


void WebTools::runDump(){

   // string url = "http://www.linuxhowtos.org/";
    //string url = "http://www.ba.gov.br/";
    //int depth = 1;
    waitButton();


    vector <string> paths;

    spider(paths, url, depth);

    for(int i = 0 ; i < paths.size() ; i++ ){

            if(paths[i].find("https") == string::npos){
                try{
                    dumpURL(paths[i]);
                } catch(const char* e){
                    continue;
                }
            }

    }

    this->thread()->quit();
}


void WebTools::on_buttonPressed(QString url, QString depth){
    qDebug("entrou set url/depth");

    this->url = url.toStdString();
    this->depth = depth.toInt();

    this->buttonFlag = true;
}
