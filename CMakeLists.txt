cmake_minimum_required(VERSION 3.15)
project(Ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Ex4 Main.cpp CacheManager.cpp CacheManager.h FileCacheManager.cpp FileCacheManager.h MyTestClientHandler.cpp MyTestClientHandler.h Server.cpp Server.h MySerialServer.cpp MySerialServer.h Solver.cpp Solver.h StringReverser.cpp StringReverser.h AlgServer.cpp AlgServer.h SockStreams.cpp SockStreams.h QA.cpp QA.h Searcher.h Searchable.h)