//
// Created by ofir on 12/01/2020.
//

#ifndef EX4__SOCKSTREAMS_H_
#define EX4__SOCKSTREAMS_H_
#include "AlgServer.h"
#include <string.h>
#include "sys/socket.h"
#include <unistd.h>

string SocketInputStream::readFromStream() {
  cout << "IM IN INPUT STREAM1" << endl;

  //reading from client
  char buffer[1024] = {0};
  int valread = read(this->socket, buffer, 1024);
  cout << valread << endl;

  if (valread) {
    throw "could not get the message";
  }

  //writing back to client
  char *hello = "Hello, I can hear you! \n";
  send(this->socket , hello , strlen(hello) , 0 );
  std::cout<<"Hello message sent\n"<<std::endl;

  std::cout << buffer << std::endl;

  cout << "IM IN INPUT STREAM2" << endl;
  return buffer;
}

bool SocketOutputStream::writeToStream(string str) {

  cout << "IM IN OUTPUT STREAM" << endl;

  int isSend = 0;
  const char *msg = str.c_str();
  isSend = send(this->socket, msg, strlen(msg),0);
  if (isSend < 0) {
    cout << "Error writing a massage! " << endl;
    return false;
  }
  return true;
}

#endif //EX4__SOCKSTREAMS_H_