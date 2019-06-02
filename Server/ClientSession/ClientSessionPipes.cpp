#include <pthread.h>
#include <vector>
#include <string>
#include <utility>

#include "../../Messages/Message.pb.h"

#include "ClientSessionPipes.h"
#include "ClientSessionPipe.h"
#include "Client.h"

using namespace std;

ClientSessionPipes::ClientSessionPipes(){
    clientSessionPipesMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&this->clientSessionPipesMutex, NULL);

    writeMessagesBufferNotEmpty = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&this->writeMessagesBufferNotEmpty, NULL);

    writeMessagesCounter = 0;
}

bool ClientSessionPipes::isWriteMessagesBufferEmpty() {
    return writeMessagesCounter == 0;
}


pair<Client, Message::ClientMessage> ClientSessionPipes::getWriteMessageBufferMessage() {
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(!it->second.isWriteMessagesBufferEmpty()) {
            Message::ClientMessage message = it->second.getWriteMessageBufferMessage();

            return make_pair(it->first, message);
        }
    }
}

bool ClientSessionPipes::isWriteBytesBufferEmpty() {
    return writeBytesBuffer.empty();
}

pair<Client, Message::ClientMessage> ClientSessionPipes::writeMessage() {
    pthread_mutex_lock(&clientSessionPipesMutex);

    while(isWriteMessagesBufferEmpty()) {
        struct timespec waitTime;
        clock_gettime(CLOCK_REALTIME, &waitTime);
        waitTime.tv_sec += WRITE_MESSAGE_COND_WAIT_SEC;

        pthread_cond_timedwait(&writeMessagesBufferNotEmpty,
            &clientSessionPipesMutex, &waitTime);
    }

    pair<Client, Message::ClientMessage> message =
        getWriteMessageBufferMessage();

    --writeMessagesCounter;
    pthread_mutex_unlock(&clientSessionPipesMutex);

    return message;
}

void ClientSessionPipes::readMessage(long localId, Message::ClientMessage message) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    string bytes;
    message.SerializeToString(&bytes);

    writeBytesBuffer.push_back(BytesMessage(localId, bytes));

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

int ClientSessionPipes::readBytes(int socketNumber) {
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
        ++writeMessagesCounter;
        pthread_cond_signal(&writeMessagesBufferNotEmpty);
    } else if (result == -1) {
        //Error while reading message, client disconnected
        deleteClientSessionPipe(socketNumber);
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);

    return result;
}

long ClientSessionPipes::getClientLocalId(int socketNumber) {
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->second.getSocketNumber() == socketNumber) {
            return it->first.getLocalId();
        }
    }

    return -1;
}

int ClientSessionPipes::writeBytes(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);


    long localId = getClientLocalId(socketNumber);
    if(localId < 0) return -1;
    if(isWriteBytesBufferEmpty()) {

        pthread_mutex_unlock(&clientSessionPipesMutex);
        return 0;
    }
    
    vector<BytesMessage>::iterator it;
    int result;

    for(it = writeBytesBuffer.begin(); it != writeBytesBuffer.end(); ++it) {
        if(it->getLocalId() == localId) {
            result = it->writeBytes(socketNumber);
            break;
        }
    }

    if(result == 1) {
        //Message fully send, erase it from vector of messages to be send
        writeBytesBuffer.erase(it);
    } else if(result == -1) {
        //Error while sending message, client disconnected
        deleteClientSessionPipe(socketNumber);
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);

    return result;
}

void ClientSessionPipes::createClientSession(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    ClientSessionPipe clientSessionPipe(socketNumber);
    Client client;

    pair<Client, ClientSessionPipe> session =
        make_pair(client, clientSessionPipe);

    clientSessionPipes.push_back(session);

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

void ClientSessionPipes::deleteWriteBuffers(int socketNumber) {
    long localId = getClientLocalId(socketNumber);
    if(localId < 0) return;

    /*
        Erase all messages which are addressed to disconnected client
        associated with socketNumber
    */
    writeBytesBuffer.erase(std::remove_if(
    writeBytesBuffer.begin(), writeBytesBuffer.end(),
    [&localId](BytesMessage& bytesMessage) {
        return bytesMessage.getLocalId() == localId;
    }), writeBytesBuffer.end());
}

void ClientSessionPipes::deleteClientSessionPipe(int socketNumber) {
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->second.getSocketNumber() == socketNumber) {
            writeMessagesCounter -= it->second.getWriteMessagesCount();
            deleteWriteBuffers(socketNumber);

            clientSessionPipes.erase(it);
            break;
        }
    }
}

void ClientSessionPipes::deleteClientSession(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    deleteClientSessionPipe(socketNumber);

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

vector<Client> ClientSessionPipes::getLoggedClients() {
    pthread_mutex_lock(&clientSessionPipesMutex);
    vector<Client> loggedClients;

    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->first.isLogged()) {
            loggedClients.push_back(it->first);
        }
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);

    return loggedClients;
}

void ClientSessionPipes::setClientLogin(long localId, string login) {
    pthread_mutex_lock(&clientSessionPipesMutex);
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->first.getLocalId() == localId) {
            it->first.setLogin(login);
        }
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}
