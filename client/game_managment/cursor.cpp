#include "cursor.h"

#include <SDL2pp/SDL2pp.hh>

Cursor::Cursor(uint32_t width_pixels, uint32_t height_pixels, uint32_t width_norm, uint32_t height_norm)
    : width_pixels(width_pixels), height_pixels(height_pixels)
    , width_norm(width_norm), height_norm(height_norm) {}

void Cursor::setPixelsSize(uint32_t width, uint32_t height) {
    this->width_pixels = width;
    this->height_pixels = height;
}

uint32_t Cursor::getPosX() const {
    int x;
    SDL_GetMouseState(&x, nullptr);
    return static_cast<uint32_t>(x);
}

uint32_t Cursor::getPosY() const {
    int y;
    SDL_GetMouseState(nullptr, &y);

    return static_cast<uint32_t>(y);
}

uint32_t Cursor::getNormPosX() const {
    return this->getPosX() * this->width_norm / this->width_pixels; 
}

uint32_t Cursor::getNormPosY() const {
    return this->getPosY() * this->height_norm / this->height_pixels;
}
