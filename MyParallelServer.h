//
// Created by michael on 09/01/2020.
//
#ifndef EX4__MYPARALLELSERVER_H_
#define EX4__MYPARALLELSERVER_H_
#include "Server.h"
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include "AlgServer.h"
#include <queue>
#include <mutex>

using namespace server_side;

class MyParallelServer : Server {
 private:
  vector<thread> clientVect;
  int client_socket;

 public:
  MyParallelServer() {};
  ~MyParallelServer();
  int open(int port, ClientHandler *c);
  static void clientExecution(ClientHandler *c, int clientSock);
  void stop();
};

#endif //EX4__MYSERIALSERVER_H_