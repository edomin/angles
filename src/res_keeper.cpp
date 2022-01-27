#include "res_keeper.hpp"

#include <memory>

#include "exception.hpp"
#include "iimg.hpp"
#include "img_characters.hpp"
#include "img_floor.hpp"

using namespace std::string_literals;

ResKeeper::ResKeeper()
: textures()
, spritesheets()
, sprites() {
    std::unique_ptr<IImg> img_floor = std::make_unique<ImgFloor>();
    std::unique_ptr<IImg> img_characters = std::make_unique<ImgCharacters>();
    Texture              *tex_floor = new Texture(img_floor->get_data(),
     img_floor->get_width(), img_floor->get_height());
    Texture              *tex_characters = new Texture(
     img_characters->get_data(), img_characters->get_width(),
     img_characters->get_height());
    Spritesheet          *sprsh_floor = new Spritesheet(*tex_floor, 128, 128);
    Spritesheet          *sprsh_characters = new Spritesheet(*tex_characters,
     16, 16);
    Sprite               *spr_floor = new Sprite(*sprsh_floor, 0);
    Sprite               *spr_boy = new Sprite(*sprsh_characters, 0);
    Sprite               *spr_girl = new Sprite(*sprsh_characters, 3);

    textures.insert({tex_floor, tex_characters});
    spritesheets.insert({sprsh_floor, sprsh_characters});
    sprites.insert({
        {"floor"s, spr_floor},
        {"boy"s, spr_boy},
        {"girl"s, spr_girl},
    });
}

ResKeeper::~ResKeeper() {
    for (auto &[_, sprite] : sprites)
        delete sprite;
    for (Spritesheet *spritesheet : spritesheets)
        delete spritesheet;
    for (Texture *texture : textures)
        delete texture;
}

Sprite *ResKeeper::get_sprite(const std::string &name) {
    Sprite *sprite = sprites[name];

    if (!sprite)
        ANG_THROW("Sprite not found: "s.append(name).c_str());

    return sprite;
}
