////
//// Created by michael on 09/01/2020.
////
//#ifndef EX4__MYPARALLELSERVER_H_
//#define EX4__MYPARALLELSERVER_H_
//#include "Server.h"
//#include <thread>
//#include <netinet/in.h>
//#include <unistd.h>
//#include "AlgServer.h"
//#include <queue>
//#include <mutex>
//
//using namespace server_side;
//extern int client_socket;
//mutex mutex_lock;
//
//class MyParallelServer : Server {
// private:
//  int isStop = 0;
//  queue<int> clientQueue;
//
// public:
//  void runExucteMethosAsThread(int portNum, ClientHandler *client_handler) {
//
//    //create socket
//    int sockIn = socket(AF_INET, SOCK_STREAM, 0); //socket for input
//    if (sockIn == -1) {
//      //error
//      std::cerr << "Could not create a socket" << std::endl;
//      exit(1);
//    }
//
//    //bind socket to IP address
//    // we first need to create the sockaddr obj
//    sockaddr_in address; //in means IP4
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
//    address.sin_port = htons(portNum);
//
//    //we need to convert our number to a number that the network understands
//    //the actual bind command
//    if (bind(sockIn, (struct sockaddr *) &address, sizeof(address)) == -1) {
//      std::cerr << "Could not bind the socket to an IP" << std::endl;
//      exit(1);
//    }
//
//    //making socket listen to the port
//    if (listen(sockIn, 5) == -1) {
//      //can also set to SOMAXCON (max connections)
//      std::cerr << "Error during listening command" << std::endl;
//      exit(1);
//    } else {
//      std::cout << "Server is now listening ..." << std::endl;
//    }
//    int timeOutCheck = 0;
//    while (true) {
//
//      struct timeval tv;
//      tv.tv_sec = 120;
//      setsockopt(sockIn, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
//
//      client_socket = accept(sockIn, (struct sockaddr *) &address,
//                             (socklen_t *) &address);
//
//      if (client_socket == -1) {
//        std::cerr << "Time out - error accepting client" << std::endl;
//        exit(0);
//      }
//
//      // adding the request to the queue
//      this->clientQueue.push(client_socket);
//    }
//  }
//
//  // handling request
//  void handleRequest(queue<int> q, ClientHandler *client_handler) {
//    // locking the thread
//    mutex_lock.lock();
//    if (!q.empty()) {
//      int clientSocket = q.front();
//      mutex_lock.unlock(); // unlocking the thread
//      q.pop();
//
//      client_handler->handleClient(new SocketInputStream(clientSocket),
//                                   new SocketOutputStream(clientSocket));
//    }
//  }
//
//  int open(int port, ClientHandler *c) {
//    // accepting clients loop
//    thread ServerThread(&MyParallelServer::runExucteMethosAsThread, this, port, c);
//
//    while (!isStop) {
//      // clients threads
//      thread ClientsThread1(&MyParallelServer::handleRequest, this, clientQueue, c);
//      thread ClientsThread2(&MyParallelServer::handleRequest, this, clientQueue, c);
//      thread ClientsThread3(&MyParallelServer::handleRequest, this, clientQueue, c);
//      thread ClientsThread4(&MyParallelServer::handleRequest, this, clientQueue, c);
//      thread ClientsThread5(&MyParallelServer::handleRequest, this, clientQueue, c);
//    }
//
//    return 1;
//  }
//
//  void stop() {
//    this->isStop = 1;
//    close(client_socket); //closing the listening socket
//  }
//};
//
//#endif //EX4__MYSERIALSERVER_H_