#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "app.hpp"
#include "draw.hpp"
#include "res_keeper.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace game {

class State {
    public:
        enum class phase_t {
            PLAYER_TURN,
            PLAYER_ANIMATION,
            COMPUTER_TURN,
            COMPUTER_ANIMATION,
        };

    private:
        phase_t phase;

    public:
        State();
        ~State();

        phase_t proceed();

        phase_t get_phase() const;
};

} // game::

#endif // GAME_STATE_HPP
