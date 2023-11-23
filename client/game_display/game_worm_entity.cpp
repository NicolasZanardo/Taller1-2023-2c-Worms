#include "game_worm_entity.h"
#include "constants.h"

WormEntity::WormEntity(GameDisplay& display, WormDto& values) :
    attributes(
        values.client_id, values.entity_id, 
        values.x, values.y, values.angle, 
        values.is_facing_right, values.life, values.state,
        values.weapon_hold, values.aiming_angle
    ), animations({
{ MovementStateDto::idle          , display.new_sprite("widle"  , WORM_SIZE, WORM_SIZE, 0) },
{ MovementStateDto::falling       , display.new_sprite("wfall"  , WORM_SIZE, WORM_SIZE, 0) },
{ MovementStateDto::going_upwards , display.new_sprite("wjumpu" , WORM_SIZE, WORM_SIZE, 0) },
{ MovementStateDto::moving        , display.new_sprite("wwalk"  , WORM_SIZE, WORM_SIZE, 0) },
{ MovementStateDto::moving        , display.new_sprite("w_bazooka"  , WORM_SIZE, WORM_SIZE, 0) },
{ MovementStateDto::moving        , display.new_sprite("w_green_grenade"  , WORM_SIZE, WORM_SIZE, 0) },
{ MovementStateDto::moving        , display.new_sprite("w_mortar"  , WORM_SIZE, WORM_SIZE, 0) }
    }), active_animation(animations[MovementStateDto::idle])
    {
        animations[MovementStateDto::idle         ]->hidden(false);
        animations[MovementStateDto::falling      ]->hidden(true);
        animations[MovementStateDto::going_upwards]->hidden(true);
        animations[MovementStateDto::moving       ]->hidden(true);
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
    attributes.aiming_angle = new_values.aiming_angle;
    attributes.weapon_hold = new_values.weapon_hold;

    if (attributes.state != new_values.state) {
        active_animation->hidden(true);
        active_animation = animations[new_values.state];
        active_animation->hidden(false);
    }
    active_animation->set_pos(attributes.x,attributes.y);
    active_animation->image_flipped(attributes.is_facing_right);
    active_animation->set_angle(attributes.aiming_angle);

    attributes.state = new_values.state;
}

float WormEntity::get_x() {
    return attributes.x;
}

float WormEntity::get_y() {
    return attributes.y;
}
