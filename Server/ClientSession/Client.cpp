#include <string>

#include "Client.h"

using namespace std;

long Client::localClientCounter = 0;

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

long Client::getLocalId() {
    return localId;
}