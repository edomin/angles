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
    const float MOVE_SPEED = 1.0f;

    const float TEXT_X = 32.0f * CANVAS_SCALE_FACTOR;
    const float TEXT_Y = 48.0f * CANVAS_SCALE_FACTOR;

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

    // Converts cell row index to y or col index to x
    inline float cell_to_canvas_coord(unsigned index) {
        return index * CELL_SIDE * CANVAS_SCALE_FACTOR;
    }

    // Converts y to row index or x to col index
    inline unsigned canvas_coord_to_cell(float coord) {
        return floor(coord / (CELL_SIDE * CANVAS_SCALE_FACTOR));
    }
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
, move({0.0f, 0.0f, 0.0f, 0.0f})
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
                cell_to_canvas_coord(selected_cell.col),
                cell_to_canvas_coord(selected_cell.row),
                cell_to_canvas_coord(mouse_cell.col),
                cell_to_canvas_coord(mouse_cell.row),
            };
            field.unset_content(selected_cell);
            state.proceed();
        }
    }
}

void Game::update_phase_player_animation() {
    auto [x, y, dst_x, dst_y] = move;
    // Vec2 pos(x, y);
    // Vec2 dst(dst_x, dst_y);
    // Vec2 new_pos(dst - pos);

    // ...
    //
    // Здесь планировалось сделать плавную анимацию передвижения, но у меня
    // времени не хватило
    //
    // ...

    field.set_content(Cell{canvas_coord_to_cell(dst_y), canvas_coord_to_cell(dst_x)},
     Field::content_t::PLAYER);
    victory = is_victory();
    state.proceed();
}

void Game::update_phase_computer_turn() {
    ai.process_turn();
    state.proceed();
}

void Game::update_phase_computer_animation() {
    defeat = is_defeat();
    state.proceed();
}

void Game::update_phase() {
    std::invoke(update_phase_funcs[state.get_phase()], this);
}

void Game::render_white_frames() {
    Sprite  *spr_white_frame = resources.get_sprite("white_frame"s);
    unsigned rows_count = field.get_rows_count();
    unsigned cols_count = field.get_cols_count();

    for (unsigned row = 0; row < 3; row++) {
        for (unsigned col = 0; col < 3; col++)
            draw->put_sprite(*spr_white_frame, cell_to_canvas_coord(col),
             cell_to_canvas_coord(row), FRAMES_Z, CANVAS_SCALE_FACTOR);
    }
    for (unsigned row = rows_count - 3; row < rows_count; row++) {
        for (unsigned col = cols_count - 3; col < cols_count; col++)
            draw->put_sprite(*spr_white_frame, cell_to_canvas_coord(col),
             cell_to_canvas_coord(row), FRAMES_Z, CANVAS_SCALE_FACTOR);
    }
}

void Game::render_phase_player_turn() {
    Cell    cell = mouse_coords_to_cell();
    Sprite *spr_yellow_frame = resources.get_sprite("yellow_frame"s);

    if (field.can_move(Field::content_t::PLAYER, cell))
        draw->put_sprite(*spr_yellow_frame, cell_to_canvas_coord(cell.col),
         cell_to_canvas_coord(cell.row), FRAMES_Z, CANVAS_SCALE_FACTOR);
}

void Game::render_possible_direction(const Cell &cell, const Cell &mouse_cell,
 Sprite *spr_selected, Sprite *spr_direction) {
    if (field.is_empty(cell)) {
        if (mouse_cell == cell)
            draw->put_sprite(*spr_selected, cell_to_canvas_coord(cell.col),
             cell_to_canvas_coord(cell.row), FRAMES_Z, CANVAS_SCALE_FACTOR);
        else
            draw->put_sprite(*spr_direction, cell_to_canvas_coord(cell.col),
             cell_to_canvas_coord(cell.row), FRAMES_Z, CANVAS_SCALE_FACTOR);
    }
}

void Game::render_phase_character_selected() {
    Cell    mouse_cell = mouse_coords_to_cell();
    Sprite *spr_yellow_frame = resources.get_sprite("yellow_frame"s);
    Sprite *spr_green_frame = resources.get_sprite("green_frame"s);

    draw->put_sprite(*spr_yellow_frame, cell_to_canvas_coord(selected_cell.col),
     cell_to_canvas_coord(selected_cell.row), FRAMES_Z, CANVAS_SCALE_FACTOR);

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

}

void Game::render_phase_computer_turn() {

}

void Game::render_phase_computer_animation() {

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

    draw->put_sprite(*spr_field, 0.0f, 0.0f, FIELD_Z, CANVAS_SCALE_FACTOR);

    render_white_frames();

    for (unsigned row = 0; row < field.get_rows_count(); row++) {
        for (unsigned col = 0; col < field.get_cols_count(); col++) {
            Sprite *character_sprite = field_content_sprites[field.get_content(row, col)];

            if (character_sprite != nullptr)
                draw->put_sprite(*character_sprite,
                 cell_to_canvas_coord(col), cell_to_canvas_coord(row),
                 CHARACTERS_Z, CANVAS_SCALE_FACTOR);
        }
    }

    render_phase();
    if (is_victory()) {
        Sprite *spr_msg = resources.get_sprite("win"s);
        draw->put_sprite(*spr_msg, TEXT_X, TEXT_Y, TEXT_Z, CANVAS_SCALE_FACTOR);
    }
    if (is_defeat()) {
        Sprite *spr_msg = resources.get_sprite("fail"s);
        draw->put_sprite(*spr_msg, TEXT_X, TEXT_Y, TEXT_Z, CANVAS_SCALE_FACTOR);
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
