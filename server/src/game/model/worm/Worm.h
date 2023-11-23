#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include <map>
#include <memory>
#include "../../../../../common_base/Game/wormDto.h"
#include "WormMovement.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../core/Updatable.h"
#include "../core/OnTurnEndedListener.h"
#include "../weapons/Weapon.h"

typedef std::map<WeaponTypeDto, std::shared_ptr<Weapon>> WeaponMap;

class InstancesManager;

class Worm: public Instance, Updatable, OnTurnEndedListener {
private:
    friend class InstancesManager;
    WeaponMap weapons;
    std::shared_ptr<Weapon> & actual_weapon;

    explicit Worm(size_t id);
    static WeaponMap create_default_weapons();

public:
    std::shared_ptr<WormMovement> movement;
    bool has_done_an_ending_turn_action;

    int health = 100;

    WormDto toWormDto(size_t clientId);

    float X() const;
    float Y() const;

    void start_moving_right() const;

    void start_moving_left() const;

    void stop_moving() const;

    void jump_forward() const;

    void jump_backwards() const;

    void start_aiming_up();

    void start_aiming_down();

    void stop_aiming_up();
    void stop_aiming_down();
    void start_shooting();
    void end_shooting();

    void change_weapon(WeaponTypeDto weapon);

    std::unique_ptr<Shot> shot_component();

    void update() override;
    void on_turn_ended() override;

};

#endif
