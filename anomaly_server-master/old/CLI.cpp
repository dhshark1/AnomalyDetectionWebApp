//
// Created by tom on 09/01/2021.
//

#include "CLI.h"

CLI::CLI(Command** c, size_t cSize){
    //maybe instead I should implement a deep copy???
    this->cmdsArr = c;
    this->cmdsSize = cSize;
}


void CLI::start(){
    cout<<"Welcome to the Anomaly Detection Server."<<endl;
    cout<<"Please choose an option:"<<endl;
    printComds();
}

void CLI::printComds() {
    int i=0;
    for(;i<this->cmdsSize;++i){
        cout<< i+1 << " " + (*(this->cmdsArr+i))->getDescription() <<endl;
    }
}