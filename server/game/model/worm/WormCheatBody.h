#ifndef TP_WORMS_WORMCHEATBODY_H
#define TP_WORMS_WORMCHEATBODY_H


#include "WormBodyComponent.h"
#include "WormBody.h"

class WormCheatBody : public WormBodyComponent {
public:

    WormCheatBody(b2World &world, b2Body *body, WormCfg &worm_cfg);
    explicit WormCheatBody(std::shared_ptr<WormBodyComponent> other);

    char facing_direction_sign() const override;

    void on_sensed_one_new_ground_contact() override;

    void on_sensed_one_ground_contact_ended() override;

    void start_moving_right() override;

    void start_moving_left() override;

    void stop_moving() override;

    void jump_forward() override;

    void jump_backwards() override;

    void sink() override;

    void update(const std::shared_ptr<Worm> &worm) override;

    void on_turn_ended() override;

    void receive(Force &force) override;

};
#endif //TP_WORMS_WORMCHEATBODY_H
