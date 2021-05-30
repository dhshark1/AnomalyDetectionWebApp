#include <iostream>
#include <map>
#include "Server.h"

int main() {
    int port = 34321;
    try {
        Server server(port);
        AnomalyDetectionHandler adh;
        server.start(adh);
    }catch(const char* s){
        cout<<s<<endl;
    }
    return 0;
}
