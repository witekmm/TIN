#include <pthread.h>
#include <vector>

#include "NetLibs.h"
#include "../../Messages/Message.pb.h"

#include "ClientSessionPipe.h"

using namespace std;

ClientSessionPipe(int socket) {
    socketNumber = socket;
    numberOfBytesToRead = MESSAGE_SIZE_BYTES_NUMBER;
    bytesMessageSizeRead = false;
}

void clearReadBytesVariables() {
    numberOfBytesToRead = MESSAGE_SIZE_BYTES_NUMBER;
    bytesMessageSizeRead = false;
    readBytesBuffer.clear();
}

int ClientSessionPipe::getSocketNumber() {
    return socketNumber;
}

size_t ClientSessionPipe::getWriteMessagesCount() {
    return writeMessagesBuffer.size();
}

bool ClientSessionPipe::isWriteMessagesBufferEmpty() {
    return writeMessagesBuffer.empty(); 
}

Message::ClientMessage ClientSessionPipe::getWriteMessageBufferMessage() {
    return writeMessagesBuffer.pop_back();
}

void addWriteMessage(Message::ClientMessage message) {
    writeMessagesBuffer.push_back(message);
}

int readBytesSize() {
    char *tmp = new char[numberOfBytesToRead];

    int bytesReceived = recv(this->socketNumber, &temp, 
        numberOfBytesToRead, MSG_DONTWAIT);

    if(bytesReceived == MESSAGE_SIZE_BYTES_NUMBER) {
        bytesMessageSizeRead = true;
        numberOfBytesToRead = atoi(temp);

        delete [] tmp;
        return 0;
    } else if(bytesReceived > 0 && bytesReceived < MESSAGE_SIZE_BYTES_NUMBER) {
        numberOfBytesToRead -= bytesReceived;

        string tmpString(tmp, bytesReceived);
        readBytesBuffer += tmpString;

        if(numberOfBytesToRead == 0) {
            numberOfBytesToRead = atoi(readBytesBuffer.c_str());
            bytesMessageSizeRead = true;

            readBytesBuffer.clear();
        }

        delete [] tmp;
        return 0;
    } else {
        clearReadBytesVariables();
        delete [] tmp;

        return -1;
    }
}

int readBytesMessage() {
    char *tmp = new char[numberOfBytesToRead];

    int bytesReceived = recv(this->socketNumber, &temp, 
        numberOfBytesToRead, MSG_DONTWAIT);


    if(bytesReceived > 0) {
        numberOfBytesToRead -= bytesReceived;

        string tmpString(tmp, bytesReceived);
        readBytesBuffer += tmpString;

        if(numberOfBytesToRead == 0) {
            Message::ClientMessage message;
            message.ParseFromString(readBytesBuffer);

            addWriteMessage(message);

            clearReadBytesVariables();
            delete [] tmp;
            return 1;
        }

        delete [] tmp;
        return 0;

    } else {
        clearReadBytesVariables();
        delete [] tmp;
        return -1;
    }
}

int ClientSessionPipe::readBytes() {
    int result;

    if(!bytesMessageSizeRead) {
        result = readBytesSize();
    } else {
        int result = readBytesSize();
    }

    return result;
}