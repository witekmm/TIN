#ifndef NETWORK_PIPE_H
#define NETWORK_PIPE_H

#include <pthread.h>

class NetworkPipe{
  //buffer for message to handle
  string inputMessage;
  //buffer for message to send
  string outputMessage;

  pthread_mutex_t mutex;
  bool isInputMessageSet;
  pthread_cond_t inputCond;
  bool isOutputMessageSet;
  pthread_cond_t outputCond;
public:
  LogicPipe();

  void setInputMessage(string message);
  string getInputMessage();
  void clearInputMessage();

  void setOutputBuffer(string message);
  string getOutputMessage();
  void clearOutputMessage();
};

#endif
