//
// Created by omer on 28/12/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H


#include "Command.h"

class StartCommand: public Command {

public:

    /**
    * @name : execute
    * @parametars : args - vector of args that we want to pass (first one usually a command)
    *              socket - socket to pass parameters to
    *              threadId - the id of the thread that we started
    * @brief : gets the argument from the command and execute them according to the command it gets in the string
    * @return : ignored
    **/
    virtual void execute(vector<string> args, int socket = 0, pthread_t* threadId = 0);

};

#endif //SERVER_STARTCOMMAND_H