//
// Created by omer on 28/12/17.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <string>
#include <vector>

#endif //SERVER_COMMAND_H

using namespace std;

class Command {
public:
    virtual void execute(vector<string> args, int socket = 0, pthread_t*threadId = 0) = 0;
    virtual ~Command() {}
};