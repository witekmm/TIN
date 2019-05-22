#ifndef CLIENT_H
#define CLIENT_H

#include <string>

struct userData{
  std::string login;
};

class Client{
  std::string buffer;
  userData user;
};

#endif
