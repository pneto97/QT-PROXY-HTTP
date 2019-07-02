#include "httputils.h"

Request::Request(string req){
    this->parse(req);
}
void Request::parse(string req){
    this->req = req;

    stringstream s(req);
    string word;

    s >> word;
    this->method = word;
    s >> word;
    this->uri = word;
    s >> word;
    this->version = word;

    this->host = "";
    while( s >> word){
        if(word == "Host:"){
            s >> word;
            this->host = word;
            break;
        }
    }
}

string Request::getUri(){
    return this->uri;
}
string Request::getVersion(){
    return this->version;
}
string Request::getMethod(){
    return this->method;
}
string Request::getHost(){
    return this->host;
}
string Request::getRequest(){
    return this->req;
}


int initServerSocket(string host){

    int serverFd;
    struct addrinfo hints, *res;
    int https = 0;

    const char* port = "80";


    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), port, &hints, &res) != 0) {
    //if (getaddrinfo("linuxhowtos.org", porta, &hints, &res) != 0) {
        fprintf (stderr," Erro no formato do endereco do servidor! \n");
        exit (1);
    }

    if ((serverFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        fprintf (stderr," Erro ao criar socket para o servidor! \n");
        exit (1);
    }

    if (connect(serverFd, res->ai_addr, res->ai_addrlen) < 0) {
        fprintf (stderr," Erro ao conectar com o servidor ! \n");
        exit (1);
    }

    freeaddrinfo(res);
//    free(addr);

    return serverFd;
}


int sendData(string data, int sock){

    int sendSize = data.size();
    int sentTotal = 0;
    //char sendBuf[MAX_BUFFER_SIZE];
    char* sendBuf = (char*) malloc((sendSize+1)*sizeof(char));
    memset(sendBuf, 0, sizeof(sendBuf));
    strcpy(sendBuf, data.c_str());

    //string a(sendBuf);
    //cout << a << endl;
    while(sentTotal < sendSize){
      int sent = 0;
      if((sent = send(sock, (void*) (sendBuf + sentTotal), sendSize - sentTotal,0)) <0){

          fprintf(stderr,"Erro ao enviar ao servidor!\n");
          exit(1);
      }

      sentTotal = sentTotal + sent;
    }
    free(sendBuf);
    return sentTotal;
}


int sendDataChar(char* data, int size, int sock){

        int sentTotal = 0;
        //char sendBuf[MAX_BUFFER_SIZE];
        char* sendBuf = (char*) malloc((size+1)*sizeof(char));
        memset(sendBuf, 0 , sizeof(sendBuf));
        memcpy(sendBuf,data,size);
        //strcpy(sendBuf,data.c_str());

        //string a(sendBuf);
        //cout << a << endl;
        while(sentTotal < size){
            int sent = 0;
            if((sent = send(sock, (void*) (sendBuf + sentTotal), size - sentTotal,0)) <0){

                fprintf(stderr,"Erro ao enviar ao servidor!\n");
                exit(1);
            }

            sentTotal = sentTotal + sent;
        }
        free(sendBuf);
        return sentTotal;
}


/*string sendGet(int* serverSock,string host, string uri){

    string request = "GET " + uri + " HTTP/1.1\r\n" + "Host: "+host + "\r\n" + "Connection: close" + "\r\n\r\n";
    cout << "request: \n" << request << endl;
    string response = "";

    *serverSock = initServerSocket(host);


    sendData(request, *serverSock);

    int recvTotal = 0;
    int received = 0;
    char recvBuf[MAX_BUFFER_SIZE];
    memset(recvBuf, 0 , sizeof(recvBuf));


    while((received = recv(*serverSock, recvBuf, MAX_BUFFER_SIZE, 0)) > 0){
        recvBuf[received] = '\0';
        response.append(recvBuf);
        memset(recvBuf, 0 , sizeof(recvBuf));
    }

    if(received < 0){
        fprintf (stderr,"Erro ao receber do servidor. \n");
        exit (1);
    }


    return response;
}*/


vector<char> sendGet(int* serverSock,string host, string uri){

    unsigned int buffer_size = 102400;
    unsigned int recvTotal = 0;
    vector<char> resp;

    char* response = (char*) malloc(buffer_size * sizeof(char));
    response[0] = '\0';

    string request = "";

    request = "GET " + uri + " HTTP/1.1\r\n" + "Host: "+host + "\r\n" + "Connection: close" + "\r\n\r\n";

    cout << "request: \n" << request << endl;
    //string response = "";

    try{
        *serverSock = initServerSocket(host);
    } catch(exception e){
        throw "ERROOOO";
        exit(1);
    }


    sendData(request, *serverSock);

    int received = 0;
    char recvBuf[MAX_BUFFER_SIZE];
    memset(recvBuf, 0 , sizeof(recvBuf));

    // int i = 0;
    while((received = recv(*serverSock, recvBuf, MAX_BUFFER_SIZE, 0)) > 0){

        recvBuf[received] = '\0';
        resp.insert(resp.end(), recvBuf, recvBuf + received);
    }

    if(received < 0){
        fprintf (stderr,"Erro ao receber do servidor. \n");
        exit (1);
    }

    return resp;
    //return response;
}


string fixUrl(string str, string host){

    string retString = "";
    //esta correto se começar com http://
    if(str.find("http://") != std::string::npos){
        retString = str;
    }
    else if(str.find("https://") != std::string::npos) {
        retString = str;

    } else if(str.find("//") != std::string::npos){ //se a url começar com //, tratar como http
        retString = ("http:" + str);

    } else { // é só um path
        retString = "http://" + host + str;
        //retString = str;
    }
    return retString;

}


int findPaths(std::vector<string>& paths, std::string response, string host){

    //cout << "find path" << endl;
    int qtd = 0;
    int positionHref = 0;
    int positionQ1 = 0;
    int positionQ2 = 0;
    string currentLink = "";

    int qtdHref = 0;

    while((positionHref = response.find("href=\"", positionHref+1) ) != string::npos){

        qtd++;
        //positionHref = response.find("href", positionHref+1);
        positionQ1 = response.find("\"",positionHref+1) + 1;
        positionQ2 = response.find("\"",positionQ1 + 1);

        currentLink = response.substr(positionQ1, positionQ2 - positionQ1);
        //currentLink.push_back('\0');
        // cout << positionQ1 << " " << positionQ2 << " " ;
        // cout << currentLink << endl;
        currentLink = fixUrl(currentLink, host);
        // printf("%s\n",currentLink.c_str());

        if(std::find(paths.begin(), paths.end(), currentLink) == paths.end()){
            paths.push_back(currentLink);
        }
    }

    //cout << "qtd href = "  << qtd << endl;

    // cout << "foi href" << endl;

    positionHref = 0;
    qtd = 0;

    while((positionHref = response.find("src=\"", positionHref+1) ) != string::npos){

        qtd++;
        //positionHref = response.find("href", positionHref+1);
        positionQ1 = response.find("\"",positionHref+1) + 1;
        positionQ2 = response.find("\"",positionQ1 + 1);

        currentLink = response.substr(positionQ1, positionQ2 - positionQ1);

        currentLink = fixUrl(currentLink, host);
        if(std::find(paths.begin(), paths.end(), currentLink) == paths.end()){

            paths.push_back(currentLink);
        }

        //cout << currentLink << endl;
     }

    // cout << "foi src" << endl;



    return qtd;
}


string extractHost(string url){

    int pos1 = url.find("//") + 2;
    int pos2 = url.find("/",pos1+2);

    if (pos2 == string ::npos){
        pos2 = url.size();

        if(url.find("#") != string::npos){
            pos2 = url.find("#");
        }

        if(url.find("?") != string::npos){
            pos2 = url.find("?");
        }
    }



    string host(url.begin()+pos1, url.begin()+pos2);


    return host;
}


string extractPath(string url){
    int pos1 = url.find("//") + 2;
    int pos2 = url.find("/",pos1+2);

    if(pos2 == string::npos){
        return "/";
    }

    string path(url.begin()+pos2, url.end());


    return path;
}


string extractDirectory(string url){

    int pos1 = url.find("//") + 2;
    int pos2 = url.find("/",pos1+2);
    if(pos2 == string::npos){
        return "/";
    }
    int posF = url.find_last_of("/");

    string dir(url.begin()+pos2, url.begin() + posF);
    // if(dir == ""){
    //     dir = "/";
    // }
    return dir;
}


string extractFileName(string url){

    // if(extractPath(url) == "/"){
    //     return "index.html";
    // }
    if(url.back() == '/'){
        return "index.html";
    }

    int posStart = url.find_last_of("/")+1;

    string lastPath(url.begin() + posStart , url.end());

    //extrai caso tenha ?
   // int posFinal = max(lastPath.find("?"));

    return lastPath;
}