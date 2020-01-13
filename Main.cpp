#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
using namespace server_side;
using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[0]);

  int capacity = 5;

  StringReverser mySolver = StringReverser();

  ClientHandler clientHand = MyTestClientHandler<string, string>(mySolver, capacity);

  MySerialServer *mySerialServ = new MySerialServer();
  mySerialServ->open(port, clientHand);

  mySerialServ->stop();

  return 0;
}