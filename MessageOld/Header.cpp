#include <iostream>

#include "Header.h"

Header::Header(int32_t size, int32_t id){
  this->size=size;
  this->id=id;
}

Header::Header(char* Header){
  memcpy( this->start ,header, 4);
  memcpy( this->destination ,header+4, 4);
  memcpy( this->type ,header+8, 4);
  memcpy( this->size ,header+12, 4);
  memcpy( this->id ,header+16, 4);
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
  char header[20];
  /*
  header[0]= reinterpret_cast<char>(this->start);
  header[4]= reinterpret_cast<char[]>this->destination;
  header[8]= reinterpret_cast<char[]>this->type;
  header[12]= reinterpret_cast<char[]>this->size;
  header[16]= reinterpret_cast<char[]>this->id;
  */
  memcpy(header, this->start , 4);
  memcpy(header+4, this->destination , 4);
  memcpy(header+8, this->type , 4);
  memcpy(header+12, this->size , 4);
  memcpy(header+16, this->id , 4);
  return header;
}
