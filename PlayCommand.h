//
// Created by omer on 02/01/18.
//

#ifndef SERVER_PLAYCOMMAND_H
#define SERVER_PLAYCOMMAND_H

#include "Command.h"

class PlayCommand: public Command {

public:

    virtual void execute(vector<string> args, int socket = 0, pthread_t* threadId = 0);

private:
    bool gameOver = false;
    void handleClients(int firstSocket, int secondSocket);
};


#endif //SERVER_PLAYCOMMAND_H
