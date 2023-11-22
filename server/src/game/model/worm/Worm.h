#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include <map>
#include <memory>
#include "../../../../../common_base/Game/wormDto.h"
#include "components/WormMovement.h"
#include "components/Weapon.h"
#include "../../../../../common_base/Game/WeaponDto.h"

typedef std::map<WeaponDto, Weapon> WeaponMap;

class InstancesManager;

class Worm: public Instance {
private:
    friend class InstancesManager;
    WeaponMap weapons;
    std::unique_ptr<Weapon> actual_weapon;

    explicit Worm(size_t id, WeaponMap weapons);
    explicit Worm(size_t id);

public:
    std::shared_ptr<WormMovement> movement;

    int health = 100;

    WormDto toWormDto(size_t clientId);

    void start_moving_right();

    void start_moving_left();

    void stop_moving();

    void jump_forward();

    void jump_backwards();

    void start_aiming_up();

    void start_aiming_down();

    void stop_aiming_up();
    void stop_aiming_down();

    void update();
    void on_turn_ended();

};

#endif
