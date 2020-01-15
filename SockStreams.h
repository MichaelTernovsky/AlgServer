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
  //reading from client
  char buffer[1024] = {0};
  int valread = read(this->socket, buffer, 1024);
  return buffer;
}

bool SocketOutputStream::writeToStream(string str) {
  int isSend = 0;
  const char *msg = str.c_str();
  isSend = send(this->socket, msg, strlen(msg), 0);
  if (isSend < 0) {
    cout << "Error writing a massage! " << endl;
    return false;
  }
  return true;
}

#endif //EX4__SOCKSTREAMS_H_