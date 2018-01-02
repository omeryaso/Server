//
// Created by omer on 28/12/17.
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H


#include <map>
#include "Command.h"

class CommandsManager {

public:
    static CommandsManager* getInstance();
    void executeCommand(string command, vector<string> args, int socket = 0, pthread_t* threadId = 0);

private:
    // A singleton
    CommandsManager();
    CommandsManager(const CommandsManager &);
    ~CommandsManager();
    static CommandsManager* instance;
    static pthread_mutex_t lock;

    map<string, Command *> commandsMap;
};

#endif //SERVER_COMMANDSMANAGER_H