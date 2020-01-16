#include "StringReverser.h"
#include "MyClientHandler.h"
#include "Server.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "OA.h"
#include "BFS.h"
using namespace server_side;
using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[1]);
  int capacity = 5;
  CacheManager<string, string> *ch = new FileCacheManager<string, string>(capacity);

  Searcher<string> *s = new BFS<string>();
  Solver<string, string> *mySolver = new OA<string, string, string>(s);

  ClientHandler *clientHand = new MyClientHandler<string, string>(mySolver, ch);

  MySerialServer *mySerialServ = new MySerialServer();
  mySerialServ->open(port, clientHand);

  return 0;
}