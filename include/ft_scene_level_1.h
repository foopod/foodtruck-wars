#ifndef FT_SCENE_LEVEL_1_H
#define FT_SCENE_LEVEL_1_H

#include "bn_sprite_text_generator.h"

#include "ft_scene_type.h"
#include "ft_player_data.h"

namespace ft
{
    class Level1
    {       
        private:
            PlayerData* _player_data;
            bn::sprite_text_generator* _text_generator;
        public:
            Level1(PlayerData& player_data, bn::sprite_text_generator& text_generator);
            SceneType execute();
    };
}

#endif