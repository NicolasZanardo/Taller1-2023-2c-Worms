#include "game_worm_animation_set.h"
#include "sprite_animation.h"

WormAnimationSet::WormAnimationSet(
        GameSprite* idle,
        GameSprite* moving,
        GameSprite* going_upwards,
        GameSprite* falling,
        GameSprite* dead,
        GameSprite* sinking,

        GameSprite* aiming_bazooka,
        GameSprite* aiming_mortar,
        GameSprite* aiming_green_granade,
        GameSprite* aiming_hgrenade,
        GameSprite* aiming_dynamite
    ) :
    worm_state_sprite(),
    aiming_idle_sprite(),
    active_body(falling), 
    aiming_body(aiming_bazooka), 
    state(MovementStateDto::FALLING),
    weapon(WeaponTypeDto::BAZOOKA),
    is_aiming(false)
    {
        worm_state_sprite[MovementStateDto::IDLE]          = std::unique_ptr<GameSprite>(idle);
        worm_state_sprite[MovementStateDto::MOVING]        = std::unique_ptr<GameSprite>(moving);
        worm_state_sprite[MovementStateDto::GOING_UPWARDS] = std::unique_ptr<GameSprite>(going_upwards);
        worm_state_sprite[MovementStateDto::FALLING]       = std::unique_ptr<GameSprite>(falling);
        worm_state_sprite[MovementStateDto::DEAD]          = std::unique_ptr<GameSprite>(dead);
        worm_state_sprite[MovementStateDto::SINKING]       = std::unique_ptr<GameSprite>(sinking);

        aiming_idle_sprite[WeaponTypeDto::BAZOOKA]        = std::unique_ptr<GameSprite>(aiming_bazooka);
        aiming_idle_sprite[WeaponTypeDto::MORTAR]         = std::unique_ptr<GameSprite>(aiming_mortar);
        aiming_idle_sprite[WeaponTypeDto::GREEN_GRENADE]  = std::unique_ptr<GameSprite>(aiming_green_granade);
        aiming_idle_sprite[WeaponTypeDto::HOLY_GRENADE]   = std::unique_ptr<GameSprite>(aiming_hgrenade);
        aiming_idle_sprite[WeaponTypeDto::DYNAMITE]       = std::unique_ptr<GameSprite>(aiming_dynamite);

        for (const auto& [key, val] : aiming_idle_sprite)
            val->set_angle_range(-90,90);
    }

void WormAnimationSet::update_state(MovementStateDto newstate) {
    if (state == newstate)
        return;

    GameSprite* newsprite = worm_state_sprite[newstate].get();

    newsprite->x = active_body->x;
    newsprite->y = active_body->y;
    newsprite->angle = active_body->angle;
    newsprite->flip = active_body->flip;
    newsprite->animation->restart();
    
    active_body = newsprite;
    state = newstate;
}

void WormAnimationSet::aiming(bool is_aiming) {
    this->is_aiming = is_aiming;
}

void WormAnimationSet::update_weapon(WeaponTypeDto newweapon) {
    if (weapon == newweapon)
        return;

    GameSprite* newsprite = aiming_idle_sprite[newweapon].get();

    newsprite->x = aiming_body->x;
    newsprite->y = aiming_body->y;
    newsprite->flip = aiming_body->flip;
    newsprite->angle = aiming_body->angle;
    newsprite->animation->restart();
    
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
