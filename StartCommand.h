//
// Created by omer on 28/12/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H


#include "Command.h"

class StartCommand: public Command {

public:

    virtual void execute(vector<string> args, int socket = 0, pthread_t* threadId = 0);

};

#endif //SERVER_STARTCOMMAND_H