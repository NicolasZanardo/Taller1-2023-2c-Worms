add_library( server

    src/client/client_reciever.h
    src/client/client_reciever.cpp
    src/client/client_sender.h
    src/client/client_sender.cpp
    src/client/client.h
    src/client/client.cpp

    src/dumb_client.h
    src/dumb_client.cpp
    src/lobby/host.h
    src/lobby/host.cpp
    src/lobby/waiting_lobby.h
    src/lobby/waiting_lobby.cpp
    src/lobby/client_accepter.h
    src/lobby/client_accepter.cpp

    src/main/server.h
    src/main/server.cpp

        src/game/control/InGameClients.h
        src/game/control/InGameClients.cpp

        src/game/control/GameEngineInstance.h
        src/game/control/GameEngineInstance.cpp
        src/game/control/GameInstance.h
        src/game/control/GameInstance.cpp

        src/game/core/InstancesManager.h
        src/game/core/InstancesManager.cpp
        src/game/core/CollideableTags.h
        src/game/model/core/Instance.h
    src/game/model/core/Instance.cpp
    src/game/model/core/Updatable.h
        src/game/core/Logger.h
        src/game/core/Logger.cpp
        src/game/model/core/OnTurnEndedListener.h
        src/game/model/core/Body.h
        src/game/model/core/Body.cpp
        src/game/model/core/Collidable.h
        src/game/model/worm/WormBody.h
        src/game/model/worm/WormBody.cpp
    src/game/model/worm/Worm.h
    src/game/model/worm/Worm.cpp
    src/game/model/worm/Health.h
    src/game/model/worm/Health.cpp

        src/game/model/weapons/Weapon.h
        src/game/model/weapons/Weapon.cpp
        src/game/model/weapons/Bazooka.h
        src/game/model/weapons/Bazooka.cpp
        src/game/model/weapons/Mortar.h
        src/game/model/weapons/Mortar.cpp
        src/game/model/weapons/GreenGrenade.h
        src/game/model/weapons/GreenGrenade.cpp

        src/game/model/weapons/WeaponRotation.h
        src/game/model/weapons/WeaponRotation.cpp
        src/game/model/projectiles/ProjectileInfo.h
        src/game/model/projectiles/ProjectileInfo.cpp
        src/game/model/projectiles/CShot.h
        src/game/model/projectiles/CShot.cpp
        src/game/model/projectiles/CExplosion.h
        src/game/model/projectiles/CExplosion.cpp
        src/game/model/projectiles/Projectile.h
        src/game/model/projectiles/Projectile.cpp
        src/game/model/projectiles/CountdownProjectile.h
        src/game/model/projectiles/CountdownProjectile.cpp
        src/game/model/projectiles/InstantExplosionProjectile.h
        src/game/model/projectiles/InstantExplosionProjectile.cpp
        src/game/model/projectiles/ProjectileBody.h
        src/game/model/projectiles/ProjectileBody.cpp
        src/game/model/projectiles/ProjectileFactory.h
        src/game/model/projectiles/ProjectileFactory.cpp
        src/game/model/forces/Force.h
        src/game/model/forces/BuoyancyForce.h
        src/game/model/forces/BuoyancyForce.cpp
        src/game/model/forces/ExplosionForce.h
        src/game/model/forces/ExplosionForce.cpp
        src/game/model/forces/WindForce.h
        src/game/model/forces/WindForce.cpp

        src/game/model/worm/WormFootSensor.h
        src/game/model/worm/WormFootSensor.cpp
        src/game/model/collidables/ScenarioWater.h
        src/game/model/collidables/ScenarioWater.cpp
        src/game/model/collidables/ScenarioBeams.h
        src/game/model/collidables/ScenarioBeams.cpp

        src/game/model/game_events/GameWorldEvent.h
        src/game/model/game_events/GameWorldEvent.cpp

        src/game/control/GameNetMessageBehaviour.h
        src/game/control/GameNetMessageBehaviour.cpp

    src/game/scenario/BeamScenarioData.h
    src/game/scenario/WormScenarioData.h
    src/game/scenario/GameScenarioData.h
    src/game/scenario/HardcodedScenarioData.h
    src/game/scenario/ScenarioReader.h
    src/game/scenario/ScenarioReader.cpp

        src/game/systems/turns/TurnSystem.h
        src/game/systems/turns/TurnSystem.cpp
        src/game/systems/turns/WormIdIterator.h
        src/game/systems/turns/WormIdIterator.cpp
        src/game/systems/updatables/UpdatablesSystem.h
        src/game/systems/updatables/UpdatablesSystem.cpp
        src/game/systems/shot/ShotSystem.h
        src/game/systems/shot/ShotSystem.cpp

        src/game/systems/physics/begin_collision_events/BWormFootSensorWGround.h
        src/game/systems/physics/begin_collision_events/BWormFootSensorWGround.cpp
        src/game/systems/physics/begin_collision_events/BProjectileWAny.h
        src/game/systems/physics/begin_collision_events/BProjectileWAny.cpp
        src/game/systems/physics/begin_collision_events/BWaterWWorm.h
        src/game/systems/physics/begin_collision_events/BWaterWWorm.cpp
        src/game/systems/physics/begin_collision_events/BWaterWProjectile.h
        src/game/systems/physics/begin_collision_events/BWaterWProjectile.cpp
        src/game/systems/physics/end_collision_events/EWormFootSensorWGround.h
        src/game/systems/physics/end_collision_events/EWormFootSensorWGround.cpp
        src/game/systems/physics/world_queries/OnExplosionWormsQuery.h
        src/game/systems/physics/world_queries/OnExplosionWormsQuery.cpp
        src/game/systems/physics/world_queries/ExplosionQueryCallback.h
        src/game/systems/physics/world_queries/ExplosionQueryCallback.cpp
        src/game/systems/physics/PhysicsCollisionListener.h
        src/game/systems/physics/PhysicsCollisionListener.cpp
        src/game/systems/physics/PhysicsSystem.h
        src/game/systems/physics/PhysicsSystem.cpp
        src/game/systems/physics/user_data_queries/UserDataQuery.h

        src/game/systems/wind/WindSystem.h
        src/game/systems/wind/WindSystem.cpp


)

add_executable(
    server_app
    server_main.cpp
)

target_link_libraries(server PUBLIC box2d)
target_link_libraries(server_app PUBLIC server)
target_link_libraries(server_app PUBLIC common)
