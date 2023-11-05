#ifndef __FRAME_SELECTOR_H__
#define __FRAME_SELECTOR_H__

#include <cstdint>

class FrameSelector {
public:
    FrameSelector() = delete;
    explicit FrameSelector(uint16_t num_frames, uint16_t init_frame);
    ~FrameSelector() = default;

    void advanceFrame();
    void advanceFrames(uint16_t num_frames);
    uint16_t getCurrentFrame() const;

private:
    uint16_t num_frames;  // Total number of frames in the sprite.
    uint16_t current_frame;  // Current animation frame.
};

#endif  // __FRAME_SELECTOR_H__
