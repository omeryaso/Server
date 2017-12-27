//
// Created by shlomy on 06/12/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2


Server::Server(): serverSocket(0) {
    gameOver = false;
    int p;
    ifstream objectFile("../serverConfig.txt");
    if(!objectFile)
        throw "Error reading network configuration file";
    objectFile >> p;
    objectFile.close();
    port = p;
    cout << "Server" << endl;
}

void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

}

// Handle requests from a specific client
void Server::Play() {
    bool firstTurn = true;
    int error;
    while (true) {
        cout << "Waiting for client connections..." << endl;

        //accepting clients and if something want wrong exception is thrown
        if(!acceptClients())
            throw "Error on accept";

        while(!gameOver){
            if(firstTurn) {
                error = handleClients(fCS, sCS);
                firstTurn = false;
            }
            else {
                error = handleClients(sCS, fCS);
                firstTurn = true;
            }

            if(error)
                gameOver=true;
        }

        // Close communication with the first client
        close(fCS);
        cout << "First client disconnected" << endl;
        // Close communication with the second client
        close(sCS);
        cout << "Second client disconnected" << endl;
        gameOver = false;
        firstTurn = true;
    }

}

// Handle requests from a specific client
int Server::handleClients(int carrier, int receiver) {

//    bzero((char *)input, sizeof(input));
    int row, col;
    int size = 0;
    // Read new exercise arguments
    int r = read(carrier, &size, sizeof(int));

    char input[size];
    if (r == -1) {
        cout << "Error reading move" << endl;
        gameOver = true;
        return 1;
    }
    if (r == 0) {
        cout << "Client disconnected" << endl;
        gameOver = true;
        return 1;
    }

    int c = read(carrier, &input, size * sizeof(char));
    //inputx validity
    if (c == -1) {
        cout << "Error reading move" << endl;
        gameOver = true;
        return 1;
    }
    if (c == 0) {
        cout << "Client disconnected" << endl;
        gameOver = true;
        return 1;
    }

//      TODO: Convert input to string

    cout << "Got input: " << row+1 << ", " << col+1 << endl;

    //check if the input value indicates that the game is over
    if (input == "End")
    {
        cout << "End" << endl;
        gameOver = true;
        return 0;
    }

    if (input == "NoMove"){
        cout << "NoMove" << endl;
        return 0;
    }

    // Convert the number into a string.
    row = atoi(reinterpret_cast<const char *>(input[0]));
    col = atoi(reinterpret_cast<const char *>(input[2]));

    // Write the result back to the client
    r = write(receiver, &row, sizeof(int));
    c = write(receiver, &col, sizeof(int));
    if (r == -1 || c == -1) {
        cout << "Error writing to socket" << endl;
        return 1;
    }

    return 0;
}

void Server::stop() {
    close(serverSocket);
}

int Server::acceptClients() {
    int order = 1;

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    // Accept first client connection
    fCS = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
    cout << "first client connected" << endl;

    // Accept second client connection
    sCS = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
    cout << "second client connected" << endl;
    if (fCS == -1 || sCS == -1)
        return 0;

    //returns to each client if he connected first or second.
    //in case of an error prints were the error is end returns 0.
    if(write(fCS, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the first client";
        return 0;
    }
    order++;
    if(write(sCS, &order, sizeof(int)) == -1) {
        cout << "Error writing the turn of the second client";
        return 0;
    }

    return 1;
}