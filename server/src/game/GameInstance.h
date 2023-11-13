#ifndef SERVER_GAMEINSTANCE_H
#define SERVER_GAMEINSTANCE_H

#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm> // Include for std::random_shuffle
#include <cstdlib>   // Include for std::srand and std::rand
#include <random>
#include <ctime>     // Include for std::time
#include "model/instances/Worm.h"
#include "model/instances/InstancesManager.h"
#include "../client/client.h"
#include "turns/TurnManager.h"


typedef std::unordered_map<size_t, std::vector<Worm *>> ClientsWorms;

struct GameState {
    size_t currentTurnClientId;
    float windSpeed;
    float remainingGameTime;
    float remainingTurnTime;

    GameState(
            size_t currentTurnClientId,
            float windSpeed,
            float remainingGameTime,
            float remainingTurnTime
    ) : currentTurnClientId(currentTurnClientId),
        windSpeed(windSpeed),
        remainingGameTime(remainingGameTime),
        remainingTurnTime(remainingTurnTime) {}
};

class GameInstance {

    PhysicsSystem physicsSystem;
    InstancesManager instancesManager;
    ClientsWorms clientsWorms;
    TurnManager turnManager;

    void assign_worms_to_clients(const std::list<Client *> &clients);

public:
    GameInstance(
            float xGravity,
            float yGravity,
            const GameScenarioData &scenario,
            const std::list<Client *> &clients
    );

    ClientsWorms getClientsWorms();
    GameState getCurrentState();

    void update(const unsigned int it, const int diff);
    bool isClientsTurn(size_t id);

    // Actions
    void startMovingCurrentWormLeft();
    void startMovingCurrentWormRight();
    void stopMovingCurrentWorm();
    void jumpBackCurrentWorm();
    void jumpForwardCurrentWorm();


};


#endif
