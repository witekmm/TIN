#include "Transport.h"
#include "../Network/Network.h"
#include "../Logic/HandleMessage.h"

int Transport::serializeAndSend(Message::ClientMessage message, string clientLogin){
  string toSend;
  message.SerializeToString(&toSend);
  int bytesToSend = toSend.length();
  if(this->network.setMessage(toSend,bytesToSend,clientLogin) == -1) return -1;
  return 0;
}

void Transport::receiveAndParse(string& toParse){
  Message::ClientMessage msg;
  msg.ParseFromString(toParse);
  //APP.messageSent(msg);
}
