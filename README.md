# TIN - Czat grupowy

Michał Witkowski

Jakub Szachewicz

Wojtek Kurek

Mateusz Krawczyk


Uruchomienie serwera:
```
./server -flag flag_value
-p port_number
-i ip_number
-c connections_number
```

Komendy CLI:
```
start server - create server socket and bind it to ip
start listening - set server socket to passive mode
start waiting  - create thread that is waiting on select
stop server - stop waiting on select , disconnect all client , destroy server socket
stop waiting - stop waiting on select , all clients are still connected
set port NUMBER_OF_PORT - set port number (only when server is stopped)
set connections NUMBER_OF_CONNECTIONS - set max number of connections (only when server is stopped)
close NUMBER_OF_SOCKET - disconnect client on choosen socket
closebylogin CLIENT_LOGIN - disconnect client with choosen login
add user user_name password - add new user to database
add group group_name user_name - add new group and set user as admin
delete user user_name - delete user
delete group group_name - delete group
```
