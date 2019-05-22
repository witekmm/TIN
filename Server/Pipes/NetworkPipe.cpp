#include "NetworkPipe.h"

NetworkPipe::NetworkPipe(): isInputMessageSet(false) , isOutputMessageSet(false){
  this->inputMessage.clear();
  this->outputMessage.clear();
}

void NetworkPipe::setInputMessage(string message){
  pthread_mutex_lock(&this->mutex);
  if(this->isInputMessageSet==true)
    pthread_cond_wait(&this->inputCond, &this->mutex);
  this->inputMessage=message;
  this->isInputMessageSet=true;
  pthread_mutex_unlock(&this->mutex);
}

void NetworkPipe::setOutputMessage(Message::ClientMessage& message){
  pthread_mutex_lock(&this->mutex);
  if(this->isOutputMessageSet==true)
     pthread_cond_wait(&this->outputCond, &this->mutex);
  this->outputMessage=message;
  this->isOutputMessageSet=true;
  pthread_mutex_unlock(&this->mutex);
}

string NetworkPipe::getOutputMessage(){
  return this->outputMessage;
}

string NetworkPipe::getInputMessage(){
  return this->inputMessage;
}

void NetworkPipe::clearInputMessage(){
  pthread_mutex_lock(&this->mutex);
  this->isInputMessageSet=false;
  this->inputMessage.clear();
  pthread_cond_signal(&this->inputCond);
  pthread_mutex_unlock(&this->mutex);
}

void LogicPipe::clearOutputMessage(){
  pthread_mutex_lock(&this->mutex);
  this->isOutputMessageSet=false;
  this->outputMessage.clear();
  pthread_cond_signal(&this->outputCond);
  pthread_mutex_unlock(&this->mutex);
}
