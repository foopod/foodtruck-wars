#include "bn_core.h"

#include "ft_scene_type.h"
#include "ft_scene_intro.h"
#include "ft_scene_level_1.h"

#include "ft_player_data.h"

#include "ft_font.h"


int main()
{
    bn::core::init();

    //first scene
    ft::SceneType scene = ft::SceneType::Level1;

    //player data
    ft::PlayerData player_data = ft::PlayerData();

    //text generator
    bn::sprite_text_generator text_generator(ft::fixed_8x8_sprite_font);

    while(true)
    {
        switch (scene)
        {
            case ft::SceneType::Intro :
                {
                    ft::Intro intro = ft::Intro(player_data, text_generator);
                    scene = intro.execute();
                    break;
                }
            case ft::SceneType::Level1 :
                {
                    ft::Level1 level1 = ft::Level1(player_data, text_generator);
                    scene = level1.execute();
                    break;
                }
            default:
                break;
        }
        bn::core::update();
    }
}
