#include <string>

#include "Client.h"

using namespace std;

void Client::setLogin(string log) {
    login = log;
}

string Client::getLogin() {
    return login;
}

bool Client::isLogged() {
    return !login.empty();
}