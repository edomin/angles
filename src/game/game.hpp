#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include "app.hpp"
#include "draw.hpp"
#include "game/field.hpp"
#include "game/state.hpp"
#include "res_keeper.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace game {

class Game {
        const App *app;
        Window    *window;
        Draw      *draw;
        ResKeeper  resources;
        Timer      timer;
        State      state;
        Field      field;

        std::map<Field::cell_t, Sprite *> cell_sprite;

    public:
        Game(const App &_app, Window &_window, Draw &_draw);
        ~Game();

        void update();
        void render();

        void mainloop();
};

} // game::

#endif // GAME_HPP
