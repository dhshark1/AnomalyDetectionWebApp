//
// Created by tom on 09/01/2021.
//

#ifndef EVENDERECH3_EX5_COMMAND_H
#define EVENDERECH3_EX5_COMMAND_H
#include <string>
#include "DefaultIO.h"
using namespace std;
class Command {
    std::string description;
    DefaultIO dio;
public:
    Command(string cmdName, DefaultIO d){
        this->description = cmdName;
        this->dio = d;
    }
    virtual void execute()=0;
    string getDescription() {
        return this->description;
    }
};
#endif //EVENDERECH3_EX5_COMMAND_H
