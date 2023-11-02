add_library( server
    src/dumb_client.cpp 
    src/dumb_client.h 
    src/host.cpp 
    src/host.h

    server.h
    server.cpp
)

add_executable(
    server_app
    server_main.cpp
)

target_link_libraries(server PUBLIC box2d)
target_link_libraries(server_app PUBLIC server)
target_link_libraries(server_app PUBLIC common)
