#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include <map>
#include <memory>
#include "wormDto.h"
#include "WormBody.h"
#include "WeaponTypeDto.h"
#include "Updatable.h"
#include "OnTurnEndedListener.h"
#include "Weapon.h"
#include "Health.h"
#include "Collidable.h"
#include "WormFootSensor.h"
#include "ProjectileCountDown.h"
#include "WeaponCfg.h"
#include "Config.h"
#include "WormCfg.h"

typedef std::map<WeaponTypeDto, std::shared_ptr<Weapon>> WeaponMap;

class InstancesManager;
class WormFootSensor;

class Worm: public Collidable, public Instance, Updatable, OnTurnEndedListener {
private:
    friend class InstancesManager;
    int WATER_DEATH_TIME = 2000;
    bool is_dead;
    WeaponMap weapons;
    std::shared_ptr<Weapon> actual_weapon;
    Health health;
    WormFootSensor foot_sensor;
    bool is_on_water;
    int water_death_timer;
    bool has_done_an_ending_turn_action;

    Worm(size_t id, WormCfg &worm_cfg, Config<WeaponCfg> &weapons_cfg);
    static WeaponMap create_default_weapons(Config<WeaponCfg> &weapons_cfg);
public:
    std::shared_ptr<WormBody> body;

    WormDto toWormDto(size_t client_id);

    float X() const;
    float Y() const;
    b2Body* B2Body() const;
    WormFootSensor* get_foot_sensor();

    void update(int it, const int rate) override;
    void on_turn_ended() override;

    bool has_done_ending_turn_action() const;

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
    void adjust_health_to(float amount);
    void receive_damage(float damage);

    ~Worm() = default;
};

#endif
