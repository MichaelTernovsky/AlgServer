//
// Created by michael on 09/01/2020.
//
#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_
#include "Server.h"
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include "AlgServer.h"
using namespace server_side;
extern int client_socket;

class MySerialServer : Server {
 private:
  int isStop = 0;

 public:
  void runExucteMethosAsThread(int portNum, ClientHandler *client_handler) {

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
    address.sin_port = htons(portNum);

    //we need to convert our number to a number that the network understands
    //the actual bind command
    if (bind(sockIn, (struct sockaddr *) &address, sizeof(address)) == -1) {
      std::cerr << "Could not bind the socket to an IP" << std::endl;
      exit(1);
    }

    //making socket listen to the port
    if (listen(sockIn, 5) == -1) {
      //can also set to SOMAXCON (max connections)
      std::cerr << "Error during listening command" << std::endl;
      exit(1);
    } else {
      std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    client_socket = accept(sockIn, (struct sockaddr *) &address,
                           (socklen_t *) &address);

    cout << client_socket << endl;

    if (client_socket == -1) {
      std::cerr << "Error accepting client" << std::endl;
      exit(1);
    }

    close(sockIn); //closing the listening socket
    while (true) { //need to change it to other condition
      client_handler->handleClient(new SocketInputStream(client_socket),
                                   new SocketOutputStream(client_socket));
      //  this->stop();
    }

    struct timeval tv;
    tv.tv_sec = 120;
    setsockopt(sockIn, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
  }

  int open(int port, ClientHandler *c) {
    thread ServerThread(&MySerialServer::runExucteMethosAsThread, this, port, c);
    ServerThread.detach();
    while (this->isStop == 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 1;
  }

  void stop() {
    this->isStop = 1;
  }
};

#endif //EX4__MYSERIALSERVER_H_