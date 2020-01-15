#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "Server.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
using namespace server_side;
using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[1]);
  int capacity = 5;

  CacheManager<string, string> *ch = new FileCacheManager<string, string>(capacity);
  Solver<string, string> *mySolver = new StringReverser();

  ClientHandler *clientHand = new MyTestClientHandler<string, string>(mySolver, ch);

  MySerialServer *mySerialServ = new MySerialServer();
  mySerialServ->open(port, clientHand);
//  mySerialServ->stop();

  return 0;
}