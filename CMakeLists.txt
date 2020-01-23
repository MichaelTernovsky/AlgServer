cmake_minimum_required(VERSION 3.15)
project(Ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Ex4 Main.cpp CacheManager.h FileCacheManager.h MyTestClientHandler.h Server.h MySerialServer.h Solver.h StringReverser.cpp StringReverser.h AlgServer.h SockStreams.cpp SockStreams.h OA.h Searcher.h Searchable.h BestFS.h MatrixProblem.h State.h MyClientHandler.h DFS.h BFS.h MyParallelServer.h Astar.h)