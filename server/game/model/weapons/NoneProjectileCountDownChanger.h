#ifndef TP_WORMS_NONEPROJECTILECOUNTDOWNCHANGER_H
#define TP_WORMS_NONEPROJECTILECOUNTDOWNCHANGER_H

#include "ProjectileCountDownChanger.h"

class NoneProjectileCountDownChanger : public ProjectileCountDownChanger {
public:
    explicit NoneProjectileCountDownChanger(int default_countdown);

    void change_countdown(int new_countdown) override;
};


#endif //TP_WORMS_NONEPROJECTILECOUNTDOWNCHANGER_H
