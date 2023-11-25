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
        src/game/core/ServerConstants.h
    src/game/model/core/Instance.h
    src/game/model/core/Instance.cpp
    src/game/model/core/Updatable.h
        src/game/core/Logger.h
        src/game/core/Logger.cpp
        src/game/model/core/OnTurnEndedListener.h
        src/game/model/core/Body.h
        src/game/model/core/Body.cpp
        src/game/model/worm/WormBody.h
        src/game/model/worm/WormBody.cpp
    src/game/model/worm/Worm.h
    src/game/model/worm/Worm.cpp
    src/game/model/worm/Health.h
    src/game/model/worm/Health.cpp

        src/game/model/weapons/Weapon.h
        src/game/model/weapons/Weapon.cpp
        src/game/model/weapons/Damage.h
        src/game/model/weapons/Damage.cpp
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
        src/game/model/projectiles/Projectile.h
        src/game/model/projectiles/Projectile.cpp
        src/game/model/projectiles/ProjectileBody.h
        src/game/model/projectiles/ProjectileBody.cpp
        src/game/model/projectiles/Explosion.h
        src/game/model/projectiles/Explosion.cpp

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
        src/game/systems/instances/InstancesSystem.h
        src/game/systems/instances/InstancesSystem.cpp
        src/game/systems/shot/ShotSystem.h
        src/game/systems/shot/ShotSystem.cpp

        src/game/systems/physics/CollisionEvent.h
        src/game/systems/physics/begin_contact_events/BWormWithGround.h
        src/game/systems/physics/begin_contact_events/BWormWithGround.cpp
        src/game/systems/physics/begin_contact_events/BProjectileWithAny.h
        src/game/systems/physics/begin_contact_events/BProjectileWithAny.cpp
        src/game/systems/physics/end_contact_events/EWormWithGround.h
        src/game/systems/physics/end_contact_events/EWormWithGround.cpp
        src/game/systems/physics/raycast_callbacks/OnProjectileExplosionRayCast.h
        src/game/systems/physics/raycast_callbacks/OnProjectileExplosionRayCast.cpp
        src/game/systems/physics/PhysicsCollisionListener.h
        src/game/systems/physics/PhysicsCollisionListener.cpp
        src/game/systems/physics/PhysicsSystem.h
        src/game/systems/physics/PhysicsSystem.cpp
        src/game/systems/physics/fixture_queries/FixtureQueries.h

)

add_executable(
    server_app
    server_main.cpp
)

target_link_libraries(server PUBLIC box2d)
target_link_libraries(server_app PUBLIC server)
target_link_libraries(server_app PUBLIC common)
