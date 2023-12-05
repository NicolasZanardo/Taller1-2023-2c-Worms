#ifndef TP_WORMS_CLIENTTURN_H
#define TP_WORMS_CLIENTTURN_H

#include <vector>
#include <memory>
#include "Worm.h"
#include <iostream>

class ClientTurn {
public:
    int client_id;
    int current_worm_idx = 0;
    std::vector<std::shared_ptr<Worm>> worms;

    explicit ClientTurn(int client_id);

    std::shared_ptr<Worm> get_current_worm();

    void advance_next_worm();
    void remove(int worm_id);
};



#endif //TP_WORMS_CLIENTTURN_H
