#include <string>
#include <map>
#include "Server.h"
using namespace std;

//std::map<unsigned long int, CLI*> id_2_CLI_map;

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

/*
std::vector<correlatedFeatures> JsonStringToCfVec(string jsonString) {
    std::vector<correlatedFeatures> cf;
    json j = json::parse(jsonString);
    for(auto it : j["cfVec"]){
        correlatedFeatures c;
        c.feature1 = it["feature1"];
        c.feature2 = it["feature2"];
        c.corrlation = it["corrlation"];
        c.threshold = it["threshold"];
        if (it["Simple"]==1){
            c.lin_reg= Line(it["lin_reg"]["a"],it["lin_reg"]["b"]);
            c.center=nullptr;
        }
        else {
            c.lin_reg;
            c.center= new Point(it["center"]["x"], it["center"]["y"]);
        }
        cf.push_back(c);
    }
    return cf;
}
 */

/*
string cfVecToJsonString(std::vector<correlatedFeatures>& cf) {
    json j;
    std::vector<correlatedFeatures>::iterator it;
    std::vector<correlatedFeatures>::iterator endIT = cf.end();
    int i =1;
    for(it = cf.begin(); it!=endIT; ++it, ++i) {
        string temp = "cf"+ to_string(i);
        j["cfVec"][temp]["feature1"] = (*it).feature1;
        j["cfVec"][temp]["feature2"] = (*it).feature2;
        j["cfVec"][temp]["corrlation"] = (*it).corrlation;
        j["cfVec"][temp]["threshold"] = (*it).threshold;
        if ((*it).center == nullptr) {
            //correlated feature by line regression
            j["cfVec"][temp]["lin_reg"]["a"] = (*it).lin_reg.a;
            j["cfVec"][temp]["lin_reg"]["b"] = (*it).lin_reg.b;
            j["cfVec"][temp]["Simple"] = 1;
        }
        else {
            j["cfVec"][temp]["center"]["x"] = (*it).center->x;
            j["cfVec"][temp]["center"]["y"] = (*it).center->y;
            j["cfVec"][temp]["Simple"] = 0;
        }

    }
    //DEBUG
    cout<<j.dump()<<endl;
    //DEBUG
    return j.dump();
}
 */

/*
void readIDandCreadCLI(int clientID){
    SocketIO* s = new SocketIO(clientID);
    string msg = s->read();

     * NodeJS <-> cpp protocol:
     *  the nodeJS can send strings like "learn\nregression\n" thats tell cpp server to craete new cli
     *      and that the node want its anomaly detector to learn with csv that will be sent through the cli socket protocol.
     *
     *  the nodeJS can send strings like "

    if (msg.compare("learn")==0) {
        string detectorKind = s->read();
        bool simpleMode=false;
        if (detectorKind.compare("regression")==0){
            simpleMode=true;
        }
        CLI cli(s,simpleMode);
        cli.start();
        s->write(cfVecToJsonString(cli.hAD->cf));
        close(clientID);
    }
    else if (msg.compare("detect")==0) {
        CLI cli(s);
        string jsonString = s->read();
        cli.hAD->cf = JsonStringToCfVec(jsonString);
        cli.start();
        close(clientID);
    }



}
*/
//tom 2.5 2331
void Server::start(ClientHandler& ch)throw(const char*){
     t = new thread([this, &ch]() {
            while(!this->Stop) {
                socklen_t cSize = sizeof(client);
                int clientFD = ::accept(this->fd, (struct sockaddr *) &client, &cSize);
                cout<<"client accepted"<<endl;

                if(clientFD <0){
                    //throw "accept failed";
                    cout<< "accept failed"<<endl;
                }
                //open new thread for handling specific client
                new thread([&clientFD, &ch]() {
                    bool simpleMode = false;
                    SocketIO s(clientFD);
                    string msg = s.read();
                    //"Simple Anomaly Detection"
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
                    //"Hybrid Anomaly Detection"
                    //readIDandCreadCLI(clientFD);
                    ch.handle(clientFD, simpleMode);
                    close(clientFD);
                });
                //then the main thread proceed to accept new clients


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


//tom
