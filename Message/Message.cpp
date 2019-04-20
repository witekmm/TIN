#include <iostream>
#include <string>

#include "Header.h"

Message::Message(std::string content , int id): Header(content.length() , message , id){
  this->content=content;
}

std::string Message::getMessage(){
  return this->content;
}
