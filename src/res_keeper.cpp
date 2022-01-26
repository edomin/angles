#include "res_keeper.hpp"

#include <memory>

#include "iimg.hpp"
#include "img_characters.hpp"
#include "img_floor.hpp"

using namespace std::string_literals;

ResKeeper::ResKeeper()
: textures()
, spritesheets()
, sprites() {
    std::unique_ptr<IImg> img_characters = std::make_unique<ImgCharacters>();
    std::unique_ptr<IImg> img_floor = std::make_unique<ImgFloor>();
    Texture              *tex_characters = new Texture(
     img_characters->get_data(), img_characters->get_width(),
     img_characters->get_height());
    Texture              *tex_floor = new Texture(img_floor->get_data(),
     img_floor->get_width(), img_floor->get_height());
    Spritesheet          *sprsh_characters = new Spritesheet(*tex_characters,
     16, 16);
    Spritesheet          *sprsh_floor = new Spritesheet(*tex_floor, 128, 128);
    Sprite               *spr_boy = new Sprite(*sprsh_characters, 0);
    Sprite               *spr_girl = new Sprite(*sprsh_characters, 3);
    Sprite               *spr_floor = new Sprite(*sprsh_floor, 0);

    textures.insert({tex_characters, tex_floor});
    spritesheets.insert({sprsh_characters, sprsh_floor});
    sprites.insert({
        {"boy"s, spr_boy},
        {"girl"s, spr_girl},
        {"floor"s, spr_floor},
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
    return sprites[name];
}
