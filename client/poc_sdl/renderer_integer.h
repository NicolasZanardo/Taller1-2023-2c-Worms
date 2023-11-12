#ifndef __RENDERER_INTEGER_H__
#define __RENDERER_INTEGER_H__

#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "sprites_manager.h"

enum class IntegerAlignmentMode : uint8_t {
    LEFT,
    RIGHT,
    CENTER
};

class RendererInteger {
public:
    RendererInteger() = delete;
    explicit RendererInteger(SpritesManager& sprites_manager, const std::string& id, IntegerAlignmentMode mode);
    ~RendererInteger() = default;

    void render(uint32_t number, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

private:
    void calculatePosition_left();
    void calculatePosition_right();
    void calculatePosition_center();

    SpritesManager* sprites_manager;
    std::string id;
    std::vector<uint8_t> digits_buffer;
    SDL_RendererFlip flip;

    IntegerAlignmentMode mode;
    void (RendererInteger::*calculate_position)();
    uint32_t len;
    uint16_t x;
    uint16_t width;
};

#endif  // __RENDERER_INTEGER_H__
