#include "ft_scene_level_1.h"
#include "ft_dialog.h"

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_optional.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"

//assets
#include "bn_regular_bg_items_level1.h"


namespace ft
{
    Level1::Level1(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void show_loading_screen(bn::sprite_text_generator& text_generator){
        int timer = 0;

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::level1.create_bg(0, 0);
         
        while(!bn::keypad::start_pressed()){
            ++timer;
            bn::core::update();
        }
    }

    SceneType Level1::execute(){
        show_loading_screen(*_text_generator);
        return SceneType::Level1;
    }
}