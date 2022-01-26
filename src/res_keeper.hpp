#ifndef RES_KEEPER_HPP
#define RES_KEEPER_HPP

#include <map>
#include <set>
#include <string>

#include "texture.hpp"
#include "spritesheet.hpp"
#include "sprite.hpp"

// This class keeps all loaded resources
class ResKeeper {
    private:
        std::set<Texture *> textures;
        std::set<Spritesheet *> spritesheets;
        std::map<std::string, Sprite *> sprites;

    public:
        ResKeeper();
        ~ResKeeper();

        Sprite *get_sprite(const std::string &name);
};

#endif // RES_KEEPER_HPP
