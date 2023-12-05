#include "net_message_factory.h"

#include "net_message_test.h"
#include "net_message_chat.h"
#include "net_message_leave.h"
#include "net_message_inform_id.h"
#include "net_message_initial_game_state.h"
#include "net_message_game_state_update.h"
#include "net_message_game_action.h"
#include "net_message_player_changed_weapon.h"
#include "net_message_player_changed_projectile_countdown.h"
#include "net_message_player_toggle_cheat.h"

#include "net_message_create_game.h"
#include "net_message_create_game_response.h"
#include "net_message_list_games.h"
#include "net_message_list_games_response.h"
#include "net_message_join_game.h"
#include "net_message_join_game_response.h"
#include "net_message_start_game.h"
#include "net_message_game_ended.h"

NetMessage* NetMessageFactory::recieve(Socket& channel) {
    NetProtocolInterpreter interpreter(channel);
    uint16_t type = interpreter.read_byte();
    
    NetMessage* inst;
    switch (type) {
        case NET_MESSAGE_TYPE_TEST:
            inst = new NetMessage_test();
            break;
        case NET_MESSAGE_TYPE_CHAT:
            inst = new NetMessageChat();
            break;
        case NET_MESSAGE_TYPE_LEAVE:
            inst = new NetMessageLeave();
            break;
        case NET_MESSAGE_TYPE_INFORM_ID:
            inst = new NetMessageInformID();
            break;
        case NET_MESSAGE_TYPE_INITIAL_STATE:
            inst = new NetMessageInitialGameState();
            break;
        case NET_MESSAGE_TYPE_UPDATE_STATE:
            inst = new NetMessageGameStateUpdate();
            break;
        case NET_MESSAGE_TYPE_GAME_ACTION:
            inst = new NetMessageGameAction();
            break;
        case NET_MESSAGE_TYPE_PLAYER_CHANGED_WEAPON:
            inst = new NetMessagePlayerChangedWeapon();
            break;
        case NET_MESSAGE_TYPE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN:
            inst = new NetMessagePlayerChangedProjectileCountdown();
            break;
        case NET_MESSAGE_TYPE_PLAYER_TOGGLE_CHEAT:
            inst = new NetMessagePlayerToggleCheat();
            break;
        case NET_MESSAGE_TYPE_CREATE_GAME:
            inst = new NetMessageCreateGame();
            break;
        case NET_MESSAGE_TYPE_CREATE_GAME_RESPONSE:
            inst = new NetMessageCreateGameResponse();
            break;
        case NET_MESSAGE_TYPE_LIST_GAMES:
            inst = new NetMessageListGames();
            break;
        case NET_MESSAGE_TYPE_LIST_GAMES_RESPONSE:
            inst = new NetMessageListGamesResponse();
            break;
        case NET_MESSAGE_TYPE_JOIN_GAME:
            inst = new NetMessageJoinGame();
            break;
        case NET_MESSAGE_TYPE_JOIN_GAME_RESPONSE:
            inst = new NetMessageJoinGameResponse();
            break;
        case NET_MESSAGE_TYPE_START_GAME:
            inst = new NetMessageStartGame();
            break;
        case NET_MESSAGE_TYPE_GAME_ENDED:
            inst = new NetMessageGameEnded();
            break;
        default:
            break;
    }

    inst->pull_data_from(interpreter);
    return inst;
}
