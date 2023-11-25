#ifndef _CLIENT_GAME_WORM_ANIMATION_SET_H_
#define _CLIENT_GAME_WORM_ANIMATION_SET_H_

#include <SDL2pp/SDL2pp.hh>
#include "networking.h"
#include "game_displayable.h"
#include "game_sprite.h"

class WormAnimationSet : public Displayable {
    std::unordered_map<MovementStateDto, GameSprite*> worm_state_sprite;
    std::unordered_map<WeaponTypeDto, GameSprite*> weapon_state_sprite;
    GameSprite* active_body;
    MovementStateDto state;
    GameSprite* active_weapon;
    WeaponTypeDto weapon;

    public:
    ~WormAnimationSet() override;
    explicit WormAnimationSet(
        GameSprite* idle,
        GameSprite* moving,
        GameSprite* going_upwards,
        GameSprite* falling,
        GameSprite* bazooka,
        GameSprite* mortar,
        GameSprite* green_granade
    );

    void update_state(MovementStateDto newstate);
    void update_weapon(WeaponTypeDto newweapon);

    void set_pos(float x, float y);
    void set_weapon_angle(float angle);
    void image_flipped(bool image_is_flipped);
    void render(SDL2pp::Renderer& renderer, float delta_time) override;
};

#endif