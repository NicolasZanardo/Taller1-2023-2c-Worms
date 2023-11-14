#include "drawable_integer.h"

#include <stdexcept>

DrawableInteger::DrawableInteger(SpritesManager& sprites_manager, const std::string& id, IntegerAlignmentMode mode)
    : sprites_manager(&sprites_manager), id(id), flip(SDL_FLIP_NONE), mode(mode) {
    if (mode == IntegerAlignmentMode::LEFT) {
        this->calculate_position = &DrawableInteger::calculatePosition_left;
    } else if (mode == IntegerAlignmentMode::RIGHT) {
        this->calculate_position = &DrawableInteger::calculatePosition_right;
    } else if (mode == IntegerAlignmentMode::CENTER) {
        this->calculate_position = &DrawableInteger::calculatePosition_center;
    } else {
        throw std::invalid_argument("Error: Invalid Mode in IntegerAlignment.");
    }
}

void DrawableInteger::render(uint32_t number, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    this->digits_buffer.clear();
    std::string str_num = std::to_string(number);

    for (char digit_char : str_num) {
        this->digits_buffer.push_back(static_cast<uint8_t>(digit_char - '0'));
    }

    this->len = this->digits_buffer.size();
    this->x = x;
    this->width = width;
    (this->*(this->calculate_position))();

    for (uint8_t digit : this->digits_buffer) {
        std::cout << static_cast<uint16_t>(digit) << '-';;
        this->sprites_manager->renderSprite(
            this->id,
            digit,
            SDL2pp::Rect(this->x, y, width, height),
            flip
        );

        this->x += width;
    }
}

void DrawableInteger::calculatePosition_left() {
    // do nothing.
}

void DrawableInteger::calculatePosition_right() {
    this->x -= this->len*this->width;
}

void DrawableInteger::calculatePosition_center() {
    this->x -= ((this->len*this->width) / 2);
}
