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
//  int port = atoi(argv[1]);
//  int capacity = 5;
//  CacheManager<string, string> *ch = new FileCacheManager<string, string>(capacity);
//
//  Searcher<string, string> *s = new BFS<string, string>();
//  Solver<string, string> *mySolver = new OA<string, string, string>(s);
//  ClientHandler *clientHand = new MyClientHandler<string, string>(mySolver, ch);
//
//  MySerialServer *mySerialServ = new MySerialServer();
//  mySerialServ->open(port, clientHand);

  string str = "8,2,8\n"
               "4,12,2\n"
               "12, 1, 9\n"
               "0,0\n"
               "36,36\n"
               "end";

  MatrixProblem<string> *m = new MatrixProblem<string>(str);
  cout << m->getNumRows() << endl;
  cout << m->getNumCols() << endl;

  return 0;
}