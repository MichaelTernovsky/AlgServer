cmake_minimum_required(VERSION 3.15)
project(Ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ex4 main.cpp CacheManager.cpp CacheManager.h ClientHandler.cpp ClientHandler.h FileCacheManager.cpp FileCacheManager.h MyTestClientHandler.cpp MyTestClientHandler.h Server.cpp Server.h MySerialServer.cpp MySerialServer.h Solver.cpp Solver.h StringReverser.cpp StringReverser.h)