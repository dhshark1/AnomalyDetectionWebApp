//
// Created by tom on 09/01/2021.
//

#ifndef EVENDERECH3_EX5_CLI_H
#define EVENDERECH3_EX5_CLI_H

#include <string>
#include "commands.h"
class CLI {
    Command** cmdsArr;
    size_t cmdsSize;
public:
    //need to rethink about how the construction of this class should be implemented;
    CLI(Command** c, size_t cSize);
    CLI();
    void start();
private:
    void CLI::printComds();
};


#endif //EVENDERECH3_EX5_CLI_H
