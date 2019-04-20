#include <iostream>
#include <cstdint>

#IFNDEF HEADER_H
#DEFINE HEADER_H

#include "MessageTypeEnum.h"

class Header{
  int32_t start;
  int32_t destination;  
  MessageType type;
  int32_t size;
  int32_t id;

public:
  Header(int32_t size , MessageType type, int32_t id);
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
