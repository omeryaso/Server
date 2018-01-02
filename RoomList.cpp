//
// Created by omer on 31/12/17.
//

#include "RoomList.h"
#include <iostream>
#include <algorithm>

RoomList *RoomList::instance = 0;
pthread_mutex_t RoomList::lock;
RoomList *RoomList::getInstance()
{
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
        instance = new RoomList;
        }
        pthread_mutex_unlock(&lock);
    }
    return instance;
}

void RoomList::insertRoom(Room &room, string &roomName) {
    roomsMap[roomName] = &room;
}

void RoomList::deleteRoom(string &roomName) {
    roomsMap.erase(roomName);
}

bool RoomList::isRoomExist(string &roomName) {
    if(roomsMap.count(roomName))
        return true;
    return false;
}

Room* RoomList::getRoom(string &roomName) {
    return roomsMap[roomName];
}

vector<string> RoomList::getAvailableRooms() {
    vector<string> availableRooms;
    pthread_mutex_lock(&roomsMapMutex);
    for (map<string, Room*>::iterator it = roomsMap.begin(); it != roomsMap.end(); it++) {
        if (it->second->getState() == waiting)
            availableRooms.push_back(it->first);
    }
    pthread_mutex_unlock(&roomsMapMutex);

    return availableRooms;
}

void RoomList::setEnded(string &roomName) {
    roomsMap[roomName];

}