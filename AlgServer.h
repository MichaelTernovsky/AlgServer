//
// Created by ofir on 12/01/2020.
//

#ifndef EX4__ALGSERVER_H_
#define EX4__ALGSERVER_H_

#include "Server.h"
#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;
using namespace server_side;

//socket inputStream
class SocketInputStream : public InputStream {
  int socket;
 public:
  SocketInputStream(int soc) {
    this->socket = soc;
  }
  virtual string readFromStream();
};

//socket outputStream
class SocketOutputStream : public OutPutStream {
  int socket;
 public:
  SocketOutputStream(int soc) {
    this->socket = soc;
  }
  virtual bool writeToStream(string str);
};

#endif //EX4__ALGSERVER_H_