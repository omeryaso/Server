//
// Created by omer on 28/12/17.
//

#include <cstdlib>
#include "JoinCommand.h"
#include "Room.h"
#include "RoomList.h"



void JoinCommand::execute(vector<string> args) {
    // args[0] = the name of the room that wished to be opened, args[1] = the player's socket
    RoomList* roomList = RoomList::getInstance();
    if (!roomList->isRoomExist(args.at(0)))
        return;
    Room *room = roomList->getRoom(args.at(0));
    if (room->getState() == active)
        return;
    int socket = atoi(args.at(1).c_str());
    room->join(socket);

}
