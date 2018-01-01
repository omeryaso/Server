//
// Created by omer on 28/12/17.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#endif //SERVER_COMMAND_H


#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
};