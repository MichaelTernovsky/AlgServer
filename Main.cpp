#include "StringReverser.h"
#include "MyClientHandler.h"
#include "Server.h"
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "OA.h"
#include "DFS.h"
#include "BFS.h"
#include "BestFS.h"
using namespace server_side;
using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[1]);
  int capacity = 5;
  CacheManager<string, string> *ch = new FileCacheManager<string, string>(capacity);

  Searcher<int, string> *s = new BestFS<int, string>();
  Solver<string, string> *mySolver = new OA<string, string, int>(s);
  ClientHandler *clientHand = new MyClientHandler<string, string>(mySolver, ch);

  MySerialServer *mySerial = new MySerialServer();
  mySerial->open(port, clientHand);
  mySerial->stop();

  return 0;
}