#include <iostream>

#IFNDEF HEADER_H
#DEFINE HEADER_H

class Header{
  int destination;
  int start;
  int size;
  int id;
  MessageType type;

public:
  Header(int size , MessageType type);
  enum MessageType{
    message = 0,
    command = 1,
    login = 2,
    password = 3,
    group_create = 4,
    group_delete = 5,
    group_request = 6,
    group_accept = 7,
    group_decline = 8,
  };
  //SETS
  void setStart(int start);
  void setDestination(int destination);
  //Gets
  int getSize();
  int getStart();
  int getDestination();
  MessageType getType();
  int getId();

}

#ENDIF
