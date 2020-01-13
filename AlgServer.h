//
// Created by ofir on 12/01/2020.
//

#ifndef EX4__ALGSERVER_H_
#define EX4__ALGSERVER_H_

using namespace std;

#include "Server.h"
#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>

using namespace server_side;

//socket outputStream
class SocketOutputStream : public OutPutStream {
  int socket;
 public:
  SocketOutputStream(int soc) {
    this->socket = soc;
  }
  virtual bool writeToStream(string &str);
};

//socket inputStream
class SocketInputStream : public InputStream {
  int socket;
 public:
  SocketInputStream(int soc) {
    this->socket = soc;
  }
  virtual string readFromStream();
};

#endif //EX4__ALGSERVER_H_
