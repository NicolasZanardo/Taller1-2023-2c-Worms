#include "game_sprite.h"
#include <iostream>
#include <math.h>

inline float normalize_angle(float angle) {
    return 360 * (angle < 0) + std::fmod(angle,360);
}

GameSprite::~GameSprite() { }
GameSprite::GameSprite(GameCamera& cam, GameSpriteInfo& info, float width, float height, float angle) :
    cam(cam),
    info(info),
    x(0),y(0),w(width),h(height),
    transform(0,0,0,0),
    offset(width/2, height/2),
    angle(angle), angle_min(0), angle_max(360),
    is_active(true),
    flip(SDL_FLIP_NONE),
    anim_speed(0.000001f),
    anim_progress(0)
    { }

void GameSprite::set_pos(float x, float y) {
    this->x = x;
    this->y = y;
}

void GameSprite::set_size(float width, float heigth) {
    this->w = width;
    this->h = heigth;
}

void GameSprite::set_angle(float angle) {
    float min = angle_min;
    float max = angle_max;
    angle = normalize_angle(angle);

    if (min > max) { // rodea el cero y hay que desfazar angulo y maximo
        max += 360.0f;
        angle += 360.0f;
    }

    angle = angle + (angle < min)*(min-angle) + (angle > max)*(max-angle);
    this->angle = normalize_angle(angle);
}

void GameSprite::set_angle_range(float angle_min, float angle_max) {
    angle_min = normalize_angle(angle_min);
    angle_max = normalize_angle(angle_max);

    if (angle_min > angle_max) { // rodea el cero y hay que desfazar angulo y maximo
        angle_max += 360.0f;
        angle += 360.0f;
    }

    angle = angle + (angle < angle_min)*(angle_min-angle) + (angle > angle_max)*(angle_max-angle);
    this->angle_min = angle_min;
    this->angle = normalize_angle(angle);
    this->angle_max = normalize_angle(angle_max);
}

void GameSprite::image_flipped(bool image_is_flipped) {
    flip = image_is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void GameSprite::hidden(bool is_hidden) {
    is_active = !is_hidden;
}

void GameSprite::render(SDL2pp::Renderer& renderer, float delta_time) {
    if (!is_active) return;
    
    cam.body_to_transform(x,y,w,h,transform);
    offset.SetX(cam.transform_w(w)/2);
    offset.SetY(cam.transform_h(h)/2);

    if (info.frame_count <= 0) {
        renderer.Copy(info.texture,SDL2pp::NullOpt,transform,normalize_angle(-angle),offset,flip);
        
        return;
    }

    update_animation(delta_time);
    if (info.animation == BY_ANGLE)
        renderer.Copy(info.texture, info.image_frame(anim_progress), transform, 0.0, offset, flip);
    else renderer.Copy(info.texture, info.image_frame(anim_progress), transform, normalize_angle(-angle), offset, flip);


    renderer.SetDrawColor(SDL2pp::Color{255,255,255,255});
    renderer.DrawRect(transform);
    renderer.SetDrawColor(SDL2pp::Color{0,0,0,0});
}

void GameSprite::update_animation(float delta_time) {
    if (info.animation == SpriteAnimationType::NONE)
        return;
    
    if (info.animation == SpriteAnimationType::BY_ANGLE) {
        anim_progress = ((float)info.frame_count) * (angle + 270) / (angle_max-angle_min);
        return;
    }

    float true_delta = delta_time * anim_speed * info.frame_speed;
    if (true_delta == 0)
        return;

    anim_progress += true_delta;
    if (anim_progress < info.frame_count && anim_progress >= 0) {
        return;
    }

    // Las correcciones se hacen dentro de un ciclo,
    // por si se lagueo por mas de un ciclo entero de animaciones.
    switch (info.animation) {
        case SpriteAnimationType::LOOP:
            // Se reinicia la animacion manteniando el progreso del servidor.
            // de esta manera todos los clientes van a tener el mismo progreso de animacion, incluso despues de un lag.
            while (anim_progress >= info.frame_count) {
                anim_progress -= info.frame_count;
            }
            break;

        case SpriteAnimationType::REVERSE:
            // Cambiar el sendito de la animacion y retroceder del final, o volver a empezar 
            // El codigo abajo realiza la siguiente desicion:
            //     Si llego al final avanzando, retrocede lo que se paso del ultimo frame.
            while(anim_progress > info.frame_count || anim_progress < 0) {
                anim_progress = (float)info.frame_count - (anim_progress-(float)info.frame_count)*(float)(anim_speed > 0)
                              + (-anim_progress)*(float)(anim_speed < 0);
                anim_speed = -anim_speed;

                // En el caso de que se sincronize perfectamente con la cantidad de frames, este algoritmo entra en un loop infinito, 
                // por lo que lo desfazamos una milesima de progreso de animacion.
                if (anim_progress == 0.0f) {
                    anim_progress = 0.001f;
                }
            }
            break;

        case SpriteAnimationType::FREEZE:
            if (anim_progress > info.frame_count-1)
                anim_progress = info.frame_count-1;
            break;

        case SpriteAnimationType::NONE:
            //TODO: agregar una excepcion
            break;

        case SpriteAnimationType::BY_ANGLE:
            //TODO: agregar una excepcion
            break;
    }
}
