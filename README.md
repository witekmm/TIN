# [TIN] Czat grupowy :speech_balloon:

## Skład zespołu projektowego

  - Michał Witkowski
  - Jakub Szachewicz
  - Wojciech Kurek
  - Mateusz Krawczyk
  
## Uruchomienie serwera
```
./server -p port_number -i ip_address -c max_connections_number
```

Opcjonalne flagi uruchomienia programu:
  - `-p` numer portu
  - `-i` adres ip servera
  - `-c` maksymalna liczba połączeń

## Komendy CLI serwera
  - `start server` create server socket and bind it to ip
  - `start listening` set server socket to passive mode
  - `start waiting` create thread that is waiting on select
  - `stop server` stop waiting on select, disconnect all client, destroy server socket
  - `stop waiting` stop waiting on select, all clients are still connected
  - `set port PORT_NUMBER` set port number (only when server is stopped)
  - `set connections NUMBER_OF_CONNECTIONS` set max number of connections (only when server is stopped)
  - `close SOCKET_NUMBER` disconnect client on choosen socket
  - `closebylogin CLIENT_LOGIN` disconnect client with choosen login

## Budowanie serwera (Ubuntu) :hammer:
  1) Wymagana jest instalacja [Protocol Buffers](https://developers.google.com/protocol-buffers/) w wersji [v3.7.1](https://github.com/protocolbuffers/protobuf/releases/tag/v3.7.1)
  Należy pobrać paczkę [protobuf-cpp-3.7.1.tar.gz](https://github.com/protocolbuffers/protobuf/releases/tag/v3.7.1) i postępować zgodnie z instrukcjami wewnątrz pliku `src/README.md`
  2) Wymagana jest instalacja sterowników do bazy danych MySQL.
  2.1) Należy zainstalować libboost-all-dev
      ``` 
      sudo apt-get install libboost-all-dev
      ```
        2.2) Ze [strony ze streownikami](https://dev.mysql.com/downloads/connector/cpp/8.0.html) nalezy pobrać następujące pliki (lub odpowiadające im wersje dla posiadanej wersji Ubuntu):
      - ibmysqlcppconn7_8.0.16-1ubuntu18.04
      - libmysqlcppconn7-dbgsym_8.0.16-1ubuntu18.04
      - libmysqlcppconn8-2_8.0.16-1ubuntu18.04
      - libmysqlcppconn8-2-dbgsym_8.0.16-1ubuntu18.04
      - libmysqlcppconn-dev_8.0.16-1ubuntu18.04
      
      2.3) Dla każdegego z powyższych plików należy wykonac instrukcję (zachowując powyższą kolejność plików):
      ```
      sudo dpkg -i FILE_NAME
      ```
      
     Przykładowo:
      ```
      sudo dpkg -i ibmysqlcppconn7_8.0.16-1ubuntu18.04
      ```
      
3) Budowanie programu serwera (za pomocą `Makefile`)
      ```
      make
      ```


