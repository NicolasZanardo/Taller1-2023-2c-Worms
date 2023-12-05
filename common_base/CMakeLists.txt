add_library(common
    Networking/socket_connection_lost_error.h 
    Networking/socket_connection_lost_error.cpp
    Networking/net_buffer.h
    Networking/net_buffer.cpp
    Networking/net_protocol_interpreter.h
    Networking/net_protocol_interpreter.cpp

        Game/game_info_dto.h
        Game/beamDto.h
        Game/bulletDto.h
        Game/eventDto.h
        Game/wormDto.h
        Game/WeaponTypeDto.h
        Game/ProjectileDto.h
        Game/GameAction.h
        Game/GameWorldEventType.h
        Game/ProjectileCountDown.h
        Game/ProjectileTypeDto.h
        Game/ExplosionDto.h
        Game/CheatType.h

    liberror.cpp liberror.h
    network_channel.cpp network_channel.h
    protocol_consts.h
    queue.h
    resolver.cpp resolver.h
    resolvererror.cpp resolvererror.h
    socket.cpp socket.h
    thread.h

    Networking/net_operator.h
    Networking/net_operator.cpp

    Networking/Messages/net_message.h
    Networking/Messages/net_message.cpp
    Networking/Messages/net_queue.h
    Networking/Messages/net_queue.cpp
    Networking/Messages/net_message_factory.h
    Networking/Messages/net_message_factory.cpp
    Networking/Messages/net_message_test.h
    Networking/Messages/net_message_chat.h
    Networking/Messages/net_message_chat.cpp
    Networking/Messages/net_message_leave.h
    Networking/Messages/net_message_leave.cpp
    Networking/Messages/net_message_inform_id.h
    Networking/Messages/net_message_inform_id.cpp

        Networking/Messages/net_message_game_action.h
        Networking/Messages/net_message_game_action.cpp
        Networking/Messages/net_message_player_changed_weapon.h
        Networking/Messages/net_message_player_changed_weapon.cpp
        Networking/Messages/net_message_player_changed_projectile_countdown.h
        Networking/Messages/net_message_player_changed_projectile_countdown.cpp

    Networking/Messages/net_message_behaviour.h
    Networking/Messages/net_message_initial_game_state.h
    Networking/Messages/net_message_initial_game_state.cpp
    Networking/Messages/net_message_game_state_update.h
    Networking/Messages/net_message_game_ended.h
    Networking/Messages/net_message_game_ended.cpp
    Networking/Messages/net_message_game_state_update.cpp

    Networking/Messages/net_message_create_game.h
    Networking/Messages/net_message_create_game.cpp
    Networking/Messages/net_message_create_game_response.h
    Networking/Messages/net_message_create_game_response.cpp

    Networking/Messages/net_message_list_games.h
    Networking/Messages/net_message_list_games.cpp
    Networking/Messages/net_message_list_games_response.h
    Networking/Messages/net_message_list_games_response.cpp

    Networking/Messages/net_message_join_game.h
    Networking/Messages/net_message_join_game.cpp
    Networking/Messages/net_message_join_game_response.h
    Networking/Messages/net_message_join_game_response.cpp
    Networking/Messages/net_message_player_toggle_cheat.h
    Networking/Messages/net_message_player_toggle_cheat.cpp

    Networking/Messages/net_message_start_game.h
    Networking/Messages/net_message_start_game.cpp

    Networking/net_channel.h
    Networking/net_channel.cpp

    networking.h

    constants.h
    roulete.h
    Game/game_clock.h
    Game/game_clock.cpp
)

target_include_directories(common PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)
