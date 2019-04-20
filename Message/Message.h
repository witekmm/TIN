#include <iostream>
#include <string>

#IFNDEF MESSAGE_H
#DEFINE MESSAGE_H
#include "Header.h"

class Message: public Header{
  std::string content;
public:
  Message(std::string content , int id): Header(content.length() , message , id);

  std::string getMessage();
}
#ENDIF
