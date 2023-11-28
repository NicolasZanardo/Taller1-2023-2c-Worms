#include "game_projectile_entity.h"
#include "projectile_sprite_key_mapper.h"

ProjectileEntity::ProjectileEntity(GameDisplay &display, ProjectileDto &values) :
    sprite(display.new_sprite(
        ProjectileSpriteKeyMapper::map(values.type),
        PROJECTILE_RADIUS * 2,
        PROJECTILE_RADIUS * 2
        )
    ), attributes(values.entity_id, values.type, values.x, values.y)
    { }

void ProjectileEntity::update(ProjectileDto &new_values) {
    if (attributes.entity_id != new_values.entity_id)
        return;

    attributes.x = new_values.x;
    attributes.y = new_values.y;
    sprite->set_pos(attributes.x,attributes.y);
    sprite->image_flipped( false); // TODO VIA NETWORK
    sprite->set_angle(0); // TODO Projectile rotation;
}

float ProjectileEntity::get_x() {
    return attributes.x;
}

float ProjectileEntity::get_y() {
    return attributes.y;
}

GameSprite *ProjectileEntity::get_sprite() {
    return sprite;
}
