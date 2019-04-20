#include "Header.h"

Header(int size,int start,int destination,MessageType type, int id){
  this->size=size;
  this->id=id;
  this->type=type;
}

void Header::setStart(int start){ this->start=start; }
void Header::setDestination(int destination){ this->destination=destination; }

int Header::getSize(){return this->size;}
int Header::getStart(){return this->start;}
int Header::getDestination(){return this->destination;}
MessageType Header::getType(){return this->type;}
int Header::getId(){return this->id;}
