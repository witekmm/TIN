#include <pthread.h>
#include <vector>

#include "../../Messages/Message.pb.h"
#include "ClientSessionPipe.h"

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

void ClientSessionPipe::readBytes() {
    //TODO: read bytes
    //TODO: when full message is received deserialize it and push to writeMessagesBuffer
}