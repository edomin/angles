#include <string>

#include "app.hpp"
#include "draw.hpp"
#include "game/game.hpp"
#include "vao.hpp"
#include "window.hpp"

using namespace std::string_literals;

int main(int argc, char **argv) {
    App                  app;
    Window               window(512, 512, "angles"s);
    [[maybe_unused]] Vao vao;
    Draw                 draw(window);
    game::Game           gm(app, window, draw);

    gm.mainloop();

    return 0;
}
