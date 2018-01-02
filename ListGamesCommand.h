//
// Created by omer on 28/12/17.
//

#ifndef SERVER_LISTGAMESCOMMAND_H
#define SERVER_LISTGAMESCOMMAND_H


#include "Command.h"
#include "Room.h"

class ListGamesCommand: public Command {


public:

    virtual void execute(vector<string> args, int socket = 0, pthread_t* 
    threadId = 0);
};


#endif //SERVER_LISTGAMESCOMMAND_H
