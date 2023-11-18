#include "./frame_selector.h"

#include <stdexcept>

FrameSelector::FrameSelector(FrameSelectorMode mode, uint16_t num_frames, uint16_t init_frame)
    : mode(mode)
    , delta(+1)
    , num_frames(num_frames)
    , current_frame(init_frame) {
    if (mode == FrameSelectorMode::BOUNCE) {
        this->advance_frame = &FrameSelector::advanceFrame_bounce;
    } else if (mode == FrameSelectorMode::CIRCULAR) {
        this->advance_frame = &FrameSelector::advanceFrame_circular;
    } else if (mode == FrameSelectorMode::STAY_LAST) {
        this->advance_frame = &FrameSelector::advanceFrame_stayLast;
    } else {
        throw std::invalid_argument("Error: Invalid Mode in FrameSelector.");
    }
}

void FrameSelector::reset() {
    this->current_frame = 0;
}

void FrameSelector::advanceFrame() {
    (this->*(this->advance_frame))();
}

void FrameSelector::advanceFrames(uint16_t num_frames) {
    this->current_frame += num_frames;
    this->current_frame %= this->num_frames;
}

uint16_t FrameSelector::getCurrentFrame() const {
    return this->current_frame;
}

void FrameSelector::advanceFrame_bounce() {
    this->current_frame += delta;
    if ((this->current_frame == 0)
        ||
        (this->current_frame == (this->num_frames - 1))) {
        delta *= -1;
    }
}

void FrameSelector::advanceFrame_circular() {
    this->current_frame += delta;
    this->current_frame %= this->num_frames;
}

void FrameSelector::advanceFrame_stayLast() {
    if (this->current_frame < (this->num_frames - 1)) {
        this->current_frame += delta;
    }
}
