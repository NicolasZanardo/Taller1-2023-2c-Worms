#include "client_sender.h"

ClientSender::ClientSender(Queue<GameEvent>& event_queue, Queue<GameEvent>& echo_queue)
    : event_queue(event_queue), echo_queue(echo_queue) {}

void ClientSender::run() {
    while (Thread::keep_running_) {
        try {
            GameEvent game_event = this->event_queue.pop();

            this->echo_queue.push(game_event);
        } catch (const ClosedQueue& e) {
            Thread::stop();
        }
    }
}
