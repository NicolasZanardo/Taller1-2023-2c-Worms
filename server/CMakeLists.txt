add_library( server

    src/client/client_reciever.h
    src/client/client_reciever.cpp
    src/client/client_sender.h
    src/client/client_sender.cpp
    src/client/client.h
    src/client/client.cpp

    src/dumb_client.h
    src/dumb_client.cpp
    src/lobby/host.h
    src/lobby/host.cpp
    src/lobby/waiting_lobby.h
    src/lobby/waiting_lobby.cpp
    src/lobby/client_accepter.h
    src/lobby/client_accepter.cpp

    src/main/server.h
    src/main/server.cpp

     src/game/InGameClients.h
        src/game/InGameClients.cpp

        src/game/GameEngineInstance.h
        src/game/GameEngineInstance.cpp
        src/game/GameInstance.h
        src/game/GameInstance.cpp


        src/game/simulation/PhysicsSystem.h
        src/game/simulation/PhysicsSystem.cpp

        src/game/simulation/PhysicsCollisionListener.h
        src/game/simulation/PhysicsCollisionListener.cpp
        src/game/simulation/PhysicsSystem.h
        src/game/simulation/PhysicsSystem.cpp

        src/game/model/instances/Instance.h
        src/game/model/instances/Worm.h
        src/game/model/instances/Worm.cpp
        src/game/model/instances/InstancesManager.h
        src/game/model/instances/InstancesManager.cpp

        src/game/GameNetMessageBehaviour.h
        src/game/GameNetMessageBehaviour.cpp

        src/game/scenario/BeamScenarioData.h
        src/game/scenario/WormScenarioData.h
        src/game/scenario/GameScenarioData.h
        src/game/scenario/HardcodedScenarioData.h
        src/game/scenario/ScenarioReader.h
        src/game/scenario/ScenarioReader.cpp

        src/game/turns/TurnManager.h
        src/game/turns/TurnManager.cpp
        src/game/turns/WormIdIterator.h
        src/game/turns/WormIdIterator.cpp
)

add_executable(
    server_app
    server_main.cpp
)

target_link_libraries(server PUBLIC box2d)
target_link_libraries(server_app PUBLIC server)
target_link_libraries(server_app PUBLIC common)
