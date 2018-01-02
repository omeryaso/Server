//
// Created by shlomy on 06/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <sys/types.h>

class Server {
public:
    Server();
    void start();
    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    pthread_t serverThreadId;
};


#endif //SERVER_SERVER_H