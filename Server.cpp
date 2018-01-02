//
// Created by shlomy on 06/12/17.
//

#include "Server.h"

using namespace std;

#define MAX_CONNECTED_CLIENTS 1000
#define MAX_COMMAND_LEN 50

struct ThreadArgs {
    pthread_t* id;
    int serverSocket;
};

static void *acceptClients(void *);
static void *handleClient(void *);

Server::Server(): serverSocket(0) {
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
    pthread_create(&serverThreadId, NULL, &acceptClients, (void *)serverSocket);

}

// Handle requests from a specific client
static void *acceptClients(void *socket) {

    long serverSocket = (long) socket;
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";
        pthread_t threadId;

        ThreadArgs args;
        args.serverSocket = clientSocket;
        args.id = &threadId;

        pthread_create(&threadId, NULL, &handleClient,  &args);
    }

//    bool firstTurn = true;
//    int error;
//    while (true) {
//        cout << "Waiting for client connections..." << endl;
//
//        //accepting clients and if something want wrong exception is thrown
//        if(!acceptClients())
//            throw "Error on accept";
//
//        while(!gameOver){
//            if(firstTurn) {
//                error = handleClients(fCS, sCS);
//                firstTurn = false;
//            }
//            else {
//                error = handleClients(sCS, fCS);
//                firstTurn = true;
//            }
//
//            if(error)
//                gameOver=true;
//        }
//
//        // Close communication with the first client
//        close(fCS);
//        cout << "First client disconnected" << endl;
//        // Close communication with the second client
//        close(sCS);
//        cout << "Second client disconnected" << endl;
//        gameOver = false;
//        firstTurn = true;
//    }

}

// Handle requests from a specific client
//int Server::handleClients(int carrier, int receiver) {
//
//    int size = 0;
//    // Read new exercise arguments
//    int r = read(carrier, &size, sizeof(int));
//
//    char input[size];
////    bzero((char *)input, maxMove*sizeof(char));
//    if (r == -1) {
//        cout << "Error reading move" << endl;
//        gameOver = true;
//        return 1;
//    }
//    if (r == 0) {
//        cout << "Client disconnected" << endl;
//        gameOver = true;
//        return 1;
//    }
//
//    int c = read(carrier, &input, size * sizeof(char));
//    //input validity
//    if (c == -1) {
//        cout << "Error reading move" << endl;
//        return 1;
//    }
//    if (c == 0) {
//        cout << "Client disconnected" << endl;
//        return 1;
//    }
//
//    //check if the input value indicates that the game is over
//    if (!strcmp(input, "End"))
//    {
//        cout << "End" << endl;
//        return 1;
//    }
//
//    if (!strcmp(input, "NoMove")){
//        cout << "NoMove" << endl;
//        return 0;
//    }
//
//    cout << "Got input: " << input << endl;
//
//    // Write the result back to the client
//    r = write(receiver, &size, sizeof(size));
//
//    if (r == -1) {
//        cout << "Error writing to socket" << endl;
//        return 1;
//    }
//
//    c = write(receiver, &input, sizeof(input));
//
//    if (c == -1) {
//        cout << "Error writing to socket" << endl;
//        return 1;
//    }
//
//    return 0;
//}


static void *handleClient(void *tArgs) {
    struct ThreadArgs *args = (struct ThreadArgs *)tArgs;
    long clientSocket = (long)args->serverSocket;
    char commandStr[MAX_COMMAND_LEN];
    // Read the command from the socket
    int n = read(clientSocket, commandStr, MAX_COMMAND_LEN);
    if (n == -1) {
        cout << "Error reading command" << endl;
        return NULL;
    }
    cout << "Received command: " << commandStr << endl;
    // Split the command string to the command name and the arguments
    string str(commandStr);
    istringstream iss(str);
    string command;
    iss >> command;
    vector<string> argsStr;
    while (iss) {
        string arg;
        iss >> arg;
        argsStr.push_back(arg);
    }
    CommandsManager::getInstance()->executeCommand(command, argsStr, clientSocket, args->id );
    return NULL;
}

void Server::stop() {
    close(serverSocket);
}

//todo: moved to start\join command delete if everything work.
//int Server::acceptClients() {
//    int order = 1;
//
//    // Define the client socket's structures
//    struct sockaddr_in clientAddress;
//    socklen_t clientAddressLen;
//
//    // Accept first client connection
//    fCS = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
//    cout << "first client connected" << endl;
//
//    // Accept second client connection
//    sCS = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
//    cout << "second client connected" << endl;
//    if (fCS == -1 || sCS == -1)
//        return 0;
//
//    //returns to each client if he connected first or second.
//    //in case of an error prints were the error is end returns 0.
//    if(write(fCS, &order, sizeof(int)) == -1) {
//        cout << "Error writing the turn of the first client";
//        return 0;
//    }
//    order++;
//    if(write(sCS, &order, sizeof(int)) == -1) {
//        cout << "Error writing the turn of the second client";
//        return 0;
//    }
//
//    return 1;
//}