#===============================================================================
add_subdirectory(poc_sdl)

#===============================================================================
add_library(client
    client.cpp client.h
)

add_executable(client_app
    client_main.cpp
)

target_include_directories(client_app PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)

target_link_libraries(client_app PUBLIC
    client
)
