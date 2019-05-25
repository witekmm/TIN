#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

class Client {
    string login;

public:
    void setLogin(string login);
    bool isLogged();
}

#endif