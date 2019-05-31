#include <pthread.h>
#include <vector>
#include <errno.h>

#include "../Network/NetLibs.h"
#include "../../Messages/Message.pb.h"

#include "ClientSessionPipe.h"

using namespace std;

ClientSessionPipe::ClientSessionPipe(int socket) {
    socketNumber = socket;
    writeMessagesBuffer.clear();
    clearReadBytesVariables();
}

void ClientSessionPipe::clearReadBytesVariables() {
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
    Message::ClientMessage message = writeMessagesBuffer.back();
    writeMessagesBuffer.pop_back();

    return message;
}

void ClientSessionPipe::addWriteMessage(Message::ClientMessage message) {
    writeMessagesBuffer.push_back(message);
}

bool  ClientSessionPipe::isRecvSuccessfull(int bytesReceived) {
    return bytesReceived > 0 && errno == 0;
}

int ClientSessionPipe::convertRecvBytesToSize(const char* recvBytes) {
    int size = (int)*recvBytes;
    return size;
}

int ClientSessionPipe::readBytesSize() {
    char *tmp = new char[numberOfBytesToRead];
    int bytesReceived = recv(this->socketNumber, tmp,
        numberOfBytesToRead, MSG_DONTWAIT);

    if(!isRecvSuccessfull(bytesReceived)) {
        //Error while receiving message size
        clearReadBytesVariables();
        delete [] tmp;

        return -1;
    }

    if(bytesReceived == MESSAGE_SIZE_BYTES_NUMBER) {
        //Message size fully read at once
        bytesMessageSizeRead = true;
        numberOfBytesToRead = convertRecvBytesToSize(tmp);

        delete [] tmp;
        return 0;
    } else if(bytesReceived > 0 && bytesReceived < MESSAGE_SIZE_BYTES_NUMBER) {
        //Message size partially read
        numberOfBytesToRead -= bytesReceived;

        string tmpString(tmp, bytesReceived);
        readBytesBuffer += tmpString;

        if(numberOfBytesToRead == 0) {
            numberOfBytesToRead = convertRecvBytesToSize(
                readBytesBuffer.c_str());

            bytesMessageSizeRead = true;
            readBytesBuffer.clear();
        }
        
        delete [] tmp;
        return 0;
    }
}

int ClientSessionPipe::readBytesMessage() {
    char *tmp = new char[numberOfBytesToRead];

    int bytesReceived = recv(this->socketNumber, tmp,
        numberOfBytesToRead, MSG_DONTWAIT);

    if(!isRecvSuccessfull(bytesReceived)) {
        //Error while receiving message
        clearReadBytesVariables();
        delete [] tmp;

        return -1;
    }

    numberOfBytesToRead -= bytesReceived;

    string tmpString(tmp, bytesReceived);
    readBytesBuffer += tmpString;

    if(numberOfBytesToRead == 0) {
        //Message fully read, parse it and add to message buffer
        Message::ClientMessage message;
        message.ParseFromString(readBytesBuffer);

        addWriteMessage(message);

        clearReadBytesVariables();
        delete [] tmp;
        return 1;
    }

    delete [] tmp;
    return 0;
}

int ClientSessionPipe::readBytes() {
    int result;

    if(!bytesMessageSizeRead) {
        result = readBytesSize();
    } else {
        result = readBytesMessage();
    }

    return result;
}
