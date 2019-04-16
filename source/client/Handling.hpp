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

using namespace std;

class Handling{

    CLI cli;
    State state;
    int socket;
    char buffer[256];

    public:
            
        Handling(int &socket){
            this->socket = socket;
            this->state = RUNNING;
        }

        void input(){
            cout<<"here state: "<<&state<<endl;
            cli.setState(this->state);
            cli.setBuffer(this->buffer);
            cli.commandLine();
        }

        void run(){

            cout<<"handler state: "<<&state<<endl;
            while(state != STOPPED)
            {   
                                 
                if(state == SENDING)
                {
                    cout<<"Sending"<<endl;
                    /*
                    if(send(socket, &buffer, strlen(buffer)+1, 0) == -1){
                        perror("Cannot send");
                        state = STOPPED;
                    }
                    */
                    if((string)buffer == "exit"){
                        cout<<"Closing client"<<endl;
                        //if( recv(socket, NULL, 1, 0) == 0)
                            break;
                    }
                    
                    state = RUNNING;
                }
                /*
                else if( recv(socket, NULL, 1, 0) == 0){
                    cout<<"\nServer signal. \nClosing client"<<endl;
                    break;
                }
                */
            }
        }

        void handleCommand(string command){

            if(command == "exit"){
                this->state = STOPPED;
            }


        }

        void setCLI(CLI cli){
            this->cli = cli;
        }

};