#include "waiting_lobby.h"
#include <exception>
#include <iostream>

using namespace std;

// bool purged_zombie(Client* cli);

WaitingLobby::WaitingLobby()
    // : Thread()
    : mtx()
    , clients()
    , input_queue(60) {}

void WaitingLobby::addClient(const int id, Socket skt, GamesManager& games_manager) {
    std::lock_guard<std::mutex> lock(this->mtx);

    std::unique_ptr<Client> client_new = std::make_unique<Client>(id, std::move(skt), games_manager);
    client_new->switch_lobby(&(this->input_queue));

    std::shared_ptr<NetMessage> net_message(new NetMessageInformID(client_new->id));
    client_new->communicate(net_message);

    // Push back at end.
    this->clients.push_back(std::move(client_new));
}

void WaitingLobby::removeZombies() {
    std::lock_guard<std::mutex> lock(this->mtx);

    clients.remove_if([](auto& client) { return (client->is_alive()) ? false : true; });

    // clients.remove_if(purged_zombie);
}

void WaitingLobby::removeAll() {
     std::lock_guard<std::mutex> lock(this->mtx);

     this->clients.clear();
}

// void WaitingLobby::run() {
//     while (keep_running_) {
//         try {
//             return;
//             auto message = input_queue.pop();
//             remove_zombies();
//             message->execute(*this);
//         } catch (const std::exception& ex) {
//             keep_running_ = false;
//         }
//     }
// }

// void WaitingLobby::stop() {
//     std::lock_guard<std::mutex> lock(this->mtx);

//     keep_running_ = false;
//     input_queue.close();
//     join();

//     lock_guard lock(clients_mtx);
//     for (auto& it : clients) {
//         delete(it);
//     }
//     clients.clear();
// }


// bool purged_zombie(Client* cli) {
//     if (cli->is_alive())
//         return false;

//     delete(cli);
//     return true;
// }

// GameEngineInstance* WaitingLobby::start_game() {
//         auto game = new GameEngineInstance(
//             0, -40, HardcodedScenarioData::get(),
//             clients
//         );
//         game->start();
//         return game;

// } // TODO There is no Join for now

// void WaitingLobby::add(Client* new_client) {
//     lock_guard lock(clients_mtx);

//     std::unique_ptr<Client> client = std::make_unique<Client>();

//     clients.push_back(new_client);
//     new_client->switch_lobby(&input_queue);
//     std::shared_ptr<NetMessage> net_message(new NetMessageInformID(new_client->id));
//     new_client->communicate(net_message);

//     cout << "The client " << new_client->id << " just connected.\n";
// }

// void WaitingLobby::run(NetMessageChat* msg) {
//     lock_guard lock(clients_mtx);
//     std::shared_ptr<NetMessage> net_message(new NetMessageChat(msg->client_id, msg->chat));

//     for (auto& it : clients) {
//         it->communicate(net_message);
//     }
//     cout << "Client " << msg->client_id << ": said: " << msg->chat << ".\n";
// }

// void WaitingLobby::run(NetMessageLeave* msg) {
//     lock_guard lock(clients_mtx);
//     std::shared_ptr<NetMessage> net_message(new NetMessageChat(msg->client_id, "I'm leaving."));

//     for (auto& it : clients) {
//         if (it->id == msg->client_id) {
//             it->disconnect();
//         } else {
//             it->communicate(net_message);
//         }
//     }
//     cout << "Kicking client " << msg->client_id << ".\n";
// }

// void WaitingLobby::run(NetMessageInformID* msg) {
//     cout << "ERROR: The client " << msg->client_id << " informed their id...";
// }

// void WaitingLobby::run(NetMessage_test* msg) {
//     lock_guard lock(clients_mtx);
//     std::shared_ptr<NetMessage> net_message(msg);

//     for (auto& it : clients) {
//         it->communicate(net_message);
//     }
// }

// void WaitingLobby::run(NetMessageInitialGameState* msg) {
//     cout << "ERROR: Shouldnt receive MessageInitialState...";
// }

// void WaitingLobby::run(NetMessageGameStateUpdate* msg) {
//     cout << "ERROR: Shouldnt receive MessageGameUpdate...";
// }

// void WaitingLobby::run(NetMessageGameAction* msg) {
//     cerr << "Error: received action in lobby..";
// }

// void WaitingLobby::run(NetMessagePlayerChangedWeapon* msg) {
//     cerr << "Error: received action in lobby..";
// }

// void WaitingLobby::run(NetMessagePlayerChangedProjectileCountdown* msg) {
//     cerr << "Error: received action in lobby..";
// }

// void WaitingLobby::run(NetMessageGameEnded* msg) {
//     cerr << "Error: received GameEnded in lobby..";
// }

