cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-pthread")

set(SOURCE_FILES main.cpp Server.cpp Server.h Command.h CommandsManager.cpp
        CommandsManager.h JoinCommand.cpp JoinCommand.h ListGamesCommand.h
        ListGamesCommand.cpp Room.h Room.cpp RoomList.h RoomList.cpp StartCommand.h StartCommand.cpp ThreadPool.h ThreadPool.cpp)
add_executable(Server ${SOURCE_FILES})