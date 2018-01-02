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

    // put both the sockets into integers.
    int fCs = room->getFirstSocket();
    int sCS = socket;

    //if the room that wished to be joined is full already then return -1
    if (room->getState() == active) {
        int error = -1;
        int n= write(sCS, &error, sizeof(int));
        if (n == -1) {
            cout << "JC: Error writing the message to the player";
            return;
        }
            cout << "cannot join game "<<args.at(0)<<". it is already full\n";
        return;
    }

    int order = 1;
    room->join(sCS, threadId);
    if(write(fCs, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the first client";
        return;
    }
    cout << args.at(0)<< "first client connected to game: " << args.at(0)<<endl;
    //returns to client if he connected
    //in case of an error prints were the error is end returns.
    if(write(sCS, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the first client";
        return;
    }
    cout << args.at(0)<< "second client connected to game:"   << args.at(0)<<". let the game begin" << endl;


}