#ifndef TP_WORMS_CEXPLOSION_H
#define TP_WORMS_CEXPLOSION_H

class CExplosion {
public:
    explicit CExplosion(float max_damage,float radius, float x, float y);
    float max_damage;
    float radius;
    float x;
    float y;
};

#endif //TP_WORMS_CEXPLOSION_H
