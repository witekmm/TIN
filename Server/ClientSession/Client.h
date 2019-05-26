#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

class Client {
    static unsigned int localClientCounter;

    unsigned int localId;
    string login;

public:
    Client();

    void setLogin(string login);
    string getLogin();

    unsigned int getLocalId();

    bool isLogged();
};

#endif