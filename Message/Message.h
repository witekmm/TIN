#include <iostream>
#include <string>

#IFNDEF MESSAGE_H
#DEFINE MESSAGE_H
#include "Header.h"

class Message: public Header{
  std::string content;
public:
  Message(std::string content , int id, MessageType type): Header(content.length() , type , id);
  Message(char* message): Header(message);

  std::string getMessage();
  char* getSendMessage();
}
#ENDIF
