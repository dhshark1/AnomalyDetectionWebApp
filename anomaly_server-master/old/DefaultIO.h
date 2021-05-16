//
// Created by tom on 09/01/2021.
//

#ifndef EVENDERECH3_EX5_DEFAULTIO_H
#define EVENDERECH3_EX5_DEFAULTIO_H

#include <string>
using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string s)=0;
};

#endif //EVENDERECH3_EX5_DEFAULTIO_H
