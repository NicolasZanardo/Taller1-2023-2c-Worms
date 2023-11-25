#include "game_worm_entity.h"
#include "constants.h"
#include "worm_anim_key_mapper.h"

WormEntity::WormEntity(GameDisplay& display, WormDto& values) :
    attributes(
        values.client_id, values.entity_id,
        values.x, values.y, values.angle,
        values.is_facing_right, values.life, values.movement_state,
        values.weapon_hold, values.aiming_angle
    ), animations({
{ WormAnimKey::MOVING        , display.new_sprite("wwalk"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::IDLE          , display.new_sprite("widle"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::IDLE_BAZOOKA        , display.new_sprite("w_bazooka"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::IDLE_MORTAR        , display.new_sprite("w_mortar"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::IDLE_GREEN_GRENADE        , display.new_sprite("w_green_grenade"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::FALLING       , display.new_sprite("wfall"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::FALLING_BAZOOKA       , display.new_sprite("wfall"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::FALLING_MORTAR       , display.new_sprite("wfall"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::FALLING_GREEN_GRENADE       , display.new_sprite("wfall"  , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::JUMPING , display.new_sprite("wjumpu" , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::JUMPING_BAZOOKA , display.new_sprite("wjumpu" , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::JUMPING_MORTAR , display.new_sprite("wjumpu" , WORM_SIZE, WORM_SIZE, 0) },
{ WormAnimKey::JUMPING_GREEN_GRENADE , display.new_sprite("wjumpu" , WORM_SIZE, WORM_SIZE, 0) },
    }), active_animation(animations[WormAnimKey::IDLE]),
    is_active(true)
    {
        animations[WormAnimKey::IDLE         ]->hidden(false);
        animations[WormAnimKey::IDLE_BAZOOKA         ]->hidden(true);
        animations[WormAnimKey::IDLE_MORTAR         ]->hidden(true);
        animations[WormAnimKey::IDLE_GREEN_GRENADE         ]->hidden(true);
        animations[WormAnimKey::FALLING      ]->hidden(true);
        animations[WormAnimKey::FALLING_BAZOOKA      ]->hidden(true);
        animations[WormAnimKey::FALLING_MORTAR      ]->hidden(true);
        animations[WormAnimKey::FALLING_GREEN_GRENADE      ]->hidden(true);
        animations[WormAnimKey::JUMPING]->hidden(true);
        animations[WormAnimKey::JUMPING_BAZOOKA]->hidden(true);
        animations[WormAnimKey::JUMPING_MORTAR]->hidden(true);
        animations[WormAnimKey::JUMPING_GREEN_GRENADE]->hidden(true);
        animations[WormAnimKey::MOVING       ]->hidden(true);
    }

void WormEntity::update(WormDto& new_values) {
    if (attributes.entity_id != new_values.entity_id)
        return;

    //const float tolerance = 0.05f;
    //MovementStateDto oldstate = attributes.state;
    //if ((attributes.y - new_values.y) > tolerance) {
    //    attributes.state = MovementStateDto::falling;
    //} else if ((attributes.y - new_values.y) < -tolerance) {
    //    attributes.state = MovementStateDto::going_upwards;
    //} else if (abs(attributes.x - new_values.x) > tolerance) {
    //    attributes.state = MovementStateDto::moving;
    //} else {
    //    attributes.state = MovementStateDto::idle;
    //}

    attributes.x = new_values.x;
    attributes.y = new_values.y;

    attributes.life = new_values.life;
    attributes.is_facing_right = new_values.is_facing_right;
    attributes.angle = new_values.angle;
    attributes.weapon_hold = new_values.weapon_hold;
    if (attributes.movement_state != new_values.movement_state) {
        active_animation->hidden(true);
        active_animation = animations[WormAnimKeyMapper::get_anim_key(new_values.movement_state, new_values.weapon_hold)];
        active_animation->hidden(false);
    }
    active_animation->set_pos(attributes.x,attributes.y);
    active_animation->image_flipped(attributes.is_facing_right);
    active_animation->set_angle(attributes.angle);
    attributes.movement_state = new_values.movement_state;
}

void WormEntity::destroy() {
    is_active = false;
}

float WormEntity::get_x() {
    return attributes.x;
}

float WormEntity::get_y() {
    return attributes.y;
}
