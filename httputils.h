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
#include "httputils.h"
#define MAX_BUFFER_SIZE 10000



using namespace std;

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

int sendData(string, int);
string sendGet(int* serverSock,string host, string uri);
string fixUrl(string str, string host);
findPaths(std::vector<string>& paths, std::string response, string host);

#endif
