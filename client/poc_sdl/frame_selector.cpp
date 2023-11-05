#include "./frame_selector.h"

FrameSelector::FrameSelector(uint16_t num_frames, uint16_t init_frame)
    : num_frames(num_frames)
    , current_frame(init_frame) {}

void FrameSelector::advanceFrame() {
    this->current_frame++;
    this->current_frame %= this->num_frames;
}

void FrameSelector::advanceFrames(uint16_t num_frames) {
    this->current_frame += num_frames;
    this->current_frame %= this->num_frames;
}

uint16_t FrameSelector::getCurrentFrame() const {
    return this->current_frame;
}
