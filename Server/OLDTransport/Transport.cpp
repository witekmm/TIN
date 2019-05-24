#include "Transport.h"
#include "../Network/Network.h"
#include "../Logic/HandleMessage.h"

int Transport::serializeAndSend(Message::ClientMessage message, string clientLogin)
{
  string toSend;
  message.SerializeToString(&toSend);
  int bytesToSend = toSend.length();
  if(this->network.setMessage(toSend,bytesToSend,clientLogin) == -1) 
    return -1;
  return 0;
}

int Transport::serializeAndSend(Message::ClientMessage message, int socketNumber)
{
  string toSend;
  message.SerializeToString(&toSend);
  int bytesToSend = toSend.length();
  if(this->network.setMessage(toSend,bytesToSend,socketNumber) == -1) 
    return -1;
  return 0;
}

void Transport::receiveAndParse(string& toParse, string login, int socketNumber)
{
  Message::ClientMessage msg;
  msg.ParseFromString(toParse);
  handleMessage.checkReceivedMessage(msg,login,socketNumber);
}

Network& Transport::getNetwork(){
  return this->network;
}

HandleMessage& Transport::getHandleMessage(){
  return this->handleMessage;
}
