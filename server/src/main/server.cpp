#include "server.h"
#include "../lobby/waiting_lobby.h"

#include <iostream>
#include <string>
using namespace std;

Server::Server(const char* servname) : servname(servname) {}

void Server::execute() {
	WaitingLobby lobby(servname);
	lobby.start();
	
	//cin.ignore();
	string action;
	do {
		action = cin.get();
	} while (action != "q");
	
	lobby.stop();
	lobby.join();
}