#===============================================================================
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable (sdlpp-events
    animation.cpp animation.h
    client_main.cpp
    client.cpp client.h
    client_receiver.cpp client_receiver.h
    client_sender.cpp client_sender.h
    cursor.cpp cursor.h
    event_handler.cpp event_handler.h
    frame_selector.cpp frame_selector.h
    game_loop.cpp game_loop.h
    icon.cpp icon.h
    player_state.cpp player_state.h
    sprite.cpp sprite.h
    sprites_manager.cpp sprites_manager.h
)

target_link_libraries(sdlpp-events common ${SDL2PP_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
