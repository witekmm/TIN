#ifndef CLIENT_H
#define CLIENT_H

#include "ClientSocket.h"

class Client{
  int socketNumber;
  char* clientBuffer;

public:
  Client(int socketNumber);
  ~Client();

  int sendMessage(char* buffer, int bufferSize);
  int receiveMessage(int bytes);

  void setNewBuffer(int bufferSize);
  void clearBuffer();

  char* getClientBuffer();
  int getSocketNumber();

};

#endif
