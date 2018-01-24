//
// Created by shlomy on 06/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <sys/types.h>
#include "CommandsManager.h"
#include "ThreadPool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

class Server {
public:
    /**
    * @name : server
    * @brief : the server constructor
    **/
    Server();

    /**
    * @name : start
    * @brief : starts the server
    **/
    void start();

    /**
    * @name : stop
    * @return : stops the server
    **/
    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    pthread_t serverThreadId;
    ThreadPool *pool;
};


#endif //SERVER_SERVER_H