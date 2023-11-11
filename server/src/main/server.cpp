#include "server.h"
#include "../dumb_client.h"
#include "../GameInstance.h"

#include <iostream>
#include <sstream>
using namespace std;

void Server::execute() {
	lobby.start();
	accepter.start();

	handle_input();

	// MANEJAR EL CASO DONDE EL CLIENTE ES QUIEN SE DESCONECTA PORQUE QUEDA EN UN JOIN ETERNO.

	accepter.stop();
	lobby.stop();
}

vector<string> split(string& action);
void Server::handle_input() {
	string action = "initialization";
	do {
		vector<string> values = split(action);

		if (values[0] == "initialization") {
			// do nothing
		} else if (values[0] == "kick") {
			kick(values);
		} else if (values[0] == "chat") {
			chat(values);
		} else if (values[0] == "start") {
			start(values);
		} else if (values[0] == "stop") {
			break;
		} else {
			cout << "wrong action: " << values[0] << " Full action: " << action << "\n";
		}

		getline(cin, action);
	} while (action != "q");
}

void Server::kick(vector<string>& values) {
	int client_id(stoi(values[1]));
	NetMessageLeave msg(client_id);
	lobby.run(&msg);
}

void Server::chat(vector<string>& values) {
	int client_id(stoi(values[1]));

	string chat(values[2]);
	for (size_t i = 3; i < values.size(); i++) {
		chat += " " + values[i];
	}

	NetMessageChat msg(client_id, chat);
	lobby.run(&msg);
}

void Server::start(vector<string>& values) {
	lock_guard lock(active_games_mtx);
	active_games.push_back(lobby.start_game());
}

Server::Server(const char* servname) : 
	lobby(), accepter(servname, this->lobby),
	active_games_mtx(), active_games()
	{}

Server::~Server() {
	{
		lock_guard lock(active_games_mtx);
		for (auto game : active_games) {
			delete(game);
		}
		active_games.clear();
	}

}

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