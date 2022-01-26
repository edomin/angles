#include <string>

#include "app.hpp"
#include "draw.hpp"
#include "res_keeper.hpp"
#include "timer.hpp"
#include "vao.hpp"
#include "window.hpp"

using namespace std::string_literals;

int main(int argc, char **argv) {
    App                  app;
    Timer                timer;
    Window               window(800, 600, "angles"s);
    ResKeeper            resources;
    [[maybe_unused]] Vao vao;
    Draw                 draw(window);

    while (!window.should_close()) {
        [[maybe_unused]] double delta_time = timer.update();

        // draw.put_sprite(spr_floor, 20.0f, 32.0f, 300.0f, 8.0f);
        // draw.put_sprite(spr_boy, 500.0f, 32.0f, 200.0f, 8.0f);

        draw.update();
        app.update();
    }

    return 0;
}
