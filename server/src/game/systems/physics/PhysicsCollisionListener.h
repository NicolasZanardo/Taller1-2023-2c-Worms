#ifndef TP_WORMS_PHYSICSCOLLISIONLISTENER_H
#define TP_WORMS_PHYSICSCOLLISIONLISTENER_H

#include <map>
#include "box2d/box2d.h"
#include "../../model/worm/Worm.h"
#include "../../model/projectiles/Projectile.h"
#include "user_data_queries/UserDataQuery.h"

class PhysicsCollisionListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

    void _init_beginning_collisions_hit_map();
    void _init_ending_collisions_hit_map();
private:
    typedef void (*hit_function_ptr)(Collidable*, Collidable*);
    typedef std::map< std::pair<std::string,std::string>, hit_function_ptr > HitMap;
    HitMap beginning_hit_map;
    HitMap ending_hit_map;

public:
    explicit PhysicsCollisionListener();
};

#endif
