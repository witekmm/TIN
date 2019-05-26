#include <string>
#include <cstring>

#include "BytesMessage.h"

using namespace std;

BytesMessage::BytesMessage(string log, string bytesBuff) {
    login = log;
    bytesBuffer = bytesBuff;

    sizeSent = false;
    numberOfBytesToSend = MESSAGE_SIZE_BYTES_NUMBER;
    
}

string BytesMessage::getLogin() {
    return login;
}

int BytesMessage::getBufferSize() {
    //TODO: implement this function
}

int BytesMessage::sendSize(int socketNumber) {
    char *tmp = new char[MESSAGE_SIZE_BYTES_NUMBER];
    int bufferSize = getBufferSize();

    memcpy(tmp , (char*)&bufferSize , MESSAGE_SIZE_BYTES_NUMBER);

    if(numberOfBytesToSend < MESSAGE_SIZE_BYTES_NUMBER) {
        int sentSizeBytesNumber = 
            MESSAGE_SIZE_BYTES_NUMBER - numberOfBytesToSend;

        strncpy(tmp, tmp + sentSizeBytesNumber, numberOfBytesToSend);
    }

    int bytesSent = send(socketNumber, tmp, 
        numberOfBytesToSend, MSG_DONTWAIT);

    if(bytesSent == -1) {
        delete [] tmp;
        return -1;
    }

    numberOfBytesToSend -= bytesSent;

    if(numberOfBytesToSend == 0) {
        sizeSent = true;
        numberOfBytesToSend = getBufferSize();

        delete [] tmp;
        return 1;
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
        return -1;
    }

    numberOfBytesToSend -= bytesSent;

    if(numberOfBytesToSend == 0) {
        return 1;
    } else {
        bytesBuffer.erase(0, bytesSent);
        return 0;
    }
}



int BytesMessage::writeBytes(int socketNumber) {
    int result;

    if(!sizeSent) {
        result = sendSize(socketNumber);
    } else {
        result = sendBuffer(socketNumber);
    }

    return result;
}