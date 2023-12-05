#include "game_worm_entity.h"
#include "constants.h"

WormEntity::WormEntity(GameDisplay& display, WormDto& values, int color) :
    attributes(
        values.client_id, values.entity_id,
        values.x, values.y, values.angle,
        values.is_facing_right, values.life, values.movement_state,
        values.weapon_hold, values.aiming_angle
    )
    , sprite(display.new_worm_animation(1.0f, 0.0f))
    , color(color)
    , name(display.new_text(
        std::to_string(values.life),
        values.x, values.y + 1,
        TextAlign::center,
        TextLayer::ingame,
        TextType::gametext,
        color
    ))
    { }

void WormEntity::update(WormDto& new_values, bool active) {
    if (attributes.entity_id != new_values.entity_id)
        return;

    attributes.x = new_values.x;
    attributes.y = new_values.y;

    name->set_pos(attributes.x, attributes.y+1);
    if (attributes.life != new_values.life)
       name->update(std::to_string(new_values.life));
    attributes.life = new_values.life;

    sprite->aiming(active);
    sprite->update_weapon(new_values.weapon_hold);
    sprite->update_state(new_values.movement_state);

    sprite->set_pos(new_values.x,new_values.y);
    sprite->image_flipped(new_values.is_facing_right);
    sprite->set_weapon_angle(new_values.aiming_angle);
}

float WormEntity::get_x() {
    return attributes.x;
}

float WormEntity::get_y() {
    return attributes.y;
}
