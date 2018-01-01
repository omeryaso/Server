//
// Created by omer on 28/12/17.
//

#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include "StartCommand.h"
#include "RoomList.h"



void StartCommand::execute(vector<string> args) {
    // args[0] = the name of the room that wished to be opened, args[1] = the
    // server socket
    RoomList* roomList = RoomList::getInstance();
    int serverSocket = atoi(args.at(1).c_str());

    int order = 1;
    int error = -1;

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    // Accept first client connection
    int fCS = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

    //if the room exists return to the player -1
    if(roomList->isRoomExist(args.at(0))) {
        if(write(fCS, &error, sizeof(int)) == -1) {
            cout << "Error writing the turn of the first client";
        }
        return;
    }

    Room room(fCS, args.at(0));
    roomList->insertRoom(room,args[0]);

    //returns to each client if he connected first or second.
    //in case of an error prints were the error is end returns 0.
    if(write(fCS, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the first client";
        return;
    }
    cout << args.at(0)<< ": first client connected" << endl;
}
