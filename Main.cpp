#include "StringReverser.h"
#include "MyClientHandler.h"
#include "Server.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "OA.h"
#include "DFS.h"
using namespace server_side;
using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[1]);
  int capacity = 5;
  CacheManager<string, string> *ch = new FileCacheManager<string, string>(capacity);

  Searcher<int, string> *s = new DFS<int, string>();
  Solver<string, string> *mySolver = new OA<string, string, int>(s);
  ClientHandler *clientHand = new MyClientHandler<string, string>(mySolver, ch);

  MySerialServer *mySerialServ = new MySerialServer();
  mySerialServ->open(port, clientHand);

//  string str = "8,2,8\n"
//               "4,12,2\n"
//               "12, -1, 9\n"
//               "0,0\n"
//               "2,2\n"
//               "end";
//
//  MatrixProblem<int> *m = new MatrixProblem<int>(str);
//  Searcher<int, int> *s = new DFS<int, int>();
//  s->search(m);


//  State<int> *currState = new State<int>(1, 1, 9);
//  State<int> *initState = m->getInitialState();
//  int k = m->isGoalState(currState);
//  vector<State<int> *> vc = m->getAllPossibleStates(currState);

  return 0;
}