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
    /**
    * @name : Room
    * @parameters : socket- this will be the first client socket
    *               room - this is the name (string) of the room
    **/
    static RoomList *getInstance();

    /**
    * @name : RoomList
    * @parameters : socket- this will be the first client socket
    * @return:
    **/
    void insertRoom(Room *room, string &roomName);

    /**
    * @name : RoomList
    * @parameters :
    * @return:
    **/
    void deleteRoom(string &roomName);

    /**
     * @name : RoomList
     * @parameters :
     * @return:
     **/
    void setEnded(string &roomName);

    /**
    * @name : RoomList
    * @parameters :
    * @return:
    **/
    Room* getRoom(string &roomName);

    /**
    * @name : RoomList
    * @parameters : socket- this will be the first client socket
    * @return:
    **/
    bool isRoomExist(string &roomName);

    /**
    * @name : RoomList
    * @parameters :
    * @return:
    **/
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
