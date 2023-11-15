#ifndef __FRAME_SELECTOR_H__
#define __FRAME_SELECTOR_H__

#include <cstdint>

enum class FrameSelectorMode : uint8_t {
    BOUNCE = 0x00,
    CIRCULAR = 0x01,
    STAY_LAST = 0x02
};

class FrameSelector {
public:
    FrameSelector() = delete;
    explicit FrameSelector(FrameSelectorMode mode, uint16_t num_frames, uint16_t init_frame);
    ~FrameSelector() = default;

    FrameSelector(const FrameSelector&) = default;
    FrameSelector& operator=(const FrameSelector&) = default;

    void advanceFrame();
    void advanceFrames(uint16_t num_frames);
    uint16_t getCurrentFrame() const;

private:
    void advanceFrame_bounce();
    void advanceFrame_circular();
    void advanceFrame_stayLast();

    FrameSelectorMode mode;
    int8_t delta;
    uint16_t num_frames;  // Total number of frames in the sprite.
    uint16_t current_frame;  // Current animation frame.
    void (FrameSelector::*advance_frame)();
};

#endif  // __FRAME_SELECTOR_H__
