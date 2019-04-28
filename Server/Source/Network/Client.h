using namespace std;
#include "NetLibs.h"
#include "ClientStatus.h"
#ifndef CLIENT_H
#define CLIENT_H

class Client{
  int socketNumber;
  char* clientBuffer;
  ClientStatus status;
  string login;

public:
  Client(int socketNumber);
  ~Client();

  int operator*(int);
  int operator==(int toCheck);

  int sendMessage(char* buffer, int bufferSize);
  int receiveMessage(int bytes);

  void setNewBuffer(int bufferSize);
  void clearBuffer();
  void setLogin(string login);

  char* getClientBuffer();
  int getSocketNumber();

};

#endif
