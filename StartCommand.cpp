//
// Created by omer on 28/12/17.
//

#include <cstdlib>
#include "StartCommand.h"
#include "RoomList.h"



void StartCommand::execute(vector<string> args) {
    // args[0] = the name of the room that wished to be opened, args[1] = the player's socket
    RoomList* roomList = RoomList::getInstance();
    if(roomList->isRoomExist(args.at(0)))
        return;
    int socket = atoi(args.at(1).c_str());
    Room room(socket, args.at(0));
    roomList->insertRoom(room,args[0]);
}
