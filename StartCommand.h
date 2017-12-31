//
// Created by omer on 28/12/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H

#include "Command.h"
#include "Server.h"
#include "Room.h"


class StartCommand: public Command {

public:

    StartCommand(vector<Room> &gl);
    virtual void execute(vector<string> args);

private:
    vector<Room>& gamesList;

};

#endif //SERVER_STARTCOMMAND_H