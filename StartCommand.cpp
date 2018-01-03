//
// Created by omer on 28/12/17.
//

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "RoomList.h"
#include "StartCommand.h"


void StartCommand::execute(vector<string> args, int socket, pthread_t*threadId) {

    // args[0] = the name of the room that wished to be opened, args[1] = the
    // server socket
    RoomList* roomList = RoomList::getInstance();

    int error = -1;

    //if the room exists return to the player -1
    if(roomList->isRoomExist(args.at(0))) {
        if(write(socket, &error, sizeof(int)) == -1) {
            cout << "Error writing the turn of the first client";
        }
        return;
    }

    Room *room = new Room(socket, args.at(0));
    roomList->insertRoom(room,args[0]);

}
