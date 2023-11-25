#ifndef TP_WORMS_DAMAGE_H
#define TP_WORMS_DAMAGE_H

class Damage {
    const float damage;
    const float radius;
public:
    Damage(float damage, float radius);
    Damage(Damage &&other) noexcept = default;

    float Radius() const;
    float Amount() const;

};


#endif
