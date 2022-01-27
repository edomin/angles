#include "game/game.hpp"

#include <iostream> // delete me

using namespace std::string_literals;

namespace {
    const float FIELD_Z = 0.0f;
    const float CHARACTERS_Z = -100.0f;
    const float CELL_SIDE = 16.0f;
    const float SCALE_FACTOR = 8.0f;
}

namespace game {

Game::Game(const App &_app, Window &_window, Draw &_draw)
: app(&_app)
, window(&_window)
, draw(&_draw)
, resources()
, timer()
, state()
, field() {
    cell_sprite = {
        {Field::cell_t::PLAYER, resources.get_sprite("boy"s)},
        {Field::cell_t::COMPUTER, resources.get_sprite("girl"s)},
        {Field::cell_t::EMPTY, nullptr},
    };
}

Game::~Game() {

}

void Game::update() {

}

void Game::render() {
    Sprite *spr_field = resources.get_sprite("floor"s);

    draw->put_sprite(*spr_field, 0.0f, 0.0f, FIELD_Z, SCALE_FACTOR);

    for (unsigned row = 0; row < field.get_rows_count(); row++) {
        for (unsigned col = 0; col < field.get_cols_count(); col++) {
            Sprite *character_sprite = cell_sprite[field.get_cell(row, col)];

            if (character_sprite != nullptr)
                draw->put_sprite(*character_sprite,
                 col * CELL_SIDE * SCALE_FACTOR, row * CELL_SIDE * SCALE_FACTOR,
                 CHARACTERS_Z, SCALE_FACTOR);
        }
    }

    draw->update();
}

void Game::mainloop() {
    // Sprite *spr_field = resources.get_sprite("floor"s);
    // Sprite *spr_boy = resources.get_sprite("boy"s);
    // Sprite *spr_girl = resources.get_sprite("girl"s);

    while (!window->should_close()) {
        [[maybe_unused]] double delta_time = timer.update();

        update();
        render();

        // draw->update();
        app->update();
    }
}

} // game::
