#include "game_worm_animation_set.h"
#include <iostream>

WormAnimationSet::~WormAnimationSet() {
    for (auto [key, val] : worm_state_sprite) {
        delete(val);
    }
    for (auto [key, val] : aiming_idle_sprite) {
        delete(val);
    }
}

WormAnimationSet::WormAnimationSet(
        GameSprite* idle,
        GameSprite* moving,
        GameSprite* going_upwards,
        GameSprite* falling,

        GameSprite* aiming_bazooka,
        GameSprite* aiming_mortar,
        GameSprite* aiming_green_granade
    ) :
    worm_state_sprite({
{ MovementStateDto::IDLE          , idle },
{ MovementStateDto::MOVING        , moving },
{ MovementStateDto::GOING_UPWARDS , going_upwards },
{ MovementStateDto::FALLING       , falling },
{ MovementStateDto::SINKING       , falling } // TODO for now same as falling
    }),
    aiming_idle_sprite({
{ WeaponTypeDto::BAZOOKA       , aiming_bazooka },
{ WeaponTypeDto::MORTAR        , aiming_mortar },
{ WeaponTypeDto::GREEN_GRENADE , aiming_green_granade }
    }),
    active_body(falling), 
    aiming_body(aiming_bazooka), 
    state(MovementStateDto::FALLING),
    weapon(WeaponTypeDto::BAZOOKA),
    is_aiming(false)
    {
        for (auto [key, val] : aiming_idle_sprite)
            val->set_angle_range(-90,90);
    }

void WormAnimationSet::update_state(MovementStateDto newstate) {
    if (state == newstate)
        return;
    
    auto newsprite = worm_state_sprite[newstate];

    newsprite->x = active_body->x;
    newsprite->y = active_body->y;
    newsprite->angle = active_body->angle;
    newsprite->flip = active_body->flip;
    newsprite->anim_progress = 0;
    
    active_body = newsprite;
    state = newstate;
}

void WormAnimationSet::aiming(bool is_aiming) {
    this->is_aiming = is_aiming;
}

void WormAnimationSet::update_weapon(WeaponTypeDto newweapon) {
    if (weapon == newweapon)
        return;

    auto newsprite = aiming_idle_sprite[newweapon];

    newsprite->x = aiming_body->x;
    newsprite->y = aiming_body->y;
    newsprite->flip = aiming_body->flip;
    newsprite->angle = aiming_body->angle;
    newsprite->anim_progress = 0;
    
    aiming_body = newsprite;
    weapon = newweapon;
}

void WormAnimationSet::set_pos(float x, float y) {
    active_body->set_pos(x,y);
    aiming_body->set_pos(x,y);
}

void WormAnimationSet::set_weapon_angle(float angle) {
    aiming_body->set_angle(-angle);
}

void WormAnimationSet::image_flipped(bool image_is_flipped) {
    active_body->image_flipped(image_is_flipped);
    aiming_body->image_flipped(image_is_flipped);
}

void WormAnimationSet::render(SDL2pp::Renderer& renderer, float delta_time) {
    if (is_aiming && state == MovementStateDto::IDLE)
        aiming_body->render(renderer, delta_time);
    else
        active_body->render(renderer, delta_time);
}
