#ifndef TP_WORMS_WORMCFG_H
#define TP_WORMS_WORMCFG_H

struct WormCfg {

    struct Health {
        float default_health;
        float disadvantage_health;
    };

    struct Body {
        float speed;
        float forward_jump_height;
        float forward_jump_reach;
        float backwards_jump_height;
        float backwards_jump_reach;
        float size;
        float restitution;
        float density;
    };

    Health health;
    Body body;

};

#endif //TP_WORMS_WORMCFG_H
