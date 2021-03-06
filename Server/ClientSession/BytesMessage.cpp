#include <string>
#include <cstring>

#include "../Network/NetLibs.h"
#include "BytesMessage.h"

using namespace std;

BytesMessage::BytesMessage(long id, string bytesBuff) {
    localId = id;
    bytesBuffer = bytesBuff;

    sizeSent = false;
    numberOfBytesToSend = MESSAGE_SIZE_BYTES_NUMBER;
}

long BytesMessage::getLocalId() {
    return localId;
}

string BytesMessage::getLogin() {
    return login;
}

int BytesMessage::getBufferSize() {
    return bytesBuffer.length();
}

int BytesMessage::sendSize(int socketNumber) {
    char *tmp = new char[MESSAGE_SIZE_BYTES_NUMBER];
    int bufferSize = getBufferSize();

    memcpy(tmp , (char*)&bufferSize , MESSAGE_SIZE_BYTES_NUMBER);

    if(numberOfBytesToSend < MESSAGE_SIZE_BYTES_NUMBER) {
        //Buffer size wasn't send fully. Cut and send lacking bytes.
        int sentSizeBytesNumber =
            MESSAGE_SIZE_BYTES_NUMBER - numberOfBytesToSend;

        strncpy(tmp, tmp + sentSizeBytesNumber, numberOfBytesToSend);
    }

    int bytesSent = send(socketNumber, tmp,
        numberOfBytesToSend, MSG_DONTWAIT);

    if(bytesSent == -1) {
        //Error while sending buffer size
        delete [] tmp;
        return -1;
    }

    numberOfBytesToSend -= bytesSent;

    if(numberOfBytesToSend == 0) {
        //Buffer size fully send
        sizeSent = true;
        numberOfBytesToSend = getBufferSize();
        puts("Size sent");

        delete [] tmp;
        return 0;
    } else {
        delete [] tmp;
        return 0;
    }
}

int BytesMessage::sendBuffer(int socketNumber) {
    const char* tmp = bytesBuffer.c_str();

    int bytesSent = send(socketNumber, tmp,
        numberOfBytesToSend, MSG_DONTWAIT);

    if(bytesSent == -1) {
        //Error while sending buffer
        return -1;
    }

    numberOfBytesToSend -= bytesSent;

    if(numberOfBytesToSend == 0) {
        //Buffer fully sent
        puts("MESSAGE SENT");
        return 1;
    } else {
        //Buffer partially send
        bytesBuffer.erase(0, bytesSent);
        return 0;
    }
}



int BytesMessage::writeBytes(int socketNumber) {
    int result;
    puts("SENDING");
    if(!sizeSent) {
        result = sendSize(socketNumber);
    } else {
        result = sendBuffer(socketNumber);
    }

    return result;
}
