#ifndef _CLIENT_GAME_WORM_ANIMATION_SET_H_
#define _CLIENT_GAME_WORM_ANIMATION_SET_H_

#include <memory>
#include <unordered_map>
#include <SDL2pp/SDL2pp.hh>
#include "networking.h"
#include "game_displayable.h"
#include "game_sprite.h"

class WormAnimationSet : public Displayable {
    std::unordered_map<WormStateDto, std::unique_ptr<GameSprite>> worm_state_sprite;
    std::unordered_map<WeaponTypeDto, std::unique_ptr<GameSprite>> aiming_idle_sprite;
    GameSprite* active_body;
    GameSprite* aiming_body;
    WormStateDto state;
    WeaponTypeDto weapon;
    bool is_aiming;

    public:
    explicit WormAnimationSet(
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
    );

    void update_state(WormStateDto newstate);
    void update_weapon(WeaponTypeDto newweapon);

    void aiming(bool is_aiming);
    void set_pos(float x, float y);
    void set_weapon_angle(float angle);
    void image_flipped(bool image_is_flipped);
    void render(SDL2pp::Renderer& renderer, float delta_time) override;
};

#endif