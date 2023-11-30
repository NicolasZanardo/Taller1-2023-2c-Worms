#include "ui_utils.h"

int UiUtils::meters_to_pixels(float meters) {
    return meters * PIXEL_CONVERSION_CONSTANT;
}

int UiUtils::y_meters_pos_to_y_pixel_pos(float y) {
     return (WINDOW_HEIGHT) - meters_to_pixels(y);
}

int UiUtils::x_meters_pos_to_x_pixel_pos(float x) {
    return meters_to_pixels(x);
}

