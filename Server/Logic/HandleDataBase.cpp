#include "HandleDataBase.h"
using namespace std;

void HandleDataBase::sendGroupMessage(string content , string groupName , string login){
  //Sprawdz czy uzytkownik w grupie
  this->createReply.userNotInGroup(groupName , login);
  //jesli tak to dodaj wiadomosc do bazy danych dla wszystkich uzytkownikow grupy
  //wyslij potwierdzenie wyslania wiadomosci
  this->createReply.groupMessageConfirmation(groupName , login);
}

void HandleDataBase::createGroup(string groupName , string login){
  //Czy nazwa grupy istnieje
  this->createReply.groupNameExist(groupName , login);
  //Stworz grupe - tworca to administrator
  this->createReply.groupCreated( groupName , login);
}

void HandleDataBase::deleteGroup(string groupName , string login){
  //czy grupa istnieje
  this->createReply.groupDoesntExist(groupName , login);
  //czy jest jej administratorem
  this->createReply.noRightsToDeleteGroup(groupName , login);
  //Usun grupe
  this->createReply.groupDeleted(groupName , login);
}

void HandleDataBase::requestToGroup(string groupName , string login){
  //czy grupa istnieje
  this->createReply.groupDoesntExist(groupName , login);
  //czy naleze do grupy
  this->createReply.userAlreadyInGroup(groupName , login);
  //dodaj wiadomosc do bazy danych
  //wyslano
  this->createReply.requestSend(groupName ,  login);
}

void HandleDataBase::acceptRequest(string groupName , string userName ,string login){
  //sprawdzy czy jest administratorem grupy
  this->createReply.noRightsToReplyRequest(groupName , login);
  //Sprawdz czy taki request istnieje
  this->createReply.NoRequestFromThisPerson(userName , login);
  //usun request z bazy danych
  //dodaj uzytkownika do grupy
  //wyslij potweirdznie dodanie do administratora i uzytkownika dodanego
  this->createReply.requestAccepted( groupName ,  userName , login);
  //dodaj wiadomosc do bazy danych dla uzytkownika ktory zlozyl prosbe
}

void HandleDataBase::declineRequest(string groupName , string userName ,string login){
  //sprawdzy czy jest administratorem grupy
  this->createReply.noRightsToReplyRequest( groupName ,  login);
  //Sprawdz czy taki request istnieje
  this->createReply.NoRequestFromThisPerson( userName,  login);
  //usun request z bazy danych
  //wyslij potweirdznie odrzucenia do administratora i uzytkownika dodanego
  this->createReply.requestDeclined( groupName ,  userName , login);
    //dodaj wiadomosc do bazy danych dla uzytkownika ktory zlozyl prosbe
}

void HandleDataBase::leaveGroup(string groupName , string login){
  //sprawdz cyz nalezy do grupy
  this->createReply.userNotInGroup( groupName ,  login);
  string newAdmin;
  /*if( user == admin){
      if( ilosc uzytkownikow >1)
        administrator sie zmienia
        usun z grupy
      else
        usun grupe
    }*/
  //usun z grupy
  this->createReply.userLeftGroup( groupName ,  login);
  //ywslij info o nowym administratorze do niego
  this->createReply.newAdmin( groupName , newAdmin);
}

void HandleDataBase::logInUser(string login, string password, int socketNumber){
  //sprawdz czy istnieje taki login
  //porownaj skrot haslo z bazy danych  i przekaznaego
  this->createReply.incorrectData(login , socketNumber);
  //uzytkownik zalogowany
  this->createReply.userLogged(login, socketNumber);
  //pobierz z bazy danych wszystki grupy do ktorych nalezy login
  vector<string> groupList;
  this->createReply.sendGroups(groupList , login , socketNumber);
}

void HandleDataBase::addLogin(string login, int socketNumber){
  //sprawdz czy istnieje login
  this->createReply.loginIsForbidden(login , socketNumber);
  //wysylamy ze tak
  this->createReply.loginIsAvailable(login , socketNumber);
}

void HandleDataBase::addPasswordToLogin(string login, string password, int socketNumber){
  //sprawdz czy istnieje login
  this->createReply.loginIsForbidden(login , socketNumber);
  //wysylamy potwierdzenie
  this->createReply.userAccountCreated(login , socketNumber);
}

void HandleDataBase::checkIfMessageExistAndSend(string login){
  //sprawdz czy istnieje
  //jest tak to pobierz z bazy danych i wyslij
//  this->createReply.sendMessage(string content, string toWho, string fromWho, string whichGroup);
}

int HandleDataBase::rootDeleteGroup(string groupName){
  //SPRAWDZ CZY GRUPA istnieje
  // return 0
  //JESLI nie to usun grupe
  return 1;
}
int HandleDataBase::rootDeleteUser(string login){
  //SPRAWDZ CZY uzytkownik istnieje
  // return 0
  //JESLI nie to usun uzytkownika
  return 1;
}
int HandleDataBase::rootAddUser(string login, int password){
  //SPRAWDZ CZY uzytkownik istnieje
  // return 0
  //JESLI nie to dodaj uzytkownika
  return 1;
}
int HandleDataBase::rootAddGroup(string groupName, string administrator){
  //SPRAWDZ CZY grupa istnieje
  // return -1
  //SPRAWDZ CZY administrator (to login uzytkownika) istnieje
  // return -2
  //JESLI nie to dodaj uzytkownika
  return 1;
}
