//
// Created by omer on 28/12/17.
//

#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand: public Command {

public:

    virtual void execute(vector<string> args, int socket = 0, pthread_t*threadId = 0);
};



#endif //SERVER_CLOSECOMMAND_H
