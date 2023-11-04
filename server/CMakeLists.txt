add_library( server
    src/dumb_client.cpp
    src/dumb_client.h
    src/lobby/host.cpp
    src/lobby/host.h
    src/lobby/waiting_lobby.cpp
    src/lobby/waiting_lobby.h

    src/main/server.h
    src/main/server.cpp
)

add_executable(
    server_app
    server_main.cpp
)

target_link_libraries(server PUBLIC box2d)
target_link_libraries(server_app PUBLIC server)
target_link_libraries(server_app PUBLIC common)
