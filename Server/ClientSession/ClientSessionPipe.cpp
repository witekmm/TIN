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
        }

        delete [] tmp;
        return 0;
    } else {
        delete [] tmp;
        return -1;
    }
}

int ClientSessionPipe::readBytes() {
    if(!bytesMessageSizeRead) {
        int result = readBytesSize();
        return result;
    } else {
        
    }



    //TODO: read bytes
    //TODO: when full message is received deserialize it and push to writeMessagesBuffer

    //return:
    //  1: full message is read
    //  0: part of message is read
    //  -1: error while reading
}