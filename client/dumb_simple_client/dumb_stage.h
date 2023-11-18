#ifndef CLIENT_DUMB_STAGE_H_
#define CLIENT_DUMB_STAGE_H_

#include <map>
#include <cstdint>
#include "one_worm_to_rule_them_all.h"

struct TheStage {
    const float width;
    const float height;

    const float scale;
    const float xoffset;
    const float yoffset;
    std::map<int, TheWorm*> worms; // worm por entity_id

    TheStage(float width, float height) : 
        width(width),
        height(height),
        scale(700/width < 500/height ? 700/width : 500/height),
        xoffset(50),yoffset(50),
        worms()
        {

        }
    
    ~TheStage() {
        for (auto [entity_id, worm] : worms) {
            delete(worm);
        }
    }

    float localize_x(const float webX) const {
        return webX * scale + xoffset;
    }

    float localize_y(const float webY) const {
        return (height-webY) * scale + yoffset;
    }
};
#endif
