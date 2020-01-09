#include "ClientHandler.h"
namespace server_side {
// Interface
class Server {
 public:
  virtual int open(int port, ClientHandler c) = 0;
  virtual void stop() = 0;
};

// The class
class MySerialServer : public Server {
// to be continue
};
}

int main() {
  return 0;
}