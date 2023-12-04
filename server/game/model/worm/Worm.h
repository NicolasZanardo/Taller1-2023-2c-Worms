#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include <map>
#include <memory>
#include "wormDto.h"
#include "WeaponTypeDto.h"
#include "Updatable.h"
#include "OnTurnEndedListener.h"
#include "Weapon.h"
#include "HealthComponent.h"
#include "Collidable.h"
#include "WormFootSensor.h"
#include "ProjectileCountDown.h"
#include "WeaponCfg.h"
#include "Config.h"
#include "WormCfg.h"
#include "WeaponsComponent.h"
#include "CheatType.h"
#include "CheatManager.h"
#include "GameAction.h"
#include "WormBody.h"

enum class WormState : uint8_t {
    IDLE = 0x00,
    MOVING = 0x01,
    JUMPING = 0x02,
    FALLING = 0x03,
    SINKING = 0x04,
    DEAD = 0x05
};


class InstancesManager;
class WormFootSensor;
class HealthComponent;

class Worm
    : public Collidable, public Instance, Updatable, OnTurnEndedListener, public std::enable_shared_from_this<Worm> {
private:
    friend class InstancesManager;
    friend class HealthComponent;
    friend class WormBody;
    friend class WormCheatBody;

    friend class CheatManager;
    void cheat_movement(bool toggled);
    void cheat_health();
    void cheat_weapon(int new_ammo, float new_damage);

    WormStateDto state;
    std::shared_ptr<WeaponsComponent> weapons_component;
    HealthComponent health;
    CheatManager cheat_manager;

    WormFootSensor foot_sensor;
    bool is_on_water;
    bool has_done_an_ending_turn_action;

    Worm(
        size_t id,
        WormCfg &worm_cfg,
        std::shared_ptr<WeaponsComponent> weapons_component
    );

public:
    std::shared_ptr<WormBody> body;
    WormDto toWormDto(size_t client_id);

    float X() const;

    float Y() const;

    bool is_still() const;

    b2Body *B2Body() const;

    std::shared_ptr<WormBody> get_body() const;

    WormFootSensor *get_foot_sensor();

    void update(int it, const int rate) override;

    void on_turn_ended() override;

    void act(GameAction action);

    bool has_done_ending_turn_action() const;

    // Movement
    void on_sensed_one_new_ground_contact() const;

    void on_sensed_one_ground_contact_ended() const;

    void sink();

    std::unique_ptr<CShot> shot_component();

    // Weapon
    void change_weapon(WeaponTypeDto weapon);

    void change_projectile_count_down(ProjectileCountDown time);

    // health
    void adjust_health_to(float amount);

    void receive_damage(float damage);

    // Cheat
    void toggle_cheat_mode(CheatType type);

    void receive_force(Force& force);

    ~Worm() = default;
};

#endif
