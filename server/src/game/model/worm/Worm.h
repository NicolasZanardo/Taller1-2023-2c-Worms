#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include <map>
#include <memory>
#include "../../../../../common_base/Game/wormDto.h"
#include "WormBody.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../core/Updatable.h"
#include "../core/OnTurnEndedListener.h"
#include "../weapons/Weapon.h"
#include "Health.h"
#include "../core/Collidable.h"
#include "WormFootSensor.h"
#include "../../../../../common_base/Game/ProjectileCountDown.h"

typedef std::map<WeaponTypeDto, std::shared_ptr<Weapon>> WeaponMap;

class InstancesManager;
class WormFootSensor;

class Worm: public Collidable, public Instance, Updatable, OnTurnEndedListener {
private:
    friend class InstancesManager;
    bool is_dead;
    WeaponMap weapons;
    std::shared_ptr<Weapon> & actual_weapon;
    Health health;
    WormFootSensor foot_sensor;
    bool is_on_water;
    int water_death_timer;
    explicit Worm(size_t id);
    WeaponMap create_default_weapons();

public:
    std::shared_ptr<WormBody> body;
    bool has_done_an_ending_turn_action;

    WormDto toWormDto(size_t client_id);

    float X() const;
    float Y() const;
    b2Body* B2Body() const;
    WormFootSensor* get_foot_sensor();

    void update(int it, const int rate) override;
    void on_turn_ended() override;

    // Movement
    void on_sensed_one_new_ground_contact() const;
    void on_sensed_one_ground_contact_ended() const;
    void start_moving_right() const;
    void start_moving_left() const;
    void stop_moving() const;
    void jump_forward() const;
    void jump_backwards() const;
    void sink();

    // Aim
    void start_aiming_up();
    void start_aiming_down();
    void stop_aiming_up();
    void stop_aiming_down();

    // Shot
    void start_shooting();
    void end_shooting();
    std::unique_ptr<CShot> shot_component();

    // Weapon
    void change_weapon(WeaponTypeDto weapon);
    void change_projectile_count_down(ProjectileCountDown time);

    // health
    void heal(float amount);
    void receive_damage(float damage);

    ~Worm() = default;
};

#endif
