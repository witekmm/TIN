#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include "State.hpp"

using namespace std;

class CLI{

    State *state;
    string *buffer;

    public:

        void commandLine(){

            while(*state != STOPPED)
            {
                cout<<"Input message: ";
                getline(cin , *buffer);
                
                *state = SENDING;
                while(*state == SENDING);
            }
        }

        void setState(State *state){
            this->state = state;
        }

        void setBuffer(string* buffer){
            this->buffer = buffer;
        }
};


