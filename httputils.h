#include <string>
#include <iostream>
#include <sstream>

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
