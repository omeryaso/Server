//
// Created by omer on 28/12/17.
//


#include <cstring>
#include <iostream>
#include <unistd.h>
#include "PlayCommand.h"
#include "Room.h"
#include "RoomList.h"

void PlayCommand::execute(vector<string> args, int socket, pthread_t* threadId) {

    RoomList* roomList = RoomList::getInstance();
    Room *room = roomList->getRoom(args.at(0));
    int size = 0;
    int carrier , receiver;

    if(strcmp(args.at(1).c_str(), "first")) {
        carrier = room->getFirstSocket();
        receiver = room->getSecondSocket();
    } else {
        carrier = room->getSecondSocket();
        receiver = room->getFirstSocket();
    }
    // Read new exercise arguments
    int r = read(carrier, &size, sizeof(int));
    char input[size];
    if (r == -1) {
        cout << "Error reading move" << endl;
        room->setEnded();
        return;
    }
    if (r == 0) {
        cout << "Client disconnected" << endl;
        room->setEnded();
        return ;
    }

    int c = read(carrier, &input, size * sizeof(char));
    //input validity
    if (c == -1) {
        cout << "Error reading move" << endl;
        room->setEnded();
        return;
    }
    if (c == 0) {
        cout << "Client disconnected" << endl;
        room->setEnded();
        return;
    }

    //check if the input value indicates that the game is over
    if (!strcmp(input, "End"))
    {
        cout << "End" << endl;
        room->setEnded();
        return;
    }

    if (!strcmp(input, "NoMove")){
        cout << "NoMove" << endl;
        return;
    }

    cout << "Got input: " << input << endl;

    // Write the result back to the client
    r = write(receiver, &size, sizeof(size));

    if (r == -1) {
        cout << "Error writing to socket" << endl;
        room->setEnded();
        return;
    }

    c = write(receiver, &input, sizeof(input));
    if (c == -1) {
        cout << "Error writing to socket" << endl;
        room->setEnded();
        return;
    }

}
