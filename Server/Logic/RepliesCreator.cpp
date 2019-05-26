#include "RepliesCreator.h"

Reply::Reply(std::shared_ptr<ClientSessionPipes> clients): clients(clients) {}

void Reply::incorrectGroupTypeMessage(int clientId, std::string error){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(error);
  //wyslij
  this->clients->readMessage(clientId,message);
}

void Reply::incorrectAuthorizationTypeMessage(int clientId , std::string error){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(error);
  this->clients->readMessage(clientId,message);
}

void Reply::correctMessage(int clientId){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  this->clients->readMessage(clientId,message);
}

void Reply::correctLoginMessage(int clientId, std::vector<std::string> groups){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  for(auto it = groups.begin(); it != groups.end() ; it++){
    message.add_groups( *it );
  }
  this->clients->readMessage(clientId,message);
}

void Reply::createAndSetMessage(std::string sender, std::string content,int type, int clientId){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  switch (type){
    case 1:
      message.set_groupactiontype(Message::ClientMessage::MESSAGE);
      break;
    case 2:
      message.set_groupactiontype(Message::ClientMessage::REQUEST);
      break;
    case 3:
      message.set_groupactiontype(Message::ClientMessage::ACCEPT);
      break;
    case 4:
      message.set_groupactiontype(Message::ClientMessage::DECLINE);
      break;
  }
  message.set_username(sender);
  message.set_messagecontent(content);
  this->clients->readMessage(clientId,message);
}
