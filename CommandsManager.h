//
// Created by omer on 28/12/17.
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H


#include <map>
#include "Command.h"

class CommandsManager {

public:
    /**
    * @name : *getInstance
    * @parameters : ignored
    * @return : returns an instance of CommandsManager (creates new one if not exist)
    **/
    static CommandsManager* getInstance();

    /**
    * @name : executeCommand
    * @parametars : command - the string of the command that we want to use
    *               args - vector of args that we want to pass (first one usually a command)
    *               socket- the number of the socket that is sent
    *              threadId - the id of the thread that we started
    * @brief : gets the argument from the command and execute them according to the command it gets in the string
    * @return : ignored
    **/
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