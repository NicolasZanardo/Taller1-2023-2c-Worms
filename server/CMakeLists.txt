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

    src/main/server.h
    src/main/server.cpp

    src/GameInstance.h
    src/GameInstance.cpp

    src/simulation/PhysicsSystem.cpp
    src/simulation/PhysicsSystem.h
    src/model/scenario/GameScenarioData.h
        src/model/scenario/HardcodedScenarioData.h
        src/model/entities/Entity.h
        src/model/entities/Worm.cpp
        src/model/entities/Worm.h
        src/model/entities/EntityManager.h
        src/model/entities/EntityManager.cpp
)

add_executable(
    server_app
    server_main.cpp
)

target_link_libraries(server PUBLIC box2d)
target_link_libraries(server_app PUBLIC server)
target_link_libraries(server_app PUBLIC common)
