#ifndef LOGIC_PIPE_H
#define LOGIC_PIPE_H

#include "../../Messages/Message.pb.h"

#include <pthread.h>

class LogicPipe{
  //buffer for message to handle
  Message::ClientMessage inputMessage;
  //buffer for message to send
  Message::ClientMessage outputMessage;
  pthread_mutex_t mutex;
  bool isInputMessageSet;
  pthread_cond_t inputCond;
  bool isOutputMessageSet;
  pthread_cond_t outputCond;
public:
  LogicPipe();

  void setInputMessage(Message::ClientMessage& message);
  Message::ClientMessage getInputMessage();
  void clearInputMessage();

  void setOutputMessage(Message::ClientMessage& message);
  Message::ClientMessage getOutputMessage();
  void clearOutputMessage();
};

#endif
