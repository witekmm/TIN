#include <pthread.h>
#include <vector>
#include <errno.h>

#include "../Network/NetLibs.h"
#include "../../Messages/Message.pb.h"

#include "ClientSessionPipe.h"

using namespace std;

ClientSessionPipe::ClientSessionPipe(int socket) {
    socketNumber = socket;
    writeMessagesBuffer.clear();
    clearReadBytesVariables();
}

void ClientSessionPipe::clearReadBytesVariables() {
    numberOfBytesToRead = MESSAGE_SIZE_BYTES_NUMBER;
    bytesMessageSizeRead = false;
    readBytesBuffer.clear();
}

int ClientSessionPipe::getSocketNumber() {
    return socketNumber;
}

size_t ClientSessionPipe::getWriteMessagesCount() {
    return writeMessagesBuffer.size();
}

bool ClientSessionPipe::isWriteMessagesBufferEmpty() {
    return writeMessagesBuffer.empty();
}

Message::ClientMessage ClientSessionPipe::getWriteMessageBufferMessage() {
    Message::ClientMessage message = writeMessagesBuffer.back();
    writeMessagesBuffer.pop_back();

    return message;
}

void ClientSessionPipe::addWriteMessage(Message::ClientMessage message) {
    writeMessagesBuffer.push_back(message);
}

int ClientSessionPipe::readBytesSize() {
    char *tmp = new char[numberOfBytesToRead];
    //char *tmp = (char *)malloc(numberOfBytesToRead);
    int bytesReceived = recv(this->socketNumber, tmp,
        numberOfBytesToRead, MSG_DONTWAIT);
    if(errno != 0){
      return -1;
    }
    cout<<"Received: "<<bytesReceived<<" bytes."<<endl;
    if(bytesReceived == MESSAGE_SIZE_BYTES_NUMBER) {
        //Message size fully read
        bytesMessageSizeRead = true;
      //  numberOfBytesToRead = atoi(tmp);
        this->numberOfBytesToRead = (int)*tmp;
        cout<<"Payload is gonna be "<<this->numberOfBytesToRead<<" bytes"<<endl;
        delete [] tmp;
        //free(tmp);
        return 0;
    } else if(bytesReceived >= 0 && bytesReceived < MESSAGE_SIZE_BYTES_NUMBER) {
        //Message size partially read
        numberOfBytesToRead -= bytesReceived;

        string tmpString(tmp, bytesReceived);
        readBytesBuffer += tmpString;

        if(numberOfBytesToRead == 0) {
            numberOfBytesToRead = atoi(readBytesBuffer.c_str());
            bytesMessageSizeRead = true;

            readBytesBuffer.clear();
        }
        //free(tmp);
        delete [] tmp;
        return 0;
    } else {
        //Error while reading message size
        clearReadBytesVariables();
        delete [] tmp;
        //free(tmp);
        return -1;
    }
}

int ClientSessionPipe::readBytesMessage() {
    char *tmp = new char[numberOfBytesToRead];

    int bytesReceived = recv(this->socketNumber, tmp,
        numberOfBytesToRead, MSG_DONTWAIT);

    cout<<"Received - "<<bytesReceived<<endl;
    if(bytesReceived >= 0) {
        numberOfBytesToRead -= bytesReceived;

        //string tmpString(tmp, bytesReceived);
        string tmpString(tmp);
        readBytesBuffer += tmpString;

        if(numberOfBytesToRead == 0) {
            //Message fully read, parse it and add to message buffer
            Message::ClientMessage message;
            message.ParseFromString(readBytesBuffer);
            cout<<message.messagetype()<<message.authorizationtype()<<message.login()<<message.password();

            addWriteMessage(message);

            clearReadBytesVariables();
            delete [] tmp;
            return 1;
        }

        delete [] tmp;
        return 0;

    } else {
        //Error while reading message
        clearReadBytesVariables();
        delete [] tmp;
        return -1;
    }
}

int ClientSessionPipe::readBytes() {
    int result;

    if(!bytesMessageSizeRead) {
        result = readBytesSize();
    } else {
        result = readBytesMessage();
    }

    return result;
}
