#include "MessageHandler.h"
#include "../../Messages/Message.pb.h"

int MessageHandler::HandleMessage(Message::ClientMessage message, int clientId){
  if(!message.messagetype()){
    return 1;
  }
  if(message.messagetype() == Message::ClientMessage::GROUP){
    return HandleGroupType(message, clientId);
  }
  else if(message.messagetype() == Message::ClientMessage::AUTHORIZATION){
    //Sprawdzam czy zalogowany
    return HandleAuthorizationType(message, clientId);
  }
  else if(message.messagetype() == Message::ClientMessage::REPLY){
    //Sprawdzam czy zalogowany
    return HandleAuthorizationType(message, clientId);
  }
  else {
    return 1;
  }
}


int MessageHandler::HandleAuthorizationType(Message::ClientMessage message, int clientId){
  if(!message.authorizationtype()){
    return 2;
  }
  if(message.login().empty() || message.password().empty()){
    return 3;
  }
  if(message.authorizationtype() == Message::ClientMessage::LOG_IN){
    //return jakas funkcja do logowania

  }
  else if(message.authorizationtype() == Message::ClientMessage::REGISTER){
    //jakas funkcja do registerowania
    return 0;
  }
}


int MessageHandler::HandleGroupType(Message::ClientMessage message){
  if(!message.groupactiontype()){
    return 2;
  }
  std::string toCheck;
  if(message.groupactiontype() == Message::ClientMessage::MESSAGE){
    if(message.messagecontent().empty() || message.groupname().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::CREATE){
    if(message.groupname().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DELETE){
    if(message.groupname().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::REQUEST){
    if(message.groupname().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::ACCEPT){
    if(message.groupname().empty() || message.username().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DECLINE){
    if(message.groupname().empty() || message.username().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::LEAVE){
    if(message.groupname().empty()){
      return 3;
    }
    //pobierz login uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
}
