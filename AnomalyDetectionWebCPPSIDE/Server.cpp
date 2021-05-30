#include <string>
#include <map>
#include "Server.h"
using namespace std;




Server::Server(int port)throw (const char*){
    this->Stop = 0;
    this->fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw "socket failed";

    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(port);

    if (::bind(this->fd, (struct sockaddr *) &this->server, sizeof(this->server)) < 0) {
        throw "bind failure";
    }


    if(listen(fd, 5)<0)
        throw "listen failure";


}


void Server::start(ClientHandler& ch)throw(const char*){
     t = new thread([this, &ch]() {
            while(!this->Stop) {
                socklen_t cSize = sizeof(client);
                int clientFD = ::accept(this->fd, (struct sockaddr *) &client, &cSize);
                cout<<"client accepted"<<endl;

                if(clientFD <0){
                    cout<< "accept failed"<<endl;
                }
                //open new thread for handling specific client
                new thread([&clientFD, &ch]() {
                    bool simpleMode = false;
                    SocketIO s(clientFD);
                    string msg = s.read();
                    if (msg.compare("Simple Anomaly Detection")==0){
                        simpleMode=true;
                    }
                    else if(msg.compare("Hybrid Anomaly Detection")==0){
                        simpleMode=false;
                    }
                    else{
                        s.write("E404");
                        close(clientFD);
                        return;
                    }
                    ch.handle(clientFD, simpleMode);
                    close(clientFD);
                });


            }
            ::close(this->fd);
        });
    t->join();

}


void Server::stop(){
    this->Stop=1;
    t->join();
}

Server::~Server() {
}


