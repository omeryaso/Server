//
// Created by omer on 28/12/17.
//

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include "ListGamesCommand.h"
#include "RoomList.h"

void ListGamesCommand::execute(vector<string> args, int socket,pthread_t* threadId) {
    std::ostringstream oss;
    RoomList* roomList = RoomList::getInstance();
    vector<string> rooms = roomList->getAvailableRooms();
    int size = 2 * rooms.size();

    if (!rooms.empty()) {
        // Convert all but the last element to avoid a trailing ","
        copy(rooms.begin(), rooms.end()-1, ostream_iterator<string>(oss, ","));

        // Now add the last element with no delimiter
        oss << rooms.back();
    }

    // Write the list size back to the client
    int s = write(socket, &size, sizeof(size));

    if (s == -1) {
        cout << "ListGames CMD: Error writing to socket" << endl;
        return;
    }

    if(size) {
        // Write the list back to the client
        int l = write(socket, oss, sizeof(oss));

        if (l == -1) {
            cout << "ListGames CMD: Error writing to socket" << endl;
            return;
        }
    }
}
