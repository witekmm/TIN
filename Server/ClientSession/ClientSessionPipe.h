#ifndef CLIENT_SESSION_PIPE_H
#define CLIENT_SESSION_PIPE_H

#define MESSAGE_SIZE_BYTES_NUMBER 4

#include <pthread.h>
#include <vector>
#include <cstring>

#include "../Network/NetLibs.h"
#include "../../Messages/Message.pb.h"

using namespace std;

class ClientSessionPipe {
    int socketNumber;

    string readBytesBuffer;
    int numberOfBytesToRead;
    bool bytesMessageSizeRead;

    vector<Message::ClientMessage> writeMessagesBuffer;

    void clearReadBytesVariables();
    void addWriteMessage(Message::ClientMessage);

    int readBytesSize();
    int readBytesMessage();

    bool  isRecvSuccessfull(int bytesReceived);
    int convertRecvBytesToSize(const char* recvBytes);

public:
    ClientSessionPipe(int socketNumber);

    int getSocketNumber();

    size_t getWriteMessagesCount();
    bool isWriteMessagesBufferEmpty();
    Message::ClientMessage getWriteMessageBufferMessage();

    int readBytes();
};

#endif
