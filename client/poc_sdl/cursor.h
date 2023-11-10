#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <cstdint>

class Cursor {
public:
    Cursor() = delete;
    explicit Cursor(uint32_t width_pixels, uint32_t height_pixels,
                            uint32_t width_norm, uint32_t height_norm);
    ~Cursor() = default;

    void setPixelsSize(uint32_t width, uint32_t height);

    uint32_t getPosX() const;
    uint32_t getPosY() const;

    uint32_t getNormPosX() const;
    uint32_t getNormPosY() const;

private:
    uint32_t width_pixels;
    uint32_t height_pixels;
    uint32_t width_norm;
    uint32_t height_norm;
};

#endif  // _CURSOR_H__
