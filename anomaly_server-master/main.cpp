#include <iostream>
//#include "MainTrain.h"
#include "MainTrain_ex6.h"
#include <map>

int main() {
    //mainTrain();
    //mainTrainEX6();
    int port = 34321;
    try {
        //AnomalyDetectionHandler adh;
        Server server(port);
        AnomalyDetectionHandler adh;
        server.start(adh);
    }catch(const char* s){
        cout<<s<<endl;
    }
        //mainsocket
    /*
    std::map<unsigned long int, TimeSeriesAnomalyDetector*> m;
    HybridAnomalyDetector* hb;
    SimpleAnomalyDetector* sAD = new SimpleAnomalyDetector();
    m.insert(std::pair<unsigned long int, TimeSeriesAnomalyDetector*>(0,hb));
    m.insert(std::pair<unsigned long int, TimeSeriesAnomalyDetector*>(1,sAD));*/
    //dic<modelid,<socketi,cli()>>
    //socket1 = new socket1
    //cli(new sock(socket1))
    return 0;
}
