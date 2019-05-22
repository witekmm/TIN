#include "LogicPipe.h"

//dont know what to create
LogicPipe::LogicPipe(): isInputMessageSet(false) , isOutputMessageSet(false) {}

void LogicPipe::setInputMessage(Message::ClientMessage& message){
  pthread_mutex_lock(&this->mutex);
  if(this->isInputMessageSet==true)
    pthread_cond_wait(&this->inputCond, &this->mutex);
  this->inputMessage=Message::ClientMessage();
  this->inputMessage.CopyFrom(message);
  this->isInputMessageSet=true;
  pthread_mutex_unlock(&this->mutex);
}

void LogicPipe::setOutputMessage(Message::ClientMessage& message){
  pthread_mutex_lock(&this->mutex);
  if(this->isOutputMessageSet==true)
     pthread_cond_wait(&this->outputCond, &this->mutex);
  this->outputMessage=Message::ClientMessage();
  this->outputMessage.CopyFrom(message);
  this->isOutputMessageSet=true;
  pthread_mutex_unlock(&this->mutex);
}

Message::ClientMessage LogicPipe::getOutputMessage(){
  return this->outputMessage;
}

Message::ClientMessage LogicPipe::getInputMessage(){
  return this->inputMessage;
}

void LogicPipe::clearInputMessage(){
  pthread_mutex_lock(&this->mutex);
  this->isInputMessageSet=false;
  this->inputMessage=nullptr;
  pthread_cond_signal(&this->inputCond);
  pthread_mutex_unlock(&this->mutex);
}

void LogicPipe::clearOutputMessage(){
  pthread_mutex_lock(&this->mutex);
  this->isOutputMessageSet=false;
  this->outputMessage=nullptr;
  pthread_cond_signal(&this->outputCond);
  pthread_mutex_unlock(&this->mutex);
}
