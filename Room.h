//
// Created by omer on 28/12/17.
//

#ifndef SERVER_ROOM_H
#define SERVER_ROOM_H
#include <string>
#include <map>

using namespace std;

enum state {waiting = 0, active = 1};


class Room {

public:

    /**
    * @name : Room
    * @parameters : socket- this will be the first client socket
    *               room - this is the name (string) of the room
    **/
    Room(int socket, const string &roomName);

    /**
    * @name : Join
    * @parameters : socket - the function will initialize socket to be the
     * second player socket.
    **/
    void join(int socket);

    /**
    * @name : Room
    * @return : returns the name of this room.
    **/
    string getName () const;

    /**
    * @name : getState
    * @return : returns the state of this room. 0 if its waiting for client
    * and 1 if the room is active.
    **/
    int getState();

    /**
    * @name : getFirstSocket
    * @return : returns first Second Socket
    **/
    int getFirstSocket() const;

    /**
    * @name : getSecondSocket
    * @return : returns second Second Socket
    **/
    int getSecondSocket() const;

private:
    string name;
    int firstSocket;
    int secondSocket;
    state roomState;
};

#endif //SERVER_ROOM_H
