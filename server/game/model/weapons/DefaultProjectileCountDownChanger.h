#ifndef TP_WORMS_DEFAULTPROJECTILECOUNTDOWNCHANGER_H
#define TP_WORMS_DEFAULTPROJECTILECOUNTDOWNCHANGER_H

#include "ProjectileCountDownChanger.h"

class DefaultProjectileCountdownChanger : public ProjectileCountDownChanger {
public:
    explicit DefaultProjectileCountdownChanger(int default_countdown);

    void change_countdown(int new_countdown) override;
};

#endif
