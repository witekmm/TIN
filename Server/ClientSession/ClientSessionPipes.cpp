#include <pthread.h>
#include <vector>
#include <string>
#include <tuple>

#include "../../Messages/Message.pb.h"

#include "ClientSessionPipes.h"
#include "ClientSessionPipe.h"
#include "Client.h"

using namespace std;

bool ClientSessionPipes::isWriteMessagesBufferEmpty() {
    return writeMessagesCounter == 0;
}


Message::ClientMessage ClientSessionPipes::getWriteMessageBufferMessage() {
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(!it->isWriteMessagesBufferEmpty()) {
            return it->getWriteMessageBufferMessage();
        }
    }
}


bool ClientSessionPipes::isWriteBytesBufferEmpty() {
    return writeBytesCounter == 0;
}

string ClientSessionPipes::getWriteBytesBufferMessage() {
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(!it->isWriteBytesBufferEmpty()) {
            return it->getWriteBytesBufferMessage();
        }
    }
}

Message::ClientMessage  ClientSessionPipes::writeMessage() {
    pthread_mutex_lock(&clientSessionPipesMutex);
    if(isWriteMessagesBufferEmpty()) {
        pthread_cond_wait(&writeMessagesBufferNotEmpty, 
            &clientSessionPipesMutex);
    }

    Message::ClientMessage message = 
        getWriteMessageBufferMessage();

    --writeMessagesCounter;
    pthread_mutex_unlock(&clientSessionPipesMutex);

    return message;
}

void  ClientSessionPipes::readBytes(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->getSocketNumber() == socketNumber) {
            return it->readBytes();
        }
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

string  ClientSessionPipes::writeBytes() {
    pthread_mutex_lock(&clientSessionPipesMutex);
    if(isWriteBytesBufferEmpty()) {
        pthread_cond_wait(&writeBytesBufferNotEmpty, 
            &clientSessionPipesMutex);
    }

    string bytes = getWriteBytesBufferMessage();

    --writeBytesCounter;
    pthread_mutex_unlock(&clientSessionPipesMutex);

    return bytes;
}

void  ClientSessionPipes::createClientSession(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    //TODO: create Client and ClientSessionPipe associated with socketNumber
    //TODO: add pair <Client, ClientSessionPipe> to clientSessionPipes vector

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

void  ClientSessionPipes::deleteClientSession(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->getSocketNumber() == socketNumber) {

            writeMessagesCounter -= it->getWriteMessagesCount();
            writeBytesCounter -= it->getWriteBytesCount();

            clientSessionPipes.erase(it);
        }
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}