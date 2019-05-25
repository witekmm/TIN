#ifndef CLIENT_SESSION_PIPES_H
#define CLIENT_SESSION_PIPES_H

#include <pthread.h>
#include <vector>
#include <string>
#include <tuple>

#include "../../Messages/Message.pb.h"

#include "ClientSessionPipe.h"
#include "Client.h"

using namespace std;

class ClientSessionPipes {
    vector<pair<Client, ClientSessionPipe>> clientSessionPipes;

    pthread_mutex_t clientSessionPipesMutex;

    pthread_cond_t writeMessagesBufferNotEmpty;
    unsigned int writeMessagesCounter;

    vector<string> writeBytesBuffer;
    pthread_cond_t writeBytesBufferNotEmpty;

    bool isWriteMessagesBufferEmpty();
    Message::ClientMessage getWriteMessageBufferMessage();

    bool isWriteBytesBufferEmpty();

public:
    void readMessage(Message::ClientMessage);//for Logic, push new Message to send pipe
    Message::ClientMessage writeMessage();//for Logic, get Message and handle it

    void readBytes(int socketNumber);//for Network, read bytes from socket
    void writeBytes(); //for Network, send bytes

    void createClientSession(int socketNumber);
    void deleteClientSession(int socketNumber);

}

#endif