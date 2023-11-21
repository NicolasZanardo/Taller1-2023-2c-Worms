#ifndef _CLIENT_GAME_CAMERA_H_
#define _CLIENT_GAME_CAMERA_H_

#include "constants.h"
#include <SDL2pp/SDL2pp.hh>
#include "game_displayable.h"

struct CameraTarget {
    virtual float get_x() = 0;
    virtual float get_y() = 0;
};

class GameCamera : public Displayable {
    float hlf_width;
    float hlf_height;
    float xoffset;
    float yoffset;

    float scale;
    CameraTarget* target;

    public:
    GameCamera(float width, float height, float scale);
    ~GameCamera() {}
    void set_target(CameraTarget* target);

    float transform_x(float x);
    float transform_y(float y);
    float transform_w(float w);
    float transform_h(float h);

    void body_to_transform(float x, float y, float w, float h, SDL2pp::Rect& transform);

    void set_pos(float x, float y);
    void render(SDL2pp::Renderer& renderer, float delta_time) override;
};
#endif