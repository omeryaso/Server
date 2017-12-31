//
// Created by omer on 31/12/17.
//

#ifndef SERVER_ROOMLIST_H
#define SERVER_ROOMLIST_H
#include <map>
#include "Room.h"

class RoomList {
public:
    static RoomList *getInstance();
    void insertRoom(Room &room, string &roomName);
    Room* getRoom(string &roomName);
    bool isRoomExist(string &roomName);

private:
    map<string, Room*> roomsMap;
    RoomList() {}; // Private c'tor
    RoomList(const RoomList &other); // Private copy c'tor
    ~RoomList() {};

    static RoomList *instance;
};


#endif //SERVER_ROOMLIST_H



