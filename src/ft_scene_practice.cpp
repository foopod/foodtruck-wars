#include "ft_scene_practice.h"
#include "ft_dialog.h"

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_optional.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"



namespace ft
{
    Practice::Practice(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void show_explanation(bn::sprite_text_generator& text_generator){
        int timer = 0;

         
        while(timer < 180){
            ++timer;
            bn::core::update();
        }
    }

    SceneType Practice::execute(){
        return SceneType::Level1;
    }
}