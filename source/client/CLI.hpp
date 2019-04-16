#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include "State.hpp"

using namespace std;

class CLI{

    State state;
    char* buffer;

    public:
        CLI(){

        }

        void commandLine(){

            cout<<"command state: "<<&state<<endl;
            while(state != STOPPED)
            {
                string command;
                //char tempBuffer[256];
                cout<<"Input message: ";
                //getline(cin , command);
                scanf("%255s", buffer);
                while((getchar()) != '\n');
                int leng = strlen(buffer);
                buffer[leng] = '\0';
                cout<<"command: "<<(string)buffer<<endl;
        
                state = SENDING;
                while(state == SENDING);
            }
        }

        void setState(State &state){
            this->state = state;
        }

        void setBuffer(char* buffer){
            this->buffer = buffer;
        }
};


