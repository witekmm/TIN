#include <string>

#include "BytesMessage.h"

using namespace std;

BytesMessage::BytesMessage(string log, string bytesBuff) {
    login = log;
    bytesBuffer = bytesBuff;
}

string BytesMessage::getLogin() {
    return login;
}

int BytesMessage::writeBytes(int socketNumber) {
    //TODO: implement this function

    return 0;
}