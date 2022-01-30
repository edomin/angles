#include "game/game.hpp"

#include <cmath>
#include <functional>
#include <iostream> // delete me

#if __has_include(<GL/glew.h>) && __has_include(<GLFW/glfw3.h>)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif

using namespace std::string_literals;

namespace {
    typedef enum {
        KEY_QUIT,
    } key_t;

    // This magic needs for case if We have custom keyboard handling
    // implementation working with GLFW key codes
    #if !__has_include(<GL/glew.h>) || !__has_include(<GLFW/glfw3.h>)
        #undef GLFW_KEY_ESCAPE
        const int GLFW_KEY_ESCAPE = 256;
    #endif

    const Vec2  FIELD_POS = {0.0f, 0.0f};
    const float FIELD_Z = 0.0f;
    const float FRAMES_Z = -50.0f;
    const float CHARACTERS_Z = -100.0f;
    const float TEXT_Z = -150.0f;
    const float CELL_SIDE = 16.0f;

    // При инициализации GLWF я выставлял размеры окна 512*512, но почему-то
    // размер холста у меня 1024*1024, а диапазон значений для координат мыши
    // от 0 до 512. Скорее всего косяк где-то в моём коде, но у меня уже нет
    // времени разбираться. Я сделаю разный scale factor для мыши и для холста.
    // Да, я знаю, что это не фикс а костыль :-(
    // Scale factor нужен, что-бы работать с координатами, как будто мы
    // ограничены разрешением 128*128. Это я захотел такой крупнопиксельный
    // ретро-стиль :-)
    const float CANVAS_SCALE_FACTOR = 8.0f;
    const float MOUSE_SCALE_FACTOR = 4.0f;
    const float MOVE_SPEED = 750.0f;

    const Vec2  TEXT_POS = {
        32.0f * CANVAS_SCALE_FACTOR,
        48.0f * CANVAS_SCALE_FACTOR
    };

    const std::vector<game::Cell> player_victory_cells = {
        {game::Field::ROWS_COUNT - 3, game::Field::COLS_COUNT - 3},
        {game::Field::ROWS_COUNT - 3, game::Field::COLS_COUNT - 2},
        {game::Field::ROWS_COUNT - 3, game::Field::COLS_COUNT - 1},

        {game::Field::ROWS_COUNT - 2, game::Field::COLS_COUNT - 3},
        {game::Field::ROWS_COUNT - 2, game::Field::COLS_COUNT - 2},
        {game::Field::ROWS_COUNT - 2, game::Field::COLS_COUNT - 1},

        {game::Field::ROWS_COUNT - 1, game::Field::COLS_COUNT - 3},
        {game::Field::ROWS_COUNT - 1, game::Field::COLS_COUNT - 2},
        {game::Field::ROWS_COUNT - 1, game::Field::COLS_COUNT - 1},
    };
    const std::vector<game::Cell> computer_victory_cells = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0}, {1, 1}, {1, 2},
        {2, 0}, {2, 1}, {2, 2},
    };
}

namespace game {

Game::Game(const App &_app, Window &_window, Draw &_draw)
: app(&_app)
, window(&_window)
, draw(&_draw)
, resources()
, keyboard(*window)
, mouse(*window)
, timer()
, state()
, field()
, ai(field)
, field_content_sprites()
, update_phase_funcs()
, render_phase_funcs()
, selected_cell({0, 0})
, delta_time(timer.update())
, move({0.0f, 0.0f}, {0.0f, 0.0f})
, victory(false)
, defeat(false) {
    field_content_sprites = {
        {Field::content_t::PLAYER,   resources.get_sprite("boy"s)},
        {Field::content_t::COMPUTER, resources.get_sprite("girl"s)},
        {Field::content_t::EMPTY,    nullptr},
    };

    update_phase_funcs = {
        {State::phase_t::PLAYER_TURN,        &Game::update_phase_player_turn},
        {State::phase_t::CHARACTER_SELECTED, &Game::update_phase_character_selected},
        {State::phase_t::PLAYER_ANIMATION,   &Game::update_phase_player_animation},
        {State::phase_t::COMPUTER_TURN,      &Game::update_phase_computer_turn},
        {State::phase_t::COMPUTER_ANIMATION, &Game::update_phase_computer_animation},
    };

    render_phase_funcs = {
        {State::phase_t::PLAYER_TURN,        &Game::render_phase_player_turn},
        {State::phase_t::CHARACTER_SELECTED, &Game::render_phase_character_selected},
        {State::phase_t::PLAYER_ANIMATION,   &Game::render_phase_player_animation},
        {State::phase_t::COMPUTER_TURN,      &Game::render_phase_computer_turn},
        {State::phase_t::COMPUTER_ANIMATION, &Game::render_phase_computer_animation},
    };

    keyboard.register_key(KEY_QUIT, GLFW_KEY_ESCAPE);
}

Game::~Game() {

}

Vec2 Game::cell_to_canvas_coords(unsigned row, unsigned col) {
    float scaled_side = CELL_SIDE * CANVAS_SCALE_FACTOR;

    return Vec2{col * scaled_side, row * scaled_side};
}

Vec2 Game::cell_to_canvas_coords(const Cell &cell) {
    return cell_to_canvas_coords(cell.row, cell.col);
}

Cell Game::canvas_coords_to_cell(const Vec2 &coords) {
    float    scaled_side = CELL_SIDE * CANVAS_SCALE_FACTOR;
    unsigned row = static_cast<unsigned>(floor(coords.y / scaled_side));
    unsigned col = static_cast<unsigned>(floor(coords.x / scaled_side));

    return Cell{row, col};
}

Cell Game::mouse_coords_to_cell() {
    float    scaled_side = CELL_SIDE * MOUSE_SCALE_FACTOR;
    Vec2     cursor_pos = mouse.get_cursor_pos();
    unsigned row = static_cast<unsigned>(floor(cursor_pos.y / scaled_side));
    unsigned col = static_cast<unsigned>(floor(cursor_pos.x / scaled_side));

    return Cell{row, col};
}

void Game::update_phase_player_turn() {
    if (mouse.left_button_down()) {
        Cell cell = mouse_coords_to_cell();

        if (field.can_move(Field::content_t::PLAYER, cell)) {
            selected_cell = cell;
            state.proceed();
        }
    }
}

void Game::update_phase_character_selected() {
    if (mouse.right_button_down()) {
        state.set_phase(State::phase_t::PLAYER_TURN);

        return;
    }

    if (mouse.left_button_down()) {
        Cell mouse_cell = mouse_coords_to_cell();
        bool adjacents = field.is_adjacents(selected_cell, mouse_cell);

        if (field.is_empty(mouse_cell) && adjacents) {
            move = {
                cell_to_canvas_coords(selected_cell),
                cell_to_canvas_coords(mouse_cell)
            };
            field.unset_content(selected_cell);
            state.proceed();
        }
    }
}

void Game::update_phase_player_animation() {
    if (move.shrink_to_b(MOVE_SPEED * delta_time)) {
        field.set_content(canvas_coords_to_cell(move.b),
         Field::content_t::PLAYER);
        victory = is_victory();
        state.proceed();
    }
}

void Game::update_phase_computer_turn() {
    auto [start_cell, dst_cell] = ai.process_turn();

    move = {
        cell_to_canvas_coords(start_cell),
        cell_to_canvas_coords(dst_cell)
    };

    state.proceed();
}

void Game::update_phase_computer_animation() {
    if (move.shrink_to_b(MOVE_SPEED * delta_time)) {
        field.set_content(canvas_coords_to_cell(move.b),
         Field::content_t::COMPUTER);
        defeat = is_defeat();
        state.proceed();
    }
}

void Game::update_phase() {
    std::invoke(update_phase_funcs[state.get_phase()], this);
}

void Game::render_white_frames() {
    Sprite *spr_white_frame = resources.get_sprite("white_frame"s);

    // player_victory_cells.size() == computer_victory_cells.size()
    for (unsigned i = 0; i < player_victory_cells.size(); i++) {
        draw->put_sprite(*spr_white_frame,
         cell_to_canvas_coords(player_victory_cells[i]), FRAMES_Z,
         CANVAS_SCALE_FACTOR);
        draw->put_sprite(*spr_white_frame,
         cell_to_canvas_coords(computer_victory_cells[i]), FRAMES_Z,
         CANVAS_SCALE_FACTOR);
    }
}

void Game::render_phase_player_turn() {
    Cell    cell = mouse_coords_to_cell();
    Sprite *spr_yellow_frame = resources.get_sprite("yellow_frame"s);

    if (field.can_move(Field::content_t::PLAYER, cell))
        draw->put_sprite(*spr_yellow_frame, cell_to_canvas_coords(cell),
         FRAMES_Z, CANVAS_SCALE_FACTOR);
}

void Game::render_possible_direction(const Cell &cell, const Cell &mouse_cell,
 Sprite *spr_selected, Sprite *spr_direction) {
    if (field.is_empty(cell)) {
        if (mouse_cell == cell)
            draw->put_sprite(*spr_selected, cell_to_canvas_coords(cell),
             FRAMES_Z, CANVAS_SCALE_FACTOR);
        else
            draw->put_sprite(*spr_direction, cell_to_canvas_coords(cell),
             FRAMES_Z, CANVAS_SCALE_FACTOR);
    }
}

void Game::render_phase_character_selected() {
    Cell    mouse_cell = mouse_coords_to_cell();
    Sprite *spr_yellow_frame = resources.get_sprite("yellow_frame"s);
    Sprite *spr_green_frame = resources.get_sprite("green_frame"s);

    draw->put_sprite(*spr_yellow_frame, cell_to_canvas_coords(selected_cell),
     FRAMES_Z, CANVAS_SCALE_FACTOR);

    render_possible_direction(selected_cell.near_top(), mouse_cell,
     spr_yellow_frame, spr_green_frame);
    render_possible_direction(selected_cell.near_bottom(), mouse_cell,
     spr_yellow_frame, spr_green_frame);
    render_possible_direction(selected_cell.near_left(), mouse_cell,
     spr_yellow_frame, spr_green_frame);
    render_possible_direction(selected_cell.near_right(), mouse_cell,
     spr_yellow_frame, spr_green_frame);
}

void Game::render_phase_player_animation() {
    Sprite *spr_boy = resources.get_sprite("boy"s);

    draw->put_sprite(*spr_boy, move.a, CHARACTERS_Z, CANVAS_SCALE_FACTOR);
}

void Game::render_phase_computer_turn() {

}

void Game::render_phase_computer_animation() {
    Sprite *spr_girl = resources.get_sprite("girl"s);

    draw->put_sprite(*spr_girl, move.a, CHARACTERS_Z, CANVAS_SCALE_FACTOR);
}

void Game::render_phase() {
    std::invoke(render_phase_funcs[state.get_phase()], this);
}

void Game::update() {
    update_phase();
}

bool Game::is_side_wins(bool side_victory, bool side_defeat,
 const std::vector<Cell> &victory_cells, Field::content_t req_content) {
    bool new_side_victory = true;

    if (side_victory)
        return true;

    if (side_defeat)
        return false;

    for (size_t i = 0; i < victory_cells.size() && new_side_victory; i++)
        new_side_victory = new_side_victory
         && (field.get_content(victory_cells[i]) == req_content);

    return new_side_victory;
}

bool Game::is_victory() {
    return is_side_wins(victory, defeat, player_victory_cells,
     Field::content_t::PLAYER);
}

bool Game::is_defeat() {
    return is_side_wins(defeat, victory, computer_victory_cells,
     Field::content_t::COMPUTER);
}

void Game::render() {
    Sprite *spr_field = resources.get_sprite("floor"s);

    draw->put_sprite(*spr_field, FIELD_POS, FIELD_Z, CANVAS_SCALE_FACTOR);

    render_white_frames();

    for (unsigned row = 0; row < field.get_rows_count(); row++) {
        for (unsigned col = 0; col < field.get_cols_count(); col++) {
            Sprite *character_sprite = field_content_sprites[field.get_content(row, col)];

            if (character_sprite != nullptr)
                draw->put_sprite(*character_sprite,
                 cell_to_canvas_coords(row, col), CHARACTERS_Z,
                 CANVAS_SCALE_FACTOR);
        }
    }

    render_phase();
    if (is_victory()) {
        Sprite *spr_msg = resources.get_sprite("win"s);
        draw->put_sprite(*spr_msg, TEXT_POS, TEXT_Z, CANVAS_SCALE_FACTOR);
    }
    if (is_defeat()) {
        Sprite *spr_msg = resources.get_sprite("fail"s);
        draw->put_sprite(*spr_msg, TEXT_POS, TEXT_Z, CANVAS_SCALE_FACTOR);
    }


    draw->update();
}

void Game::mainloop() {
    while (!window->should_close()) {
        update();
        render();

        app->update();
        mouse.update();

        if (keyboard.key_down(KEY_QUIT))
            window->request_close();

        delta_time = timer.update();
    }
}

} // game::
