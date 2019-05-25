#ifndef BYTES_MESSAGE_H
#define BYTES_MESSAGE_H

#include <string>

using namespace std;

class BytesMessage {
    string login;
    string bytesBuffer;

    bool sizeSent;
    int numberOfBytesToSend;

public:
    BytesMessage(string login, string bytesBuffer);

    string getLogin();
    int writeBytes(int socketNumber);
};

#endif