#include "game/game.hpp"

#include <cmath>
#include <functional>
#include <iostream> // delete me

#if __has_include(<GL/glew.h>) && __has_include(<GLFW/glfw3.h>)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif

#include "game/vec2.hpp"

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

    // Converts cell row index to y or col index to x
    inline float cell_to_canvas_coord(unsigned index) {
        return index * CELL_SIDE * CANVAS_SCALE_FACTOR;
    }

    // Converts y to row index or x to col index
    inline unsigned canvas_coord_to_cell(float coord) {
        return floor(coord / (CELL_SIDE * CANVAS_SCALE_FACTOR));
    }

    // Converts y to row index or x to col index
    inline unsigned mouse_coord_to_cell(float coord) {
        return floor(coord / (CELL_SIDE * MOUSE_SCALE_FACTOR));
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
, cell_sprite()
, update_phase_funcs()
, render_phase_funcs()
// , mouse_x(0.0f)
// , mouse_y(0.0f)
, mouse_state({false, false, 0.0f, 0.0f})
, selected_cell({0, 0})
, delta_time(timer.update())
, move({0.0f, 0.0f, 0.0f, 0.0f})
, victory(false)
, defeat(false) {
    cell_sprite = {
        {Field::cell_t::PLAYER,   resources.get_sprite("boy"s)},
        {Field::cell_t::COMPUTER, resources.get_sprite("girl"s)},
        {Field::cell_t::EMPTY,    nullptr},
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

void Game::update_phase_player_turn() {
    auto [lmb_press, _, mouse_x, mouse_y] = mouse_state;

    if (lmb_press) {
        unsigned row = mouse_coord_to_cell(mouse_y);
        unsigned col = mouse_coord_to_cell(mouse_x);

        if (field.can_move(Field::cell_t::PLAYER, row, col)) {
            selected_cell = {row, col};
            state.proceed();
        }
    }
}

void Game::update_phase_character_selected() {
    auto [lmb_press, rmb_press, mouse_x, mouse_y] = mouse_state;

    if (rmb_press) {
        state.set_phase(State::phase_t::PLAYER_TURN);

        return;
    }

    if (lmb_press) {
        unsigned mouse_row = mouse_coord_to_cell(mouse_y);
        unsigned mouse_col = mouse_coord_to_cell(mouse_x);
        auto     [selected_row, selected_col] = selected_cell;
        bool     adjacents = field.is_adjacents(selected_row, selected_col,
         mouse_row, mouse_col);

        if (field.is_empty(mouse_row, mouse_col) && adjacents) {
            move = {
                cell_to_canvas_coord(selected_col),
                cell_to_canvas_coord(selected_row),
                cell_to_canvas_coord(mouse_col),
                cell_to_canvas_coord(mouse_row),
            };
            field.unset_cell(selected_row, selected_col);
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

    field.set_cell(canvas_coord_to_cell(dst_y), canvas_coord_to_cell(dst_x),
     Field::cell_t::PLAYER);
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
    Sprite *spr_white_frame = resources.get_sprite("white_frame"s);
    unsigned          rows_count = field.get_rows_count();
    unsigned          cols_count = field.get_cols_count();

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
    float    mouse_x;
    float    mouse_y;
    unsigned row;
    unsigned col;
    Sprite  *spr_yellow_frame = resources.get_sprite("yellow_frame"s);

    std::tie(std::ignore, std::ignore, mouse_x, mouse_y) = mouse_state;
    row = mouse_coord_to_cell(mouse_y);
    col = mouse_coord_to_cell(mouse_x);

    if (field.can_move(Field::cell_t::PLAYER, row, col))
        draw->put_sprite(*spr_yellow_frame, cell_to_canvas_coord(col),
         cell_to_canvas_coord(row), FRAMES_Z, CANVAS_SCALE_FACTOR);
}

void Game::render_possible_direction(unsigned row, unsigned col,
 unsigned mouse_row, unsigned mouse_col, Sprite *spr_selected,
 Sprite *spr_direction) {
    if (field.is_empty(row, col)) {
        if ((mouse_row == row) && (mouse_col == col))
            draw->put_sprite(*spr_selected, cell_to_canvas_coord(col),
             cell_to_canvas_coord(row), FRAMES_Z, CANVAS_SCALE_FACTOR);
        else
            draw->put_sprite(*spr_direction, cell_to_canvas_coord(col),
             cell_to_canvas_coord(row), FRAMES_Z, CANVAS_SCALE_FACTOR);
    }
}

void Game::render_phase_character_selected() {
    unsigned mouse_row;
    unsigned mouse_col;
    float    mouse_x;
    float    mouse_y;
    auto    [selected_row, selected_col] = selected_cell;
    Sprite  *spr_yellow_frame = resources.get_sprite("yellow_frame"s);
    Sprite  *spr_green_frame = resources.get_sprite("green_frame"s);

    std::tie(std::ignore, std::ignore, mouse_x, mouse_y) = mouse_state;
    mouse_row = mouse_coord_to_cell(mouse_y);
    mouse_col = mouse_coord_to_cell(mouse_x);

    draw->put_sprite(*spr_yellow_frame, cell_to_canvas_coord(selected_col),
     cell_to_canvas_coord(selected_row), FRAMES_Z, CANVAS_SCALE_FACTOR);

    render_possible_direction(selected_row - 1, selected_col, mouse_row,
     mouse_col, spr_yellow_frame, spr_green_frame);
    render_possible_direction(selected_row + 1, selected_col, mouse_row,
     mouse_col, spr_yellow_frame, spr_green_frame);
    render_possible_direction(selected_row, selected_col - 1, mouse_row,
     mouse_col, spr_yellow_frame, spr_green_frame);
    render_possible_direction(selected_row, selected_col + 1, mouse_row,
     mouse_col, spr_yellow_frame, spr_green_frame);
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

bool Game::is_victory() {
    return victory || (field.is_player(5, 5) && field.is_player(5, 6) && field.is_player(5, 7)
     && field.is_player(6, 5) && field.is_player(6, 6) && field.is_player(6, 7)
     && field.is_player(7, 5) && field.is_player(7, 6) && field.is_player(7, 7)  && !defeat);
}

bool Game::is_defeat() {
    return defeat || (field.is_computer(0, 0) && field.is_computer(0, 1) && field.is_computer(0, 2)
     && field.is_computer(1, 0) && field.is_computer(1, 1) && field.is_computer(1, 2)
     && field.is_computer(2, 0) && field.is_computer(2, 1) && field.is_computer(2, 2) && !victory);
}

void Game::render() {
    Sprite *spr_field = resources.get_sprite("floor"s);


    draw->put_sprite(*spr_field, 0.0f, 0.0f, FIELD_Z, CANVAS_SCALE_FACTOR);

    render_white_frames();

    for (unsigned row = 0; row < field.get_rows_count(); row++) {
        for (unsigned col = 0; col < field.get_cols_count(); col++) {
            Sprite *character_sprite = cell_sprite[field.get_cell(row, col)];

            if (character_sprite != nullptr)
                draw->put_sprite(*character_sprite,
                 cell_to_canvas_coord(col), cell_to_canvas_coord(row),
                 CHARACTERS_Z, CANVAS_SCALE_FACTOR);
        }
    }

    render_phase();
    if (is_victory()) {
        Sprite *spr_msg = resources.get_sprite("win"s);
        draw->put_sprite(*spr_msg, 32.0f * CANVAS_SCALE_FACTOR, 48.0f * CANVAS_SCALE_FACTOR, TEXT_Z, CANVAS_SCALE_FACTOR);
    }
    if (is_defeat()) {
        Sprite *spr_msg = resources.get_sprite("fail"s);
        draw->put_sprite(*spr_msg, 32.0f * CANVAS_SCALE_FACTOR, 48.0f * CANVAS_SCALE_FACTOR, TEXT_Z, CANVAS_SCALE_FACTOR);
    }


    draw->update();
}

void Game::mainloop() {
    while (!window->should_close()) {
        float mouse_x;
        float mouse_y;

        update();
        render();

        app->update();

        if (keyboard.key_down(KEY_QUIT))
            window->request_close();

        std::tie(mouse_x, mouse_y) = mouse.get_cursor_pos();
        mouse_state = {
            mouse.button_down(Mouse::button_t::LEFT),
            mouse.button_down(Mouse::button_t::RIGHT),
            mouse_x,
            mouse_y,
        };

        delta_time = timer.update();
        // std::cout << delta_time << std::endl;
    }
}

} // game::
