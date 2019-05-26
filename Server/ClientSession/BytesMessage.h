#ifndef BYTES_MESSAGE_H
#define BYTES_MESSAGE_H

#include <string>
#include <cstring>

using namespace std;

class BytesMessage {
    long localId;
    string login;

    string bytesBuffer;
    bool sizeSent;
    int numberOfBytesToSend;

public:
    BytesMessage(long localId, string bytesBuffer);

    long getLocalId();

    string getLogin();
    int getBufferSize();

    int sendSize(int socketNumber);
    int sendBuffer(int socketNumber);
    int writeBytes(int socketNumber);
};

#endif