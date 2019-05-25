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
        if(!it->second.isWriteMessagesBufferEmpty()) {
            return it->second.getWriteMessageBufferMessage();
        }
    }
}

bool ClientSessionPipes::isWriteBytesBufferEmpty() {
    return writeBytesCounter == 0;
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

void readMessage(Message::ClientMessage message) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    string bytes;
    message.SerializeToString(&bytes);

    writeBytesBuffer.push_back(bytes);

    if(writeBytesBuffer.size() == 1) {
        pthread_cond_signal(&writeBytesBufferNotEmpty); 
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

void ClientSessionPipes::readBytes(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    vector<pair<Client, ClientSessionPipe>>::iterator it;
    int result;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->second.getSocketNumber() == socketNumber) {
            result = it->second.readBytes();
            break;
        }
    }

    if(result == 1) {
        //Message is successfully read
        pthread_cond_signal(&writeMessagesBufferNotEmpty);
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

void ClientSessionPipes::writeBytes() {
    pthread_mutex_lock(&clientSessionPipesMutex);
    if(isWriteBytesBufferEmpty()) {
        pthread_cond_wait(&writeBytesBufferNotEmpty, 
            &clientSessionPipesMutex);
    }

    string message = writeBytesBuffer[0];

    //TODO: send bytes
    //TODO: delete message from writeBytesBuffer only when all bytes sent

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

void ClientSessionPipes::createClientSession(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    //TODO: create Client and ClientSessionPipe associated with socketNumber
    //TODO: add pair <Client, ClientSessionPipe> to clientSessionPipes vector

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

void  ClientSessionPipes::deleteClientSession(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->second.getSocketNumber() == socketNumber) {

            writeMessagesCounter -= it->second.getWriteMessagesCount();
            writeBytesCounter -= it->second.getWriteBytesCount();

            clientSessionPipes.erase(it);
        }
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}