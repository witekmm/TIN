#include <string>

#include "Client.h"

using namespace std;

unsigned int Client::localClientCounter = 0;

Client::Client() {
    localId = ++localClientCounter;
}

void Client::setLogin(string log) {
    login = log;
}

string Client::getLogin() {
    return login;
}

bool Client::isLogged() {
    return !login.empty();
}

unsigned int Client::getLocalId() {
    return localId;
}