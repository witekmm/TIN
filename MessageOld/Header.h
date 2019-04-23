#include <iostream>


#IFNDEF HEADER_H
#DEFINE HEADER_H
#include <cstdint>
#include <stdio.h>
#include "MessageTypeEnum.h"

class Header{
  //From who
  int32_t start;
  //To who
  int32_t destination;
  //Message type
  const MessageType type;
  //Number of characters in message
  const int32_t size;
  //Id of the message
  const int32_t id;

public:
  Header(int32_t size , int32_t id);
  Header(char* header);
  //SETS
  void setStart(int start);
  void setDestination(int destination);
  //Gets
  int getSize();
  int getStart();
  int getDestination();
  MessageType getType();
  int getId();
  //Convert
  char* convertHeaderToChar();
}

#ENDIF
