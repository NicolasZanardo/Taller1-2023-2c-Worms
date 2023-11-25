#include "game_worm_animation_set.h"

WormAnimationSet::~WormAnimationSet() {
    for (auto [key, val] : worm_state_sprite) {
        delete(val);
    }
    for (auto [key, val] : weapon_state_sprite) {
        delete(val);
    }
 }

WormAnimationSet::WormAnimationSet(
        GameSprite* idle,
        GameSprite* moving,
        GameSprite* going_upwards,
        GameSprite* falling,
        GameSprite* bazooka,
        GameSprite* mortar,
        GameSprite* green_granade
    ) :
    worm_state_sprite({
{ MovementStateDto::IDLE          , idle },
{ MovementStateDto::MOVING        , moving },
{ MovementStateDto::GOING_UPWARDS , going_upwards },
{ MovementStateDto::FALLING       , falling }
    }),
    weapon_state_sprite({
{ WeaponTypeDto::BAZOOKA       , bazooka },
{ WeaponTypeDto::MORTAR        , mortar },
{ WeaponTypeDto::GREEN_GRENADE , green_granade }
    }),
    active_body(falling), state(MovementStateDto::FALLING),
    active_weapon(bazooka), weapon(WeaponTypeDto::BAZOOKA)
    { }

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
}
void WormAnimationSet::update_weapon(WeaponTypeDto newweapon) {
    if (weapon == newweapon)
        return;
    
    auto newsprite = weapon_state_sprite[newweapon];

    newsprite->x = active_weapon->x;
    newsprite->y = active_weapon->y;
    newsprite->angle = active_weapon->angle;
    newsprite->flip = active_weapon->flip;
    
    active_weapon = newsprite;
}

void WormAnimationSet::set_pos(float x, float y) {
    active_body->set_pos(x,y);
    active_weapon->set_pos(x,y);
}

void WormAnimationSet::set_weapon_angle(float angle) {
    active_weapon->set_angle(angle);
}

void WormAnimationSet::image_flipped(bool image_is_flipped) {
    active_body->image_flipped(image_is_flipped);
    active_weapon->image_flipped(image_is_flipped);
}

void WormAnimationSet::render(SDL2pp::Renderer& renderer, float delta_time) {
    active_body->render(renderer, delta_time);
    active_weapon->render(renderer, delta_time);
}
