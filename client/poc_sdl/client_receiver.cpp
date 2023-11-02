#include "client_receiver.h"

ClientReceiver::ClientReceiver(Queue<GameEvent>& state_queue, Queue<GameEvent>& echo_queue)
    : state_queue(state_queue), echo_queue(echo_queue) {}

void ClientReceiver::run() {
    while (Thread::keep_running_) {
        try {
            GameEvent game_event = this->echo_queue.pop();

            this->state_queue.push(game_event);
        } catch (const ClosedQueue& e) {
            Thread::stop();
        }
    }
}
