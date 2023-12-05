#include "DefaultProjectileCountDownChanger.h"

DefaultProjectileCountdownChanger::DefaultProjectileCountdownChanger(int default_countdown)
    : ProjectileCountDownChanger(default_countdown){}

void DefaultProjectileCountdownChanger::change_countdown(int new_countdown) {
    countdown = new_countdown;
}
