#ifndef SERVER_WORM_MOVEMENT_H
#define SERVER_WORM_MOVEMENT_H

#include "box2d/box2d.h"
#include "wormDto.h"
#include "Body.h"
#include "WormCfg.h"
#include "WormBodyComponent.h"

class Worm;

class WormBody: public WormBodyComponent {
public:

    WormBody(b2World&  world, b2Body* body, WormCfg &worm_cfg);
    explicit WormBody(std::shared_ptr<WormBodyComponent> other);

    char facing_direction_sign() const override;

    void on_sensed_one_new_ground_contact() override;
    void on_sensed_one_ground_contact_ended() override;

    void start_moving_right() override;

    void start_moving_left() override;

    void stop_moving() override;

    void jump_forward() override;

    void jump_backwards() override;

    void sink() override;

    void update(const std::shared_ptr<Worm>& worm) override;
    void on_turn_ended() override;

};

#endif // SERVER_WORM_MOVEMENT_H
