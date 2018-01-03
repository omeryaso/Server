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
    * @name : *getInstance
    * @parameters : ignored
    * @return : returns an instance of roomList (creat new one if not exist)
    **/
    static RoomList *getInstance();

    /**
    * @name : RoomList
    * @parameters : socket- this will be the first client socket
    * @return: ignored
    * @brief: insert a room to gameList map
    **/
    void insertRoom(Room *room, string &roomName);

    /**
    * @name : RoomList
    * @parameters :
    * @return:
    **/
    void deleteRoom(string &roomName);

    /**
     * @name : closeAllRooms
     * @brief closing all the rooms in the map
     * @parameters : ignored
     * @return: ignored
     **/
    void closeAllRooms();

    /**
    * @name : getRoom
    * @parameters : roomName - the name of the room
    * @return: returns pointer to the room
    **/
    Room* getRoom(string &roomName);

    /**
    * @name : isRoomExist
    * @parameters : roomName- the room name
    * @return: return true if the room exist false otherwise
    **/
    bool isRoomExist(string &roomName);

    /**
    * @name : getAvailableRooms
    * @parameters : ignored
    * @return: return a vector with the game available rooms
    **/
    vector<string> getAvailableRooms();

    /**
    * @name : closeRoom
    * @parameters : roomName - closing the room
    * @return: ignored
    **/
    void closeRoom(string &roomName);

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
