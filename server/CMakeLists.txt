add_executable(
    server_app
    server_main.cpp

    main/server.h
    main/server.cpp
    main/dumb_client.h
    main/dumb_client.cpp

        main/client/server_client_reciever.h
        main/client/server_client_reciever.cpp
        main/client/server_client_sender.h
        main/client/server_client_sender.cpp
        main/client/server_client.h
        main/client/server_client.cpp
        main/client/server_client_accepter.h
        main/client/server_client_accepter.cpp

    main/lobby/host.h
    main/lobby/host.cpp
    main/lobby/waiting_lobby.h
    main/lobby/waiting_lobby.cpp

    main/lobby/id_generator.cpp
    main/lobby/id_generator.h
    main/lobby/game_room.cpp
    main/lobby/game_room.h
    main/lobby/games_manager.cpp
    main/lobby/games_manager.h


    game/control/InGameClients.h
    game/control/InGameClients.cpp
    game/control/GameEngineInstance.h
    game/control/GameEngineInstance.cpp
    game/control/GameInstance.h
    game/control/GameInstance.cpp
    game/core/configs/Config.h
    game/core/configs/GameCfg.h
    game/core/configs/model/WeaponCfg.h
    game/core/configs/model/WeaponConfig.cpp
    game/core/configs/model/WormCfg.h
    game/core/configs/model/WormConfig.cpp
    game/core/configs/systems/TurnSystemCfg.h
    game/core/configs/systems/TurnSystemConfig.cpp
    game/core/InstancesManager.h
    game/core/InstancesManager.cpp
    game/core/constants/CollideableTags.h
    game/core/GameState.h
    game/model/core/Instance.h
    game/model/core/Instance.cpp
    game/model/core/Updatable.h
    game/core/Logger.h
    game/core/Logger.cpp
    game/model/core/OnTurnEndedListener.h
    game/model/core/Body.h
    game/model/core/Body.cpp
    game/model/core/Collidable.h
    game/model/worm/WormBody.h
    game/model/worm/WormBody.cpp
    game/model/worm/Worm.h
    game/model/worm/Worm.cpp
    game/model/worm/Health.h
    game/model/worm/Health.cpp

    game/model/weapons/Weapon.h
    game/model/weapons/Weapon.cpp
    game/model/weapons/WeaponFactory.h
    game/model/weapons/WeaponFactory.cpp
        game/model/weapons/ChargeableWeapon.h
        game/model/weapons/ChargeableWeapon.cpp
        game/model/weapons/InstantShotWeapon.h
        game/model/weapons/InstantShotWeapon.cpp

        game/model/weapons/WeaponRotation.h
    game/model/weapons/WeaponRotation.cpp
    game/model/projectiles/ProjectileInfo.h
        game/model/projectiles/FragmentsInfo.h
        game/model/projectiles/CShot.h
    game/model/projectiles/CShot.cpp
    game/model/projectiles/CExplosion.h
        game/model/projectiles/CFragments.h
        game/model/projectiles/Projectile.h
    game/model/projectiles/Projectile.cpp
    game/model/projectiles/CountdownProjectile.h
    game/model/projectiles/CountdownProjectile.cpp
    game/model/projectiles/InstantExplosionProjectile.h
    game/model/projectiles/InstantExplosionProjectile.cpp
    game/model/projectiles/ProjectileBody.h
    game/model/projectiles/ProjectileBody.cpp
    game/model/projectiles/ProjectileFactory.h
    game/model/projectiles/ProjectileFactory.cpp
    game/model/forces/Force.h
    game/model/forces/BuoyancyForce.h
    game/model/forces/BuoyancyForce.cpp
    game/model/forces/ExplosionForce.h
    game/model/forces/ExplosionForce.cpp
    game/model/forces/WindForce.h
    game/model/forces/WindForce.cpp

    game/model/worm/WormFootSensor.h
    game/model/worm/WormFootSensor.cpp
    game/model/collidables/ScenarioWater.h
    game/model/collidables/ScenarioWater.cpp
    game/model/collidables/ScenarioBeams.h
    game/model/collidables/ScenarioBeams.cpp
    game/model/collidables/ScenarioBoundaries.h
    game/model/collidables/ScenarioBoundaries.cpp

    game/control/GameNetMessageBehaviour.h
    game/control/GameNetMessageBehaviour.cpp

    game/scenario/BeamScenarioData.h
    game/scenario/WormScenarioData.h
    game/scenario/GameScenarioData.h
    game/scenario/HardcodedScenarioData.h
    game/scenario/ScenarioReader.h
    game/scenario/ScenarioReader.cpp

    game/systems/turns/TurnManager.h
    game/systems/turns/TurnManager.cpp

        game/systems/updatables/UpdatablesSystem.h
    game/systems/updatables/UpdatablesSystem.cpp
    game/systems/shot/ShotSystem.h
    game/systems/shot/ShotSystem.cpp
    game/systems/explosions/ExplosionsSystem.h
    game/systems/explosions/ExplosionsSystem.cpp

    game/systems/physics/begin_collision_resolvers/BWormFootSensorWGround.h
    game/systems/physics/begin_collision_resolvers/BWormFootSensorWGround.cpp
    game/systems/physics/begin_collision_resolvers/BProjectileWAny.h
    game/systems/physics/begin_collision_resolvers/BProjectileWAny.cpp
    game/systems/physics/begin_collision_resolvers/BWaterWWorm.h
    game/systems/physics/begin_collision_resolvers/BWaterWWorm.cpp
    game/systems/physics/begin_collision_resolvers/BWaterWProjectile.h
    game/systems/physics/begin_collision_resolvers/BWaterWProjectile.cpp
    game/systems/physics/end_collision_resolvers/EWormFootSensorWGround.h
    game/systems/physics/end_collision_resolvers/EWormFootSensorWGround.cpp
    game/systems/physics/world_queries/OnExplosionWormsQuery.h
    game/systems/physics/world_queries/OnExplosionWormsQuery.cpp
    game/systems/physics/world_queries/ExplosionQueryCallback.h
    game/systems/physics/world_queries/ExplosionQueryCallback.cpp
    game/systems/physics/PhysicsCollisionListener.h
    game/systems/physics/PhysicsCollisionListener.cpp
    game/systems/physics/PhysicsSystem.h
    game/systems/physics/PhysicsSystem.cpp
    game/systems/physics/user_data_queries/UserDataQuery.h

    game/systems/wind/WindSystem.h
    game/systems/wind/WindSystem.cpp

    game/systems/entity_camera_focus/EntityCameraFocusSystem.h
    game/systems/entity_camera_focus/EntityCameraFocusSystem.cpp
        game/model/projectiles/RotationStrategy.h
        game/model/projectiles/VelocityAlignedRotation.cpp
        game/model/weapons/ProjectileCountDownChanger.h
        game/model/weapons/DefaultProjectileCountDownChanger.h
        game/model/weapons/DefaultProjectileCountDownChanger.cpp
        game/model/weapons/NoneProjectileCountDownChanger.h
        game/model/weapons/NoneProjectileCountDownChanger.cpp
        game/systems/turns/ClientTurn.h
        game/systems/turns/ClientTurn.cpp
)

target_include_directories(server_app PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/game"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/control"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/core/configs"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/core/configs/model"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/core/configs/systems"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/core/constants"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/collidables"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/forces"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/game_events"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/projectiles"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/weapons"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/weapons/chargeable_weapons"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/weapons/instant_shot_weapons"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/model/worm"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/scenario"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/entity_camera_focus"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/explosions"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/physics"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/physics/begin_collision_resolvers"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/physics/end_collision_resolvers"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/physics/user_data_queries"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/physics/world_queries"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/shot"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/turns"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/updatables"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/systems/wind"

    "${CMAKE_CURRENT_SOURCE_DIR}/main"
    "${CMAKE_CURRENT_SOURCE_DIR}/main/client"
    "${CMAKE_CURRENT_SOURCE_DIR}/main/lobby"
    "${CMAKE_CURRENT_SOURCE_DIR}/configs"
    "${CMAKE_SOURCE_DIR}/common_base/Game"
)

set(CONFIGS_FILE_PATH "${CMAKE_SOURCE_DIR}/server/configs/")
add_compile_definitions(CONFIGS_FILE_PATH="${CONFIGS_FILE_PATH}")

target_link_libraries(server_app PUBLIC box2d)
target_link_libraries(server_app PUBLIC yaml-cpp)
target_link_libraries(server_app PUBLIC common)
