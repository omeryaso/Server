//
// Created by omer on 02/01/18.
//

#include <unistd.h>
#include <iostream>
#include <cstring>
#include "PlayCommand.h"
#include "Room.h"
#include "RoomList.h"

void PlayCommand::execute(vector<string> args, int socket, pthread_t *threadId) {

    // args[0] = the name of the room that wished to be opened
    RoomList* roomList = RoomList::getInstance();

    if (!roomList->isRoomExist(args.at(0)))
        return;

    Room *room = roomList->getRoom(args.at(0));

    // put both the sockets into integers.
    int fCS = room->getFirstSocket();
    int sCS = room->getSecondSocket();
    bool firstTurn = true;

    while(!gameOver){
        if(firstTurn) {
            handleClients(fCS, sCS);
            firstTurn = false;
        }
        else {
            handleClients(sCS, fCS);
            firstTurn = true;
        }
    }

    roomList->getRoom(args.at(0))->setEnded();
}

void PlayCommand::handleClients(int fCs, int sCS) {

    int size = 0;
    // Read new exercise arguments
    int r = read(fCs, &size, sizeof(int));

    char input[size];
    bzero((char *)input, size*sizeof(char));
    if (r == -1) {
        cout << "Error reading move" << endl;
        gameOver = true;
        return;
    }
    if (r == 0) {
        cout << "Client disconnected" << endl;
        gameOver = true;
        return;
    }

    int c = read(fCs, &input, size * sizeof(char));
    //input validity
    if (c == -1) {
        cout << "Error reading move" << endl;
        gameOver = true;
        return;
    }
    if (c == 0) {
        cout << "Client disconnected" << endl;
        gameOver = true;
        return;
    }

    //check if the input value indicates that the game is over
    if (!strcmp(input, "End"))
    {
        cout << "End" << endl;
        gameOver = true;
        return;
    }

    if (!strcmp(input, "NoMove")){
        cout << "NoMove" << endl;
        return;
    }

    cout << "Got input: " << input << endl;

    // Write the result back to the client
    r = write(sCS, &size, sizeof(size));

    if (r == -1) {
        cout << "Error writing to socket" << endl;
        gameOver = true;
        return;
    }

    c = write(sCS, &input, sizeof(input));

    if (c == -1) {
        cout << "Error writing to socket" << endl;
        gameOver = true;
        return;
    }
}
