#ifndef CLIENT_SESSION_PIPES_H
#define CLIENT_SESSION_PIPES_H

#include <pthread.h>
#include <vector>
#include <string>
#include <utility>

#include "../../Messages/Message.pb.h"

#include "ClientSessionPipe.h"
#include "Client.h"

using namespace std;

class ClientSessionPipes {
    vector<pair<Client, ClientSessionPipe>> clientSessionPipes;

    pthread_mutex_t clientSessionPipesMutex;

    pthread_cond_t writeMessagesBufferNotEmpty;
    unsigned int writeMessagesCounter;
    bool isWriteMessagesBufferEmpty();

    vector<pair<string, string>> writeBytesBuffer;
    pthread_cond_t writeBytesBufferNotEmpty;
    bool isWriteBytesBufferEmpty();

    pair<Client, Message::ClientMessage> getWriteMessageBufferMessage();

    string getClientLogin(int socketNumber);

    int sendBytes(int socketNumber, string bytes);

    void deleteWriteBuffers(int socketNumber);

public:
    void readMessage(string login, Message::ClientMessage message);//for Logic, push new Message to send pipe
    pair<Client, Message::ClientMessage> writeMessage();//for Logic, get Message and handle it

    void readBytes(int socketNumber);//for Network, read bytes from socket
    void writeBytes(int socketNumber); //for Network, send bytes

    void createClientSession(int socketNumber);
    void deleteClientSession(int socketNumber);

};

#endif