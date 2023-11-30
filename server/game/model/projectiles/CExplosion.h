#ifndef TP_WORMS_CEXPLOSION_H
#define TP_WORMS_CEXPLOSION_H

class CExplosion {
public:
    CExplosion(
        float max_damage,
        float damage_radius,
        float x,
        float y
    ) :
        max_damage(max_damage), radius(damage_radius), x(x), y(y) {}

    float max_damage;
    float radius;
    float x;
    float y;
};

#endif //TP_WORMS_CEXPLOSION_H
