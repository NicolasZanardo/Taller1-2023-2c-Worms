#ifndef TP_WORMS_PROJECTILECOUNTDOWNCHANGER_H
#define TP_WORMS_PROJECTILECOUNTDOWNCHANGER_H

class ProjectileCountDownChanger {
protected:
    int countdown;

    explicit ProjectileCountDownChanger(int default_countdown) : countdown(default_countdown) {};
public:
    virtual void change_countdown(int new_countdown) = 0;

    int get_projectile_countdown() { return countdown; };

    virtual ~ProjectileCountDownChanger() = default;
};

#endif
