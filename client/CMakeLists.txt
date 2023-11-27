#===============================================================================
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable (client_app
    client_main.cpp
    client.cpp client.h
    # dumb_simple_client/dumb_client.cpp dumb_simple_client/dumb_client.h

    game_display/game_sprite_manager.h game_display/game_sprite_manager.cpp
    game_display/game_clock.h game_display/game_clock.cpp
    game_display/game_display.h game_display/game_display.cpp
        
    game_display/worm/game_worm_entity.h game_display/worm/game_worm_entity.cpp
    game_display/worm/worm_anim_key_mapper.h game_display/worm/worm_anim_key_mapper.cpp
        game_display/worm/worm_anim_key.h

    game_display/projectiles/game_projectile_entity.h game_display/projectiles/game_projectile_entity.cpp
    game_display/projectiles/projectile_sprite_key_mapper.h game_display/projectiles/projectile_sprite_key_mapper.cpp

    game_display/ui_elements/game_displayable.h
    game_display/ui_elements/game_camera.h       game_display/ui_elements/game_camera.cpp
    game_display/ui_elements/game_text_display.h game_display/ui_elements/game_text_display.cpp
    game_display/ui_elements/game_sprite_info.h  game_display/ui_elements/game_sprite_info.cpp
    game_display/ui_elements/game_sprite.h       game_display/ui_elements/game_sprite.cpp
    game_display/ui_elements/game_worm_animation_set.h game_display/ui_elements/game_worm_animation_set.cpp
    game_display/sprite_keys.h

    game_managment/client_receiver.cpp game_managment/client_receiver.h
    game_managment/client_sender.cpp game_managment/client_sender.h
    game_managment/cursor.cpp game_managment/cursor.h
    game_managment/event_handler.cpp game_managment/event_handler.h
    game_managment/commands/Command.h
        game_managment/commands/ChangeWeaponCommand.h game_managment/commands/ChangeWeaponCommand.cpp
        game_managment/commands/ChangeProjectileCountDownCommand.h game_managment/commands/ChangeProjectileCountDownCommand.cpp
        game_managment/commands/GameActionCommand.h game_managment/commands/GameActionCommand.cpp
    #game_ui/animation.cpp game_ui/animation.h
    game_ui/client_game_state.cpp game_ui/client_game_state.h
    game_ui/game_loop.cpp game_ui/game_loop.h
    game_ui/ui_utils.h game_ui/ui_utils.cpp
)

target_include_directories(client_app PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_managment"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_display"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_display/worm"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_display/projectiles"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_display/ui_elements"
)

target_link_libraries(client_app common ${SDL2PP_LIBRARIES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/bin)

#===============================================================================
# include_directories(PUBLIC ${SDL2PP_INCLUDE_DIRS})
# file(COPY resources/sprites DESTINATION ${CMAKE_BINARY_DIR}/bin)
# file(GLOB_RECURSE model_sources src/model/*.cpp src/model/*.h)
# file(GLOB_RECURSE presentation_sources src/presentation/*.cpp src/presentation/*.h)

# add_library(client
#         ${model_sources}
#         ${presentation_sources}
#         src/client.cpp src/client.h
# )

# add_executable(client_app
#         src/client_main.cpp
# )

# target_include_directories(client_app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
# target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/model")
# target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/presentation")

# target_link_libraries(client_app PRIVATE common)
# target_link_libraries(client_app PUBLIC client)
# target_link_libraries(client_app PUBLIC ${SDL2PP_LIBRARIES})
