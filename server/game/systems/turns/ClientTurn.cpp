#include "ClientTurn.h"

ClientTurn::ClientTurn(int client_id) :
    client_id(client_id), worms() {}

std::shared_ptr<Worm> ClientTurn::get_current_worm() {
    try {
        // std::cout << "Returning the worm with id: ";
        return worms[current_worm_idx];
    } catch (...) {
        throw std::runtime_error("Inedx out of worms bounds\n");
    }
};

void ClientTurn::advance_next_worm() {
    // If current was last worm, and it was removed, current index should go to beginning
    if (current_worm_idx >= worms.size()) {
        current_worm_idx = 0;
        // std::cout << "Current worm index was last and now its 0"<< std::endl;
    } else {
        // std::cout << "Current worm index was: " << current_worm_idx << std::endl;
        current_worm_idx++;
        if (current_worm_idx >= worms.size()) {
            current_worm_idx = 0;
        }
    }
    // std::cout << "Now current worm index is: " << current_worm_idx << std::endl;
}

/*
curr_cli_idx = 1
[1, 2]

curr_wor = 1[1, 4] |
[3, 2]
curr_wor = 0
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



