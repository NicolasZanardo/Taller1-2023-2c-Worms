#include "server.h"
#include "../dumb_client.h"
#include "../lobby/waiting_lobby.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string& action) {
	size_t pos_start = 0, pos_end;
	vector<string> res;
	string item;

	while((pos_end = action.find(" ",pos_start)) != string::npos) {
		item = action.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + 1;
		res.push_back(item);
	}
	res.push_back(action.substr(pos_start));

	return res;
}

Server::Server(const char* servname) : servname(servname) {}

void Server::execute() {
	WaitingLobby lobby(servname);
	lobby.start();
	
	
	string action = "initialization";
	do {
		vector<string> values = split(action);

		if (values[0] == "initialization") {
			// do nothing
		} else if (values[0] == "kick") {
			int client_id(stoi(values[1]));
			lobby.kick(client_id);
		} else if (values[0] == "stop") {
			break;
		} else {
			cout << "wrong action: " << action << "\n  item:" << values[0] << "\n";
		}

		getline(cin, action);
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

