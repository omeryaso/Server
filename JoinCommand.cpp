//
// Created by omer on 28/12/17.
//


#include <unistd.h>
#include <iostream>
#include "Room.h"
#include "RoomList.h"
#include "JoinCommand.h"


void JoinCommand::execute(vector<string> args, int socket, pthread_t* threadId) {
    // args[0] = the name of the room that wished to be opened
    RoomList* roomList = RoomList::getInstance();
    if (!roomList->isRoomExist(args.at(0)))
        return;
    Room *room = roomList->getRoom(args.at(0));

    // Accept first client connection
    int fCS = socket;

    if (room->getState() == active) {
        int order = -1;
        if(write(fCS, &order, sizeof(int)) == -1) {
            cout << "Error writing the turn of the first client";
        }
        return;
    }

    int order = 2;

    room->join(fCS, threadId);

    //returns to client if he connected
    //in case of an error prints were the error is end returns.
    if(write(fCS, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the first client";
        return;
    }
    cout << args.at(0)<< ": second client connected, let the game begin" << endl;
}