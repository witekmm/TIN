
using namespace std;
#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <string>
#include "../Network/Network.h"
#include "../Logic/HandleMessage.h"
//NUT SURE IF HERE BUT MIGHT BE
#include "../../Messages/Message.pb.h"

class Network;

class HandleMessage;

class Transport{
  Network& network;
  HandleMessage& handleMessage;
public:
  int serializeAndSend(Message::ClientMessage message, string clientLogin);
  void receiveAndParse(string& toParse,string login);
};

#endif
