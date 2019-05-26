#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

class Client {
    static long localClientCounter;

    //id unique in program execution context 
    long localId;
    string login;

public:
    Client();

    void setLogin(string login);
    string getLogin();

    long getLocalId();

    bool isLogged();
};

#endif