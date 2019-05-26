#include "RepliesCreator.h"

Reply::Reply(std::shared_ptr<ClientSessionPipes> clients): clients(clients) {}

void Reply::incorrectGroupTypeMessage(std::string login, std::string error){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(error);
  //wyslij
  this->clients->readMessage(login,message);
}

void Reply::incorrectAuthorizationTypeMessage(int clientsId , std::string error){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(error);
  //this->clients->readMessage(clientsId,message)
}

void Reply::correctMessage(std::string login){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  this->clients->readMessage(login,message);
}

void Reply::correctLoginMessage(std::string login, std::vector<std::string> groups){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  for(auto it = groups.begin(); it != groups.end() ; it++){
    message.add_groups( *it );
  }
  this->clients->readMessage(login,message);
}
