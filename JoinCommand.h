//
// Created by omer on 28/12/17.
//

#ifndef SERVER_JOINCOMMAND_H
#define SERVER_JOINCOMMAND_H


#include "Command.h"

class JoinCommand: public Command {

public:

    virtual void execute(vector<string> args, int socket = 0, pthread_t*threadId = 0);

private:
    bool gameOver = false;
    void handleClients(int firstSocket, int secondSocket);
};


#endif //SERVER_JOINCOMMAND_H
