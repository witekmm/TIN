using namespace std;
#ifndef TRANSPORT_H
#define TRANSPORT_H

//NUT SURE IF HERE BUT MIGHT BE
#include "../../../Messages/Message.pb.h"

class Transport{
public:
  int serializeAndSend(Message::ClientMessage message, string clientLogin);
  Message::ClientMessage receiveAndParse(int clientNumber);
};

#endif
