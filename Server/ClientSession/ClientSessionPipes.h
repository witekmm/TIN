#ifndef CLIENT_SESSION_PIPES_H
#define CLIENT_SESSION_PIPES_H

#define WRITE_MESSAGE_COND_WAIT_SEC 6

#include <pthread.h>
#include <vector>
#include <string>
#include <utility>

#include "../../Messages/Message.pb.h"

#include "ClientSessionPipe.h"
#include "Client.h"
#include "BytesMessage.h"

using namespace std;

class ClientSessionPipes {
    vector<pair<Client, ClientSessionPipe>> clientSessionPipes;

    pthread_mutex_t clientSessionPipesMutex;

    pthread_cond_t writeMessagesBufferNotEmpty;
    unsigned int writeMessagesCounter;
    bool isWriteMessagesBufferEmpty();

    vector<BytesMessage> writeBytesBuffer;
    bool isWriteBytesBufferEmpty();

    pair<Client, Message::ClientMessage> getWriteMessageBufferMessage();

    long getClientLocalId(int socketNumber);

    void deleteWriteBuffers(int socketNumber);

    void deleteClientSessionPipe(int socketNumber);

public:
    ClientSessionPipes();

    /**
    * Reads message and localId of message recipient.
    *
    * Used by Logic thread to push new messages that
    * are to be send to recipient associated with passed localId.
    *
    * @param localId localId associated with message recipient.
    * @param message message to be send.
    */
    void readMessage(long localId, Message::ClientMessage message);

    /**
    * Writes received and deserialized message with association with
    * client which has sent this message
    *
    * Used by Logic thread to pull new messages that
    * are to be handled.
    *
    * @return pair of deserialized message and sender Client object.
    */
    pair<Client, Message::ClientMessage> writeMessage();

    /**
    * Reads bytes from passed socket number.
    *
    * Used by Network thread to delegate bytes read task.
    * Method selects ClientSessionPipe associated with passed socket number
    * and delegates read task to be executed in certain client session pipe context.
    *
    * @param socketNumber socket number which is eager to be read from.
    * @return 1 if completed receiving message, 0 if part of message was received, -1 when error occured
    */
    int readBytes(int socketNumber);

    /**
    * Writes bytes to passed socket number.
    *
    * Used by Network thread to delegate bytes write task.
    * Method selects message which is to be send to passed socket number
    * and if such exists it try to send via passed socket number.
    *
    * @param socketNumber socket number which is eager to read from server.
    * @return 1 if completed sending message, 0 if part of message was send, -1 when error occured
    */
    int writeBytes(int socketNumber);

    /**
    * Creates new client session associated with passed socket number.
    *
    * Used by Network thread to create new client session.
    * Method creates new Client object representing newly connected client
    * and its session pipe which ought to be used to read bytes.
    *
    * @param socketNumber socket number to be associated with newly connected client.
    */
    void createClientSession(int socketNumber);

    /**
    * Deletes client session associated with passed socket number.
    *
    * Used by Network thread to delete client session.
    * Method deletes Client object representing connected client
    * and its session pipe.
    *
    * @param socketNumber socket number associated with client session to be deleted.
    */
    void deleteClientSession(int socketNumber);

    /**
    * Select and return active and logged clients.
    *
    * Used by Logic thread to get vector of active and logged clients.
    *
    * @return vector of active and logged client objects.
    */
    vector<Client> getLoggedClients();

    /**
    * Set client as logged.
    *
    * Used by Logic thread to set client login.
    *
    * @param localId localId of client to be logged.
    * @param login login of client to be logged.
    */
    void setClientLogin(long localId, string login);

};

#endif
