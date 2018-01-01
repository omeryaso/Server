//
// Created by omer on 28/12/17.
//

#include <cstdlib>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include "JoinCommand.h"
#include "Room.h"
#include "RoomList.h"



void JoinCommand::execute(vector<string> args) {
    // args[0] = the name of the room that wished to be opened, args[1] =the server socket
    RoomList* roomList = RoomList::getInstance();
    if (!roomList->isRoomExist(args.at(0)))
        return;
    Room *room = roomList->getRoom(args.at(0));
    if (room->getState() == active)
        return;
    int serverSocket = atoi(args.at(1).c_str());

    int order = 2;

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    // Accept first client connection
    int fCS = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

    room->join(fCS);

    //returns to each client if he connected first or second.
    //in case of an error prints were the error is end returns 0.
    if(write(fCS, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the first client";
        return;
    }
    cout << args.at(0)<< ": second client connected, let the game begin" << endl;
}