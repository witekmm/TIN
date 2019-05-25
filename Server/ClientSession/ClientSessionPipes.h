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

    pthread_cond_t writeBytesBufferNotEmpty;
    unsigned int writeBytesCounter;


    bool isWriteMessagesBufferEmpty();
    Message::ClientMessage getWriteMessageBufferMessage();

    bool isWriteBytesBufferEmpty();
    string getWriteBytesBufferMessage();

public:
    Message::ClientMessage writeMessage();//for Logic, get Message and handle it

    void readBytes(int socketNumber);//for Network, read bytes from socket

    string writeBytes(); //for Network, bytes to send

    void createClientSession(int socketNumber);
    void deleteClientSession(int socketNumber);

}

#endif