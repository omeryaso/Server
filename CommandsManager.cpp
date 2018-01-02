//
// Created by omer on 28/12/17.
//

#include "CommandsManager.h"
#include "StartCommand.h"
//#include "CloseCommand.h"
#include "PlayCommand.h"
#include "JoinCommand.h"
#include "ListGamesCommand.h"

CommandsManager* CommandsManager::instance = 0;
pthread_mutex_t CommandsManager::lock;

CommandsManager* CommandsManager::getInstance() {
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
            instance = new CommandsManager();
        }
        pthread_mutex_unlock(&lock);
    }
    return instance;
}

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new ListGamesCommand();
    commandsMap["join"] = new JoinCommand();
    commandsMap["play"] = new PlayCommand();
//    commandsMap["close"] = new CloseCommand();

}

void CommandsManager::executeCommand(string command, vector<string> args, int
socket, pthread_t* threadId) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args, socket, threadId);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}