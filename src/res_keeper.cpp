#include "res_keeper.hpp"

#include <memory>

#include "exception.hpp"
#include "iimg.hpp"
#include "img_characters.hpp"
#include "img_floor.hpp"
#include "img_frames.hpp"
#include "img_text.hpp"

using namespace std::string_literals;

namespace {
    const unsigned SPRSH_CHARACTERS_CLIP_WIDTH = 16;
    const unsigned SPRSH_CHARACTERS_CLIP_HEIGHT = 16;
    const unsigned SPRSH_FLOOR_CLIP_WIDTH = 128;
    const unsigned SPRSH_FLOOR_CLIP_HEIGHT = 128;
    const unsigned SPRSH_FRAMES_CLIP_WIDTH = 16;
    const unsigned SPRSH_FRAMES_CLIP_HEIGHT = 16;
    const unsigned SPRSH_TEXT_CLIP_WIDTH = 64;
    const unsigned SPRSH_TEXT_CLIP_HEIGHT = 32;

    const unsigned SPR_BOY_FACING_DOWN_CLIP_NUMBER = 0;
    const unsigned SPR_GIRL_FACING_DOWN_CLIP_NUMBER = 3;
    const unsigned SPR_FLOOR_CLIP_NUMBER = 0;
    const unsigned SPR_WHITE_FRAME_CLIP_NUMBER = 0;
    const unsigned SPR_YELLOW_FRAME_CLIP_NUMBER = 1;
    const unsigned SPR_GREEN_FRAME_CLIP_NUMBER = 2;
    const unsigned SPR_WIN_CLIP_NUMBER = 0;
    const unsigned SPR_FAIL_CLIP_NUMBER = 1;
}

ResKeeper::ResKeeper()
: textures()
, spritesheets()
, sprites() {
    std::unique_ptr<IImg> img_characters = std::make_unique<ImgCharacters>();
    std::unique_ptr<IImg> img_floor = std::make_unique<ImgFloor>();
    std::unique_ptr<IImg> img_frames = std::make_unique<ImgFrames>();
    std::unique_ptr<IImg> img_text = std::make_unique<ImgText>();

    Texture              *tex_characters = new Texture(
     img_characters->get_data(), img_characters->get_width(),
     img_characters->get_height());
    Texture              *tex_floor = new Texture(img_floor->get_data(),
     img_floor->get_width(), img_floor->get_height());
    Texture              *tex_frames = new Texture(img_frames->get_data(),
     img_frames->get_width(), img_frames->get_height());
    Texture              *tex_text = new Texture(img_text->get_data(),
     img_text->get_width(), img_text->get_height());

    Spritesheet          *sprsh_characters = new Spritesheet(*tex_characters,
     SPRSH_FRAMES_CLIP_WIDTH, SPRSH_CHARACTERS_CLIP_HEIGHT);
    Spritesheet          *sprsh_floor = new Spritesheet(*tex_floor,
     SPRSH_FLOOR_CLIP_WIDTH, SPRSH_FLOOR_CLIP_HEIGHT);
    Spritesheet          *sprsh_frames = new Spritesheet(*tex_frames,
     SPRSH_FRAMES_CLIP_WIDTH, SPRSH_FRAMES_CLIP_HEIGHT);
    Spritesheet          *sprsh_text = new Spritesheet(*tex_text,
     SPRSH_TEXT_CLIP_WIDTH, SPRSH_TEXT_CLIP_HEIGHT);

    Sprite               *spr_boy = new Sprite(*sprsh_characters,
     SPR_BOY_FACING_DOWN_CLIP_NUMBER);
    Sprite               *spr_girl = new Sprite(*sprsh_characters,
     SPR_GIRL_FACING_DOWN_CLIP_NUMBER);
    Sprite               *spr_floor = new Sprite(*sprsh_floor,
     SPR_FLOOR_CLIP_NUMBER);
    Sprite               *spr_white_frame = new Sprite(*sprsh_frames,
     SPR_WHITE_FRAME_CLIP_NUMBER);
    Sprite               *spr_yellow_frame = new Sprite(*sprsh_frames,
     SPR_YELLOW_FRAME_CLIP_NUMBER);
    Sprite               *spr_green_frame = new Sprite(*sprsh_frames,
     SPR_GREEN_FRAME_CLIP_NUMBER);
    Sprite               *spr_win = new Sprite(*sprsh_text,
     SPR_WIN_CLIP_NUMBER);
    Sprite               *spr_fail = new Sprite(*sprsh_text,
     SPR_FAIL_CLIP_NUMBER);

    textures.insert({
        tex_characters,
        tex_floor,
        tex_frames,
        tex_text,
    });
    spritesheets.insert({
        sprsh_characters,
        sprsh_floor,
        sprsh_frames,
        sprsh_text,
    });
    sprites.insert({
        {"boy"s, spr_boy},
        {"girl"s, spr_girl},
        {"floor"s, spr_floor},
        {"white_frame"s, spr_white_frame},
        {"yellow_frame"s, spr_yellow_frame},
        {"green_frame"s, spr_green_frame},
        {"win"s, spr_win},
        {"fail"s, spr_fail},
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
