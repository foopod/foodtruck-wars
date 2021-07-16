#include "ft_scene_intro.h"

#include "bn_core.h"

namespace ft
{
    Intro::Intro(PlayerData& player_data)
    : _player_data(&player_data){}

    SceneType Intro::execute()
    {
        while(true)
        { 
            bn::core::update();
        }
    }
}