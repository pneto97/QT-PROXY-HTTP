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
