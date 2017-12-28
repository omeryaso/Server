//
// Created by omer on 28/12/17.
//

#ifndef SERVER_LISTGAMESCOMMAND_H
#define SERVER_LISTGAMESCOMMAND_H


#include "Command.h"
#include "Room.h"

class ListGamesCommand: public Command {


public:

    ListGamesCommand(vector<Room> &gamesList , int socket);

    virtual void execute(vector<string> args) {}
};


#endif //SERVER_LISTGAMESCOMMAND_H
