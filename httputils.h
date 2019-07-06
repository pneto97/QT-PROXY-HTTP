#ifndef HTTP_UTILS

#define HTTP_UTILS


#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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
#include <QDir>
#define MAX_BUFFER_SIZE 10000



using namespace std;

//classe que faz o parse e armazena dados do request
class Request{
    public:
        string getUri();
        string getVersion(); 
        string getMethod();
        string getHost();
        string getRequest();

        void parse(string req);
   //     string getHeaderFields();
        Request(string req); //parse request
    private:
        string method;
        string uri;
        string version;
        string host;
        string req;
    //    string headerFields; 
};

//recebe o host, faz a resolucao DNS, cria socket, conecta com o servidor e retorna o socket
int initServerSocket(string);

//envia todos os dados da string para algum socket
int sendData(string, int);

//Envia todos os dados de um array de caracter para um socket (para binários)
int sendDataChar(char*, int, int);

//manda uma requisição GET com connection close e retorna a resposta
vector<char> sendGet(int* serverSock,string host, string uri);

//normaliza o formato da URL ou um path para sempre mostrar http://www...
// no html pode vir como //www.host.com, /path...
// usado no spider e dump
string fixUrl(string str, string host);

//pega um html de resposta, procura todos os href e src e insere no vector paths
int findPaths(std::vector<string>& paths, std::string response, string host);

//parse de URL
string extractHost(string); //pega o www.host.com sem o http e o path
string extractPath(string); //pega tudo que tem depois do host
string extractDirectory(string); //pega o diretório em que se encontra o arquivo
string extractFileName(string); //pega apenas o nome do arquivo

//usado para substituir os links do html para os diretórios locais
string fixLinks(string);

#endif
