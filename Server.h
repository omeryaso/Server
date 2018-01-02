//
// Created by shlomy on 06/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <sys/types.h>
#include "CommandsManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

class Server {
public:
    Server();
    void start();
    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    pthread_t serverThreadId;
    bool shutDown = false;
};


#endif //SERVER_SERVER_H