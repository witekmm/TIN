#!/bin/bash
g++ -Wall -I/usr/include/cppconn -o $2 $1 -L/usr/lib -lmysqlcppconn
#g++ -o $2 $1 -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
