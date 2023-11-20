#include "game_camera.h"
#include <iostream>

GameCamera::GameCamera(float width, float height, float scale) :
    hlf_width(width / 2.0f),
    hlf_height(height / 2.0f),
    xoffset(- hlf_width / scale), 
    yoffset(hlf_height / scale), 
    scale(scale),
    target(nullptr) 
    { }


void GameCamera::set_target(CameraTarget* target) {
    this->target = target;
}

    
float GameCamera::transform_x(float x) {
    return x * scale - xoffset * scale;
}
inline float GameCamera::transform_y(float y) {
    return (yoffset-y) * scale;
}
inline float GameCamera::transform_w(float w) {
    return w * scale;
}
inline float GameCamera::transform_h(float h) {
    return h * scale;
}

void GameCamera::body_to_transform(const SDL2pp::Rect& body, SDL2pp::Rect& transform) {
    float x = transform_x(body.GetX());
    float y = transform_y(body.GetY());
    float w = transform_w(body.GetW());
    float h = transform_h(body.GetH());

    transform.SetX(x);
    transform.SetY(y);
    transform.SetW(w);
    transform.SetH(h);
    
    std::cout << "draw transform("
        << transform.GetX() << "," 
        << transform.GetY() << "," 
        << transform.GetX2() << "," 
        << transform.GetY2() << ")\n";
}

void GameCamera::hidden(bool is_hidden) { }
void GameCamera::set_angle(float angle) { }
void GameCamera::image_flipped(bool image_is_flipped) { }

void GameCamera::set_pos(float x, float y) {
    xoffset = x - hlf_width / scale;
    yoffset = y + hlf_height / scale;

    std::cout << "CAM NEW POS(" << xoffset << "," << yoffset << ")\n";
}


void GameCamera::render(SDL2pp::Renderer& renderer, float delta_time) {
    if (target == nullptr)
        return;

    set_pos(target->get_x(), target->get_y());
}
