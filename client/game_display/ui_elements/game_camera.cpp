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
    return (x-xoffset) * scale;
}
float GameCamera::transform_y(float y) {
    return (yoffset-y) * scale;
}
float GameCamera::transform_w(float w) {
    return w * scale;
}
float GameCamera::transform_h(float h) {
    return h * scale;
}
float GameCamera::px_to_w(int pixels) {
    return (float)pixels / scale;
}
float GameCamera::px_to_h(int pixels) {
    return (float)pixels / scale;
}

void GameCamera::body_to_transform(float x, float y, float w, float h, SDL2pp::Rect& transform) {
    float xx = transform_x(x)- transform_w(w)/2;
    float yy = transform_y(y)- transform_h(h)/2;
    transform.SetX(xx);
    transform.SetY(yy);
    transform.SetW(transform_w(w));
    transform.SetH(transform_h(h));
}

void GameCamera::set_pos(float x, float y) {
    float wscaled = hlf_width / scale;
    xoffset = std::clamp(x - wscaled, 0.0f, room_width - 2*wscaled);

    float hscaled = hlf_height / scale;
    yoffset = std::clamp(y + hscaled, hscaled, room_height-hscaled);
}

void GameCamera::render(SDL2pp::Renderer& renderer, float delta_time) {
    if (target == nullptr)
        return;

    set_pos(target->get_x(), target->get_y());
}

void GameCamera::set_bounds(float width, float height) {
    room_width = width;
    room_height = height;
}
