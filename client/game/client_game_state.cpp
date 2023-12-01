#include "client_game_state.h"
#include "ui_utils.h"
#include "constants.h"

ClientGameState::ClientGameState(GameDisplay &display)
    : display(display),
      turnDisplay(display.new_text("Es mi turno!", 400, 0, TextAlign::center, TextLayer::UI, TextType::title)),
      timer(display),
      worms(), my_client_id(-1) {
    turnDisplay->hidden(true);
}

void ClientGameState::load(const std::shared_ptr<ClientGameStateDTO> &game) {
    std::cout << "Loading scenario size("
              << game->width << ","
              << game->height << ")"
              << "   Water level: " << game->water_level_height
              << "   Beams: " << game->beams.size()
              << "   Worms: " << game->worms.size() << "\n";

    width = game->width;
    height = game->height;

    display.start_scenario(game->width, game->height, game->water_level_height);

    for (auto &beam: game->beams) {
        float beam_w = 0, beam_h = 0;
        switch (beam.type) {
            case BeamDto::Type::LONG:
                beam_w = LARGE_BEAM_WIDTH;
                beam_h = LARGE_BEAM_HEIGHT;
                break;
            case BeamDto::Type::SHORT:
                beam_w = SHORT_BEAM_WIDTH;
                beam_h = SHORT_BEAM_HEIGHT;
                break;
        }

        auto image = display.new_sprite("beam_large", beam_w, beam_h, beam.angle);
        image->set_pos(beam.x, beam.y);
    }

    for (auto &worm: game->worms) {
        worms.emplace(worm.entity_id, std::make_shared<WormEntity>(display, worm));
        display.camera.set_target(worms[worm.entity_id].get());
    }
}

void ClientGameState::update(const std::shared_ptr<ClientGameStateDTO> &game_state_dto) {
    timer.update(game_state_dto->remaining_turn_time, game_state_dto->remaining_game_time);


    for (auto &explosion: game_state_dto->explosions) {
        // auto image = display.new_sprite("wdead", WORM_SIZE, WORM_SIZE, 0);
        // image->set_pos(explosion.x, explosion.y);
    }

    for (auto &worm_dto: game_state_dto->worms) {
        auto &it = worms[worm_dto.entity_id];
        it->update(worm_dto, worm_dto.entity_id == game_state_dto->focused_entity_id);
    }

    if (game_state_dto->projectiles.size() < projectiles.size()) {
        destroy_old_projectiles(game_state_dto->projectiles);
    }

    for (auto &projectile_dto: game_state_dto->projectiles) {
        auto it = projectiles.find(projectile_dto.entity_id);

        if (it != projectiles.end()) {
            it->second->update(projectile_dto);
        } else {
            projectiles.emplace(
                projectile_dto.entity_id, std::make_unique<ProjectileEntity>(display, projectile_dto)
            );
        }
    }
    turnDisplay->hidden(my_client_id != game_state_dto->current_turn_client_id);

    if (game_state_dto->focused_entity_id > 0) {
        focus_camera_on(game_state_dto->focused_entity_id);
    }
}


void ClientGameState::focus_camera_on(int entity_id) {
    auto worm_iter = worms.find(entity_id);
    if (worm_iter != worms.end()) {
        display.camera.set_target(worm_iter->second.get());
    } else {
        auto projectile_iter = projectiles.find(entity_id);
        if (projectile_iter != projectiles.end()) {
            display.camera.set_target(projectile_iter->second.get());
        }
    }
}

void ClientGameState::destroy_old_projectiles(std::vector<ProjectileDto> updated_projectiles) {
    auto it = projectiles.begin();
    while (it != projectiles.end()) {
        auto projectile_id = it->first;
        auto found = std::find_if(
            updated_projectiles.begin(),
            updated_projectiles.end(),
            [projectile_id](const auto &worm_dto) {
                return worm_dto.entity_id == projectile_id;
            }
        );

        if (found == updated_projectiles.end()) {
            // LATER CAN HAVE WORLD EVENTS DTO
            // TODO HERE CAN TRIGGER EXPLOSION ANIM
            // auto image = display.new_sprite("x_explosion", EXPLOSION_SIZE, EXPLOSION_SIZE, 0);
            // image->set_pos(found->get_x(), found->get_y());

            display.remove(it->second->get_sprite());
            it = projectiles.erase(it);
        } else {
            ++it;
        }
    }
}
