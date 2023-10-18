add_library(server
    server.cpp server.h
)

add_executable(server_app
    server_main.cpp
)

target_include_directories(server_app PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)

target_link_libraries(server_app PUBLIC
    server
)
