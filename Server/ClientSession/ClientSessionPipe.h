#ifndef CLIENT_SESSION_PIPE_H
#define CLIENT_SESSION_PIPE_H

#include <pthread.h>
#include <vector>

#include "../../Messages/Message.pb.h"

class ClientSessionPipe {
    int socketNumber;

    string readBytesBuffer;
    int numberOfBytesToRead;
    bool readBytesMessageSizeRead;

    vector<Message::ClientMessage> writeMessagesBuffer;

    void addWriteMessage(Message::ClientMessage);

public:
    int getSocketNumber();

    size_t getWriteMessagesCount();
    bool isWriteMessagesBufferEmpty();
    Message::ClientMessage getWriteMessageBufferMessage();

    void readBytes();
}

#endif