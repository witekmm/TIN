
using namespace std;
#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <vector>
#include "../Network/Network.h"
//NUT SURE IF HERE BUT MIGHT BE
#include "../../Messages/Message.pb.h"
#include "../Network/Network.h"
using namespace std;

class Network; 

class Network;

class Transport{
  Network& network;
public:
  int serializeAndSend(Message::ClientMessage message, string clientLogin);
  Message::ClientMessage receiveAndParse(int clientNumber);
};

#endif
