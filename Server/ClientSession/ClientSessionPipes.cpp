#include <pthread.h>
#include <vector>
#include <string>
#include <utility>

#include "../../Messages/Message.pb.h"

#include "ClientSessionPipes.h"
#include "ClientSessionPipe.h"
#include "Client.h"

using namespace std;

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

void readMessage(string login, Message::ClientMessage message) {
    pthread_mutex_lock(&clientSessionPipesMutex);

    string bytes;
    message.SerializeToString(&bytes);

    writeBytesBuffer.push_back(make_pair(login, bytes));

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
        ++writeMessagesCounter;
        pthread_cond_signal(&writeMessagesBufferNotEmpty);
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
}

string ClientSessionPipes::getClientLogin(int socketNumber) {
    vector<pair<Client, ClientSessionPipe>>::iterator it;

    for(it = clientSessionPipes.begin(); it != clientSessionPipes.end(); ++it) {
        if(it->second.getSocketNumber() == socketNumber) {
            return it->first.getLogin();
        }
    }

    return nullptr;
}

void ClientSessionPipes::writeBytes(int socketNumber) {
    pthread_mutex_lock(&clientSessionPipesMutex);
    if(isWriteBytesBufferEmpty()) {
        pthread_cond_wait(&writeBytesBufferNotEmpty, 
            &clientSessionPipesMutex);
    }

    string login = getClientLogin(socketNumber);
    if(login == nullptr) return;

    vector<pair<string, string>>::iterator it;

    for(it = writeBytesBuffer.begin(); it != writeBytesBuffer.end(); ++it) {
        if(it->first.getLogin() == login) {
            //TODO: send bytes
            //TODO: delete message from writeBytesBuffer only when all bytes sent

            break;
        }
    }

    pthread_mutex_unlock(&clientSessionPipesMutex);
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

void ClientSessionPipes::deleteClientSession(int socketNumber) {
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