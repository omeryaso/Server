//
// Created by omer on 28/12/17.
//

#include <unistd.h>
#include "Room.h"

Room::Room(int socket, const string &roomName) :firstSocket(socket), name(roomName) {
    roomState = waiting;
}

void Room::join(int socket, pthread_t* threadId) {
    secondSocket = socket;
    threadID = threadId;
    roomState = active;
}



int Room::getState() {
    return roomState;
}

int Room::getFirstSocket() const{
    return firstSocket;
}


Room::~Room() {
    close(firstSocket);
    close(secondSocket);
    if (roomState== active)
        pthread_cancel(*threadID);
}
