//
// Created by ofir on 09/01/2020.
//

#ifndef EX4__SERVER_H_
#define EX4__SERVER_H_
#include <iostream>
using namespace std;
#include <string>
namespace server_side {

// Interfaces
class InputStream {
 public:
  virtual string readFromStream() = 0;
};

class OutPutStream {
 public:
  virtual bool writeToStream(string str) = 0;
};

class ClientHandler {
 public:
  virtual void handleClient(InputStream *input_stream, OutPutStream *out_put_stream) {};
};

class Server {
 public:
  virtual int open(int port, ClientHandler *c) = 0;
  virtual void stop() = 0;
};

}
#endif //EX4__SERVER_H_