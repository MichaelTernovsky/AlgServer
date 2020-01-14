#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "Server.h"
#include "MySerialServer.h"
using namespace server_side;
using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[0]);
  int capacity = 5;

  CacheManager<string, string> ch = CacheManager<string, string>(capacity);
  Solver<string, string> mySolver = StringReverser();

  ClientHandler clientHand = MyTestClientHandler<string, string>(mySolver, ch);

  MySerialServer *mySerialServ = new MySerialServer();
  mySerialServ->open(port, clientHand);
  mySerialServ->stop();

  return 0;
}