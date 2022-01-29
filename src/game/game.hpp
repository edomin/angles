#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <map>

#include "app.hpp"
#include "draw.hpp"
#include "game/ai.hpp"
#include "game/field.hpp"
#include "game/state.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "res_keeper.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace game {

class Game {
    private:
        typedef void (game::Game::*render_phase_func_t)();
        typedef void (game::Game::*update_phase_func_t)();

        const App *app;
        Window    *window;
        Draw      *draw;
        ResKeeper  resources;
        Keyboard   keyboard;
        Mouse      mouse;
        Timer      timer;
        State      state;
        Field      field;
        Ai         ai;

        std::map<Field::content_t, Sprite *> field_content_sprites;

        std::map<game::State::phase_t, update_phase_func_t> update_phase_funcs;
        std::map<game::State::phase_t, render_phase_func_t> render_phase_funcs;

        std::tuple<
            unsigned, // row
            unsigned  // col
        > selected_cell;

        double delta_time;

        std::tuple<
            float, // x
            float, // y
            float, // dst_x
            float  // dst_y
        > move;

        bool victory;
        bool defeat;

        void update_phase_player_turn();
        void update_phase_character_selected();
        void update_phase_player_animation();
        void update_phase_computer_turn();
        void update_phase_computer_animation();
        void update_phase();

        void render_white_frames();
        void render_possible_direction(unsigned row, unsigned col,
         unsigned mouse_row, unsigned mouse_col, Sprite *spr_selected,
         Sprite *spr_direction);

        void render_phase_player_turn();
        void render_phase_character_selected();
        void render_phase_player_animation();
        void render_phase_computer_turn();
        void render_phase_computer_animation();
        void render_phase();

        bool is_victory();
        bool is_defeat();

    public:
        Game(const App &_app, Window &_window, Draw &_draw);
        ~Game();

        void update();
        void render();

        void mainloop();
};

} // game::

#endif // GAME_HPP
