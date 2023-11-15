#include "dumb_client.h"
#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <memory>
#include <utility>

#include "../../common_base/queue.h"
#include "../game_ui/sprites_manager.h"
#include "../game_managment/event_handler.h"
using namespace std;

DumbClient::DumbClient(const char* serv, const char* port) :
    keep(true), channel(std::move(Socket(serv, port))),
    interpreter(new DumbInterpreter(*this))
    {}

DumbClient::~DumbClient() {
    delete(interpreter);
}

void DumbClient::start() {
    cout << "Soy el cliente correcto!";
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("Worms",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    interpreter->renderer = &renderer;

    Queue<GameEvent> event_queue;
    EventHandler event_handler(window, event_queue);

    sprites_manager = new SpritesManager(renderer);
    sprites_manager->addSprite("wwalk", "resources/sprites/wwalk.png", 60, 60, 0);

    
    Animation anim(*sprites_manager,"wwalk", FrameSelectorMode::BOUNCE, 12, true);
    renderer.Clear();
    anim.render(SDL2pp::Rect(300, 300, 200, 200),true);
    renderer.Present();

    std::thread receiveThread(&DumbClient::forward, this);
    std::thread sendThread(&DumbClient::send_messages, this);

    receiveThread.join();
    sendThread.join();
}

void DumbClient::forward() {
    try {
        while (keep) {
            auto msg = channel.read_message();
            msg->execute(*interpreter);
            delete(msg);
        }
    } catch (...) {
        cout << "Exception thrown.\n";
    }
}

void DumbClient::send_messages() {
    while (keep) {
        std::string user_input;
        std::getline(std::cin, user_input);

        if (user_input == "exit") {
            stop();
            break;
        }

        if (user_input == "Move right") {
            NetMessageGameAction msg(1, ActionTypeDto::moving_right_init);
            channel.send_message(msg);
        } else if (user_input == "Move left") {
            NetMessageGameAction msg(1, ActionTypeDto::moving_left_init);
            channel.send_message(msg);
        } else if (user_input == "Stop move") {
            NetMessageGameAction msg(1, ActionTypeDto::stop_moving);
            channel.send_message(msg);
        } else if (user_input == "Jump f") {
            NetMessageGameAction msg(1, ActionTypeDto::jump_forward);
            channel.send_message(msg);
        } else if (user_input == "Jump b") {
            NetMessageGameAction msg(1, ActionTypeDto::jump_back);
            channel.send_message(msg);
        }

        // Simulate some delay between checking for console input
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void DumbClient::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        keep = false;
    }
    condition_variable_.notify_all();
    channel.dissconect();
}

DumbInterpreter::DumbInterpreter(DumbClient& cli) : cli(cli) {}

void DumbInterpreter::run(NetMessageChat* msg) {
    cout << "Client " << msg->client_id << " said: " << msg->chat << "\n";
}

void DumbInterpreter::run(NetMessageLeave* msg) {
    cli.stop();
    cout << "Bye\n";
}

void DumbInterpreter::run(NetMessageInformID* msg) {
    cout << "I AM CLIENT "<< msg->client_id << "\n";
}

void DumbInterpreter::run(NetMessage_test* msg) {
    cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " float: " << msg->test_float << " string: " << msg->test_string << "\n";
}

void DumbInterpreter::run(NetMessageInitialGameState* msg) {
    cli.stage = new TheStage(msg->room_width, msg->room_height);
}

void DumbInterpreter::run(NetMessageGameStateUpdate* msg) {
    if (!cli.initialized) {
        for (auto& wrm : msg->worms) {
            cli.stage->worms.emplace(wrm.entity_id, 
                new TheWorm(
                    wrm.client_id,wrm.entity_id,
                    cli.stage->localize_x(wrm.x),
                    cli.stage->localize_y(wrm.y),
                    *cli.sprites_manager
                )
            );
        }

        cli.initialized = true;
        return;
    }

    this->renderer->Clear();
    for (auto& wrm : msg->worms) {
        auto& myworm = cli.stage->worms[wrm.entity_id];
        
        myworm->update(
            cli.stage->localize_x(wrm.x),
            cli.stage->localize_y(wrm.y)
        );
        //myworm->update(i++*100,300);
        myworm->render();
    }
    this->renderer->Present();
}

void DumbInterpreter::run(NetMessageGameAction* msg) {
    // Client shouldnt receive
    cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}
