//
// Created by shlomy on 06/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


class Server {
public:
    Server();
    void start();
    void Play();
    void stop();

private:
    int fCS; // first client socket
    int sCS; // second client socket
    int port;
    int serverSocket; // the socket's file descriptor
    static const int maxMove = 8; // the input maximum size.
    bool gameOver = false;
    int acceptClients();
    int handleClients(int firstClient, int secondClient);
};


#endif //SERVER_SERVER_H