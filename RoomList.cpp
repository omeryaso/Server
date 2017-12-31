//
// Created by omer on 31/12/17.
//

#include "RoomList.h"
#include <iostream>

using namespace std;

RoomList *RoomList::instance = 0;

RoomList *RoomList::getInstance()
{
    if (instance == 0)
    {
        instance = new RoomList;
    }
    return instance;
}

void RoomList::insertRoom(Room &room, string &roomName) {
    roomsMap[roomName] = &room;
}

bool RoomList::isRoomExist(string &roomName) {
    if(roomsMap.count(roomName))
        return true;
    return false;
}

Room* RoomList::getRoom(string &roomName) {
    return roomsMap[roomName];
}