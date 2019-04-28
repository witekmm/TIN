#include "Transport.h"
#include "../Network/Network.h"

int Transport::serializeAndSend(Message::ClientMessage message, string clientLogin){
  string toSend;
  message.SerializeToString(&toSend);
  int bytesToSend = toSend.length();
  if(this->network.sendMessage(toSend,bytesToSend,clientLogin) == -1) return -1;
  return 0;
}
