//
// Created by omer on 28/12/17.
//

#include <cstdlib>
#include "JoinCommand.h"
#include "Room.h"

JoinCommand::JoinCommand() {

}

void JoinCommand::execute(vector<string> args) {
    // args[0] = the name of the room that wished to be opened, args[1] = the player's socket
    RoomList roomList();
    Room room = roomList;
    int socket = atoi(args.at(1).c_str());
    room.join(socket);

}
