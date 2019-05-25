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

public:
    int getSocketNumber();

    bool isWriteMessagesBufferEmpty();
    Message::ClientMessage getWriteMessageBufferMessage();

    void readBytes();

    size_t getWriteMessagesCount();
}

#endif