#ifndef TP_WORMS_GAME_PROJECTILE_ENTITY_H
#define TP_WORMS_GAME_PROJECTILE_ENTITY_H

#include "game_text_display.h"
#include "Game/ProjectileDto.h"
#include "game_sprite.h"
#include "game_display.h"

class ProjectileEntity : public CameraTarget {
    GameSprite* sprite;
    ProjectileDto attributes;
public:

    ProjectileEntity(GameDisplay& display, ProjectileDto& values);
    void update(ProjectileDto& new_values);

    float get_x() override;
    float get_y() override;
    GameSprite* get_sprite();
};

#endif
