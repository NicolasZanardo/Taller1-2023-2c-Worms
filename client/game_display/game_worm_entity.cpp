#include "game_worm_entity.h"

WormEntity::WormEntity(GameDisplay& display, WormDto& values) :
    attributes(
        values.client_id, values.entity_id, 
        values.x, values.y, values.is_facing_right, 
        values.life, values.state
    ), animations({
{ MovementStateDto::idle         , display.new_sprite("wwalk" , 1.2f*30, 1.2f*30, 0) },
{ MovementStateDto::falling      , display.new_sprite("wfall" , 1.2f*30, 1.2f*30, 0) },
{ MovementStateDto::going_upwards, display.new_sprite("wjumpu", 1.2f*30, 1.2f*30, 0) },
{ MovementStateDto::moving       , display.new_sprite("widle" , 1.2f*30, 1.2f*30, 0) }
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
    
    MovementStateDto oldstate = attributes.state;
    if (attributes.y > new_values.y) {
        attributes.state = MovementStateDto::falling;
    } else if (attributes.y < new_values.y) {
        attributes.state = MovementStateDto::going_upwards;
    } else if (abs(attributes.x - new_values.x) < 0.001f) {
        attributes.state = MovementStateDto::moving;
    } else {
        attributes.state = MovementStateDto::idle;
    }

    attributes.x = new_values.x;
    attributes.y = new_values.y;
    attributes.life = new_values.life;
    attributes.is_facing_right = new_values.is_facing_right;


    if (attributes.state != oldstate) {
        active_animation->hidden(true);
        active_animation = animations[attributes.state];
        active_animation->hidden(false);
    }
    active_animation->set_pos(
        UiUtils::x_meters_pos_to_x_pixel_pos(attributes.x),
        UiUtils::y_meters_pos_to_y_pixel_pos(attributes.y)
    );
    active_animation->image_flipped(attributes.is_facing_right);
}
