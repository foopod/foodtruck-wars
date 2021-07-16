#ifndef FT_SCENE_TITLE_H
#define FT_SCENE_TITLE_H

#include "ft_scene_type.h"
#include "ft_player_data.h"

namespace ft
{
    class Intro
    {       
        private:
            PlayerData* _player_data;
        public:
            Intro(PlayerData& player_data);
            SceneType execute();
    };
}

#endif