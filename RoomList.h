//
// Created by omer on 31/12/17.
//

#ifndef SERVER_ROOMLIST_H
#define SERVER_ROOMLIST_H
#include <map>
#include <vector>
#include <list>
#include "Room.h"

class RoomList {
public:
    static RoomList *getInstance();
    void insertRoom(Room &room, string &roomName);
    void deleteRoom(string &roomName);
    void setEnded(string &roomName);
    Room* getRoom(string &roomName);
    bool isRoomExist(string &roomName);
    vector<string> getAvailableRooms();

private:

    static pthread_mutex_t lock;
    pthread_mutex_t roomsMapMutex;
    map<string, Room*> roomsMap;
    RoomList() {}; // Private c'tor
    RoomList(const RoomList &other); // Private copy c'tor
    ~RoomList() {};

    static RoomList *instance;
};


#endif //SERVER_ROOMLIST_H
