#include <cstdint>
#include <iostream>
#include "Header.h"

Header::Header(int32_t size,MessageType type, int32_t id){
  this->size=size;
  this->id=id;
  this->type=type;
}
//GETS
void Header::setStart(int start){ this->start=start; }
void Header::setDestination(int destination){ this->destination=destination; }
//GETS
int Header::getSize(){return this->size;}
int Header::getStart(){return this->start;}
int Header::getDestination(){return this->destination;}
MessageType Header::getType(){return this->type;}
int Header::getId(){return this->id;}
//
char* Header::convertHeaderToChar(){
  int char[20];
  char[0]=(char)this->start;
  char[4]=(char)this->destination;
  char[8]=(char)this->type;
  char[12]=(char)this->size;
  char[16]=(char)this->id;
  return char;
}
