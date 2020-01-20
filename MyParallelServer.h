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
  int isStop = 0;
  int client_socket;

 public:
  int open(int port, ClientHandler *c) {
    //create socket
    int sockIn = socket(AF_INET, SOCK_STREAM, 0); //socket for input
    if (sockIn == -1) {
      //error
      std::cerr << "Could not create a socket" << std::endl;
      exit(1);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //we need to convert our number to a number that the network understands
    //the actual bind command
    if (bind(sockIn, (struct sockaddr *) &address, sizeof(address)) == -1) {
      std::cerr << "Could not bind the socket to an IP" << std::endl;
      exit(1);
    }

    //making socket listen to the port
    if (listen(sockIn, 20) == -1) {
      //can also set to SOMAXCON (max connections)
      std::cerr << "Error during listening command" << std::endl;
      exit(1);
    } else {
      std::cout << "Server is now listening ..." << std::endl;
    }

    while (true) {
      struct timeval tv;
      tv.tv_sec = 120;
      setsockopt(sockIn, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

      client_socket = accept(sockIn, (struct sockaddr *) &address,
                             (socklen_t *) &address);

      if (client_socket < 0) {
        if (errno == EWOULDBLOCK) {
          cout << "timeout!" << endl;
          break;
        } else {
          cerr << "Error accepting connection" << endl;
          break;
        }
      }

      // creating clone of client handler and creating the thread
      thread tr(&MyParallelServer::clientExecution, this, c->createClone(), client_socket);
      tr.detach();
    }
    this->stop();
    if (client_socket != -1) {
      this->stop();
    }

    return 1;
  }

  void clientExecution(ClientHandler *c, int clientSock) {
    c->handleClient(new SocketInputStream(clientSock),
                    new SocketOutputStream(clientSock));
  }

  void stop() {
    this->isStop = 1;
    close(client_socket); //closing the listening socket
  }

};

#endif //EX4__MYSERIALSERVER_H_