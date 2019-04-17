#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>

//#include "State.hpp"
#include "CLI.hpp"
//#include "../message.cpp"

using namespace std;

class Handling{

    CLI cli;
    State *state;
    int socket;
    string *buffer;

    public:
            
        Handling(int &socket){
            
            this->socket = socket;
            this->state = new State(RUNNING);
            if(state == NULL){perror("Bad allock"); exit(0);}
            this->buffer = new string();
            if(state == NULL){perror("Bad allock"); exit(0);}
        }

        void input(){
            
            cli.setState(this->state);
            cli.setBuffer(this->buffer);
            cli.commandLine();
        }

        void run(){

            while(*state != STOPPED)
            {   
                if(*state == SENDING)
                {
                    Message mess(*buffer);
                    
                    if(send(socket, &mess, mess.getSendLength(), 0) == -1){
                        perror("Cannot send");
                        state = STOPPED;
                    }
                    
                    if(*buffer == "exit"){
                        if( recv(socket, NULL, 1, 0) ==0)
                            cout<<"Received exit signal. Closing client."<<endl;
                            *state = STOPPED;
                            pthread_exit(0);
                    }
                    *state = RUNNING;
                }
                
                if( recv(socket, NULL, 1, 0) == 0){
                    cout<<"\nServer signal - connection lost. \nClosing client."<<endl;
                    *state = STOPPED;
                    pthread_exit(0);
                }
                
            }
        }

        void handleCommand(string command){

            if(command == "exit"){
                *(this->state) = STOPPED;
            }
        }

        void setCLI(CLI cli){
            this->cli = cli;
        }

        ~Handling(){
            delete state;
            delete buffer;
        }
};