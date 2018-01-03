//
// Created by omer on 28/12/17.
//


#include <unistd.h>
#include <iostream>
#include <memory.h>
#include "Room.h"
#include "RoomList.h"
#include "JoinCommand.h"
#include "CommandsManager.h"


void JoinCommand::execute(vector<string> args, int socket, pthread_t* threadId) {

    int error;
    // args[0] = the name of the room that wished to be opened
    RoomList* roomList = RoomList::getInstance();
    if (!roomList->isRoomExist(args.at(0))){
        error = -2;
        int n= write(socket, &error, sizeof(int));
        if (n == -1) {
            cout << "JC: Error writing the message to the player" << endl;
            return;
        }
        cout << "cannot join game "<<args.at(0)<<". it doesn't exist.\n";
        return;
    }
    Room *room = roomList->getRoom(args.at(0));

    // put both the sockets into integers.
    int fCs = room->getFirstSocket();
    int sCS = socket;

    //if the room that wished to be joined is full already then return -1
    if (room->getState() == active) {
        error = -1;
        int n= write(sCS, &error, sizeof(int));
        if (n == -1) {
            cout << "JC: Error writing the message to the player" << endl;
            return;
        }
            cout << "cannot join game "<<args.at(0)<<". it is already full\n";
        return;
    }

    int order = 1;
    room->join(sCS, threadId);
    if(write(fCs, &order, sizeof(int)) == -1) {
        cout << "JC:Error writing the turn of the first client" << endl;
        return;
    }
    order++;
    cout << "first client connected to game: " << args.at(0)<<endl;
    //returns to client if he connected
    //in case of an error prints were the error is end returns.
    if(write(sCS, &order, sizeof(int)) == -1) {
        cout << "JC:Error writing the turn of the second client";
        return;
    }
    cout << "second client connected to game: "   << args.at(0)<<". let's get ready to rumbleeeee!!!" << endl;

    bool firstTurn = true;
    bool over;
    while(!room->getGameOver()){
        if(firstTurn) {
            over = handleClients(fCs, sCS);
            firstTurn = false;
        }
        else {
            over = handleClients(sCS, fCs);
            firstTurn = true;
        }
        room->setGameOver(over);
    }

    roomList->closeRoom(args.at(0));

}


bool JoinCommand::handleClients(int fCs, int sCS) {

    int size = 0;
    // Read new exercise arguments
    int r = read(fCs, &size, sizeof(int));

    char input[size];
    bzero((char *)input, size*sizeof(char));
    if (r == -1) {
        cout << "Error reading move" << endl;
        return true;
    }
    if (r == 0) {
        cout << "Client disconnected" << endl;
        return true;
    }

    int c = read(fCs, &input, size * sizeof(char));
    //input validity
    if (c == -1) {
        cout << "Error reading move" << endl;
        return true;
    }
    if (c == 0) {
        cout << "Client disconnected" << endl;
        return true;
    }

    //check if the input value indicates that the game is over
    if (!strcmp(input, "End"))
    {
        cout << "End" << endl;
        return true;
    }

    if (!strcmp(input, "NoMove")){
        cout << "NoMove" << endl;
        return false;
    }

    cout << "Got input: " << input << endl;

    // Write the result back to the client
    r = write(sCS, &size, sizeof(size));

    if (r == -1) {
        cout << "Error writing to socket" << endl;
        return true;
    }

    c = write(sCS, &input, sizeof(input));

    if (c == -1) {
        cout << "Error writing to socket" << endl;
        return true;
    }

    return false;
}