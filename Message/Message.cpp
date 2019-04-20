#include <iostream>
#include <string>
#include <stdio.h>

#include "Header.h"

Message::Message(std::string content , int id): Header(content.length() , message , id){
  this->content=content;
}

Message::Message(char* message){
  memcpy(this->content , message+20, size);
}

std::string Message::getMessage(){
  return this->content;
}
