#include "MessageHandler.h"
#include "../../Messages/Message.pb.h"

int MessageHandler::HandleMessage(Message::ClientMessage message, int clientId){
  if(!message.has_messagetype()){
    return 1;
  }
  if(message.messagetype() == Message::ClientMessage::GROUP){
    return HandleGroupType(message, clientId);
  }
  else if(message.messagetype() == Message::ClientMessage::AUTHORIZATION){
    //Sprawdzam czy zalogowany
    return HandleAuthorizationType(message, clientId);
  }
}


int MessageHandler::HandleAuthorizationType(Message::ClientMessage message, int clientId){
  if(!message.has_authorizationtype()){
    return 2;
  }
  if(!message.has_login() || !message.has_password()){
    return 3;
  }
  if(message.authorizationtype() == Message::ClientMessage::LOG_IN){
    //jakas funkcja do logowania
    return 0;
  }
  else if(message.authorizationtype() == Message::ClientMessage::REGISTER){
    //jakas funkcja do registerowania
    return 0;
  }
}


int MessageHandler::HandleGroupType(Message::ClientMessage message, int clientId){
  if(!message.has_groupactiontype()){
    return 2;
  }
  if(message.groupactiontype() == Message::ClientMessage::MESSAGE){
    if(!message.has_messagecontent() || !message.has_groupname()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::CREATE){
    if(!message.has_groupname()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DELETE){
    if(!message.has_groupname()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::REQUEST){
    if(!message.has_groupname()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::ACCEPT){
    if(!message.has_groupname() || !message.has_username()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DECLINE){
    if(!message.has_groupname() || !message.has_username()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::LEAVE){
    if(!message.has_groupname()){
      return 3;
    }
    //pobierz ID uytkownika z ClientSessionPipes i wstaw do funkcji
    //funkcja
    return 0;
  }
}
