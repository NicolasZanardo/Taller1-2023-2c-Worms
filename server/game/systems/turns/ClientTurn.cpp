#include "ClientTurn.h"

ClientTurn::ClientTurn(int client_id) :
    client_id(client_id), worms() {}

std::shared_ptr<Worm> ClientTurn::get_current_worm() {
    return worms[current_worm_idx];
};

void ClientTurn::advance_next_worm() {
    // TODO not sure if the if is needed anymore, no time to test
    if (current_worm_idx >= worms.size()) {
        current_worm_idx = 0;
    } else {
        current_worm_idx++;
        if (current_worm_idx >= worms.size()) {
            current_worm_idx = 0;
        }
    }
}

/*
 * If present removes the worm pointer from the worms vector and adjust the current_idx to a correct state
 *
 * if the removed worm was at an index previous to the current_idx, decrease the current_idx by one
 * if the removed worm was at the end of the vector, reset the current_idx to 0
 */
void ClientTurn::remove(int worm_id) {
    int removed_idx = -1;
    worms.erase(
        std::remove_if(
            worms.begin(),
            worms.end(),
            [worm_id, &removed_idx, this](const auto &worm) {
                removed_idx++;
                if (worm->is(worm_id)) {
                    if (removed_idx < this->current_worm_idx) {
                        this->current_worm_idx--;
                    } else if (removed_idx == (this->worms.size() - 1)) {
                        this->current_worm_idx = 0;
                    }
                    return true;
                }
                return false;
            }
        ),
        worms.end()
    );
}



