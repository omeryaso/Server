//
// Created by omer on 28/12/17.
//

#ifndef SERVER_PLAYCOMMAND_H
#define SERVER_PLAYCOMMAND_H

#include "Command.h"

class PlayCommand: public Command {

public:
    virtual void execute(vector<string> args) {}
};


#endif //SERVER_PLAYCOMMAND_H
