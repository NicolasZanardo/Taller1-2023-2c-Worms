#include "client_game_state.h"
#include "ui_utils.h"
#include "constants.h"

ClientGameState::ClientGameState(GameDisplay &display)
    : display(display), turnDisplay(display.new_text("Es mi turno!", 400, 0, 30, TextAlign::center, TextLayer::UI)),
      worms(), my_client_id(-1) {
    turnDisplay->hidden(true);
}

void ClientGameState::load(const std::shared_ptr<ClientGameStateDTO> &game_state_dto) {
    std::cout << "Loading scenario size("
              << game_state_dto->width << ","
              << game_state_dto->height << ")"
              << "   Water level: " << game_state_dto->water_level_height
              << "   Beams: " << game_state_dto->beams.size()
              << "   Worms: " << game_state_dto->worms.size() << "\n";

    width = game_state_dto->width;
    height = game_state_dto->height;

    for (auto &beam: game_state_dto->beams) {
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

    for (auto &worm: game_state_dto->worms) {
        worms.emplace(worm.entity_id, std::make_shared<WormEntity>(display, worm));
        display.camera.set_target(worms[worm.entity_id].get());
    }
}

void ClientGameState::update(const std::shared_ptr<ClientGameStateDTO> &game_state_dto) {
    game_remaining_time = game_state_dto->remaining_game_time;
    turn_remaining_time = game_state_dto->remaining_turn_time;

    // Worms that die
    if (game_state_dto->worms.size() < worms.size()) {
        transfer_death_worms(game_state_dto->worms);
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

void ClientGameState::transfer_death_worms(std::vector<WormDto> updated_worms) {
    auto it = worms.begin();
    while (it != worms.end()) {
        auto worm_id = it->first;
        auto found = std::find_if(
            updated_worms.begin(),
            updated_worms.end(),
            [worm_id](const auto &worm_dto) {
                return worm_dto.entity_id == worm_id;
            }
        );

        if (found == updated_worms.end()) {
            // death_worms[wormId] = it->second;
            auto worm_entity = it->second;
            auto image = display.new_sprite("wdead", WORM_SIZE, WORM_SIZE, 0);
            image->set_pos(worm_entity->get_x(), worm_entity->get_y());
            it = worms.erase(it);
        } else {
            ++it;
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
