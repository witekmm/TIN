#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "../Network/Network.h"
#include "../Logic/HandleMessage.h"
#include "../../Messages/Message.pb.h"
#include <string>

using namespace std;

class Network; 
class HandleMessage;

class Transport{
  Network& network;
  HandleMessage& handleMessage;
public:
  Transport();
  int serializeAndSend(Message::ClientMessage message, string clientLogin);
  int serializeAndSend(Message::ClientMessage message, int socketNumber);
  void receiveAndParse(string& toParse,string login,int socketNumber);
  Network& getNetwork();
  HandleMessage& getHandleMessage();
};

#endif