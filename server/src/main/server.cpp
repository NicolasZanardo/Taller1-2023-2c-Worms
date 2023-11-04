#include "server.h"
#include "../dumb_client.h"
#include "../lobby/waiting_lobby.h"

#include <iostream>
#include <string>
using namespace std;

Server::Server(const char* servname) : servname(servname) {}

void Server::execute() {
	WaitingLobby lobby(servname);
	lobby.start();
	
	string action;
	do {
		action = cin.get();
	} while (action != "q");
	
	lobby.stop();
	lobby.join();
}

void Server::test_isHost(bool isHost) {
	if (isHost) {
		execute();
		return;
	}

	DumbClient cli("localhost", servname);
	cli.forward();
}