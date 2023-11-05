#include "server.h"
#include "../dumb_client.h"

#include <iostream>
#include <sstream>
using namespace std;

vector<string> split(string& action) {
	size_t pos_start = 0, pos_end;
	vector<string> res;
	string item;

	while((pos_end = action.find(";",pos_start)) != string::npos) {
		item = action.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + 1;
		res.push_back(item);
	}
	res.push_back(action.substr(pos_start));

	return res;
}

Server::Server(const char* servname) : 
	servname(servname),
	lobby(nullptr) 
	{}

Server::~Server() {
	if (lobby != nullptr)
		delete(lobby);
}

void Server::execute() {
	lobby = new WaitingLobby(servname);
	lobby->start();
	
	string action = "initialization";
	do {
		vector<string> values = split(action);

		if (values[0] == "initialization") {
			// do nothing
		} else if (values[0] == "kick") {
			kick(values);
		} else if (values[0] == "chat") {
			chat(values);
		} else if (values[0] == "stop") {
			break;
		} else {
			cout << "wrong action: " << values[0] << " Full action: " << action << "\n";
		}

		getline(cin, action);
	} while (action != "q");
	
	lobby->stop();
	lobby->join();
}

void Server::test_isHost(bool isHost) {
	if (isHost) {
		execute();
		return;
	}

	DumbClient cli("localhost", servname);
	cli.forward();
}

void Server::kick(vector<string>& values) {
	int client_id(stoi(values[1]));

	lobby->kick(client_id);
}

void Server::chat(vector<string>& values) {
	int client_id(stoi(values[1]));

	string msg(values[2]);
	for (size_t i = 3; i < values.size(); i++) {
		msg += " " + values[i];
	}

	lobby->chat(client_id, msg);
}