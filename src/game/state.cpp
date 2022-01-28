#include "game/state.hpp"

namespace {
    const std::map<game::State::phase_t, game::State::phase_t> TRANSITIONS = {
        {game::State::phase_t::PLAYER_TURN,        game::State::phase_t::CHARACTER_SELECTED},
        {game::State::phase_t::CHARACTER_SELECTED, game::State::phase_t::PLAYER_ANIMATION},
        {game::State::phase_t::PLAYER_ANIMATION,   game::State::phase_t::COMPUTER_TURN},
        {game::State::phase_t::COMPUTER_TURN,      game::State::phase_t::COMPUTER_ANIMATION},
        {game::State::phase_t::COMPUTER_ANIMATION, game::State::phase_t::PLAYER_TURN},
    };
}

namespace game {

State::State()
: phase(phase_t::PLAYER_TURN) {

}

State::~State() {}

State::phase_t State::proceed() {
    phase = TRANSITIONS.at(phase);

    return phase;
}

void State::set_phase(phase_t _phase) {
    phase = _phase;
};

State::phase_t State::get_phase() const {
    return phase;
}

} // game::
