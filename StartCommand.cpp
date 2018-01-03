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
        int n =write(socket, &error, sizeof(int)) == -1;
        if (n == -1) {
            cout << "SC: Error writing the message to the player" << endl;
            return;
        }
        cout << "Cannot join room "<<args.at(0)<<". There is already a room with a name like this\n";
        return;
    }

    Room *room = new Room(socket, args.at(0));
    roomList->insertRoom(room,args[0]);

}
