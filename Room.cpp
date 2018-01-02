//
// Created by omer on 28/12/17.
//

#include "Room.h"

Room::Room(int socket, const string &roomName) :firstSocket(socket), name(roomName) {
    roomState = waiting;
    secondSocket = NULL;
}

void Room::join(int socket, pthread_t* threadId) {
    secondSocket = socket;
    threadID = threadId;
    roomState = active;
}

string Room::getName() const{
    return name;
}

int Room::getState() {
    return roomState;
}

int Room::getFirstSocket() const{
    return firstSocket;
}

int Room::getSecondSocket() const{
    return secondSocket;
}

void Room::setEnded(){
    roomState = finished;
}

pthread_t* Room::getThreadID(){
    return threadID;
}