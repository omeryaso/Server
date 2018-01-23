//
// Created by shlomy on 06/12/17.
//

#include "Server.h"
#include "RoomList.h"

using namespace std;

#define MAX_CONNECTED_CLIENTS 1000
#define MAX_COMMAND_LEN 50
#define THREADS_NUM 5

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
//      todo: Task *task = new Task(&handleClient, &args);
//       todo: pool.addTask(task);
        pthread_create(&threadId, NULL, &handleClient,  &args);
    }

}

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
    //todo: pool.terminate();
    RoomList* roomList = RoomList::getInstance();
    roomList->closeAllRooms();
}