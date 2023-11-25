#include "game_worm_entity.h"
#include "constants.h"
#include "worm_anim_key_mapper.h"

WormEntity::WormEntity(GameDisplay& display, WormDto& values) :
    attributes(
        values.client_id, values.entity_id,
        values.x, values.y, values.angle,
        values.is_facing_right, values.life, values.movement_state,
        values.weapon_hold, values.aiming_angle
    )
    , sprite(display.new_worm_animation(1.0f, 0.0f))
    , is_active(true)
    , name(display.new_text(
        std::to_string(values.entity_id), 
        values.x, values.y + 1, 12,
        TextAlign::center, TextLayer::ingame
    ))
    { }

void WormEntity::update(WormDto& new_values) {
    if (attributes.entity_id != new_values.entity_id)
        return;

    attributes.x = new_values.x;
    attributes.y = new_values.y;

    attributes.life = new_values.life;
    attributes.is_facing_right = new_values.is_facing_right;
    attributes.angle = new_values.angle;
    attributes.weapon_hold = new_values.weapon_hold;
    attributes.movement_state = new_values.movement_state;

    name->set_pos(attributes.x, attributes.y+1);

    sprite->update_weapon(new_values.weapon_hold);
    sprite->update_state(new_values.movement_state);

    sprite->set_pos(new_values.x,new_values.y);
    sprite->image_flipped(new_values.is_facing_right);
    sprite->set_weapon_angle(new_values.aiming_angle);
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
