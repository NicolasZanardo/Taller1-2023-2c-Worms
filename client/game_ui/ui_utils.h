#ifndef CLIENT_CLIENT_UTILS_H
#define CLIENT_CLIENT_UTILS_H

class UiUtils {
    static const int PIXEL_CONVERSION_CONSTANT = 25;
    static const int Y_OFFSET = 25;


public:
    static const int WINDOW_HEIGHT = 600; // px
    static const int WINDOW_WIDTH = 800; // px

    static int meters_to_pixels(float meters);
    static int y_meters_pos_to_y_pixel_pos(float y);
    static int x_meters_pos_to_x_pixel_pos(float x);

    // float pixels_to_meters();
};


#endif
