#include "bn_core.h"

#include "ft_scene_type.h"
#include "ft_scene_intro.h"

#include "ft_player_data.h"

int main()
{
    bn::core::init();

    //first scene
    ft::SceneType scene = ft::SceneType::Intro;

    //player data
    ft::PlayerData player_data = ft::PlayerData(); 

    while(true)
    {
        switch (scene)
        {
            case ft::SceneType::Intro :
                {
                    ft::Intro intro = ft::Intro(player_data);
                    intro.execute();
                    break;
                }
            default:
                break;
        }
        bn::core::update();
    }
}
