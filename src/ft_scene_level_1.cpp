#include "ft_scene_level_1.h"
#include "ft_dialog.h"

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_optional.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_tiles_ptr.h"

#include "ft_dialog_scene_level1.h"

//assets
#include "bn_regular_bg_items_level1.h"

#include "bn_regular_bg_items_buns_bg.h"
#include "bn_sprite_items_hand_down.h"
#include "bn_sprite_items_bun_sprite.h"

#include "bn_regular_bg_items_blank_bg.h"
#include "bn_sprite_items_bun_side_sprite.h"
#include "bn_sprite_items_hotdog.h"
#include "bn_sprite_items_mustard.h"



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

    int grab_bun(bn::sprite_text_generator& text_generator){
        int timer = 0;
        int time_taken = 0;

        bool grabbed = false;
        bool finished = false;

        //dialog
        DialogSceneLevel1 dialog = DialogSceneLevel1(text_generator, "Move the bun to your workstation");

        bn::fixed x_offset = 0;

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::blank_bg.create_bg(0, 0);

        //sprites
        bn::sprite_ptr hand = bn::sprite_items::hand_down.create_sprite(-20, 55);
        hand.set_bg_priority(1);
        bn::sprite_ptr bun = bn::sprite_items::bun_sprite.create_sprite(16, -10);

        dialog.start();
        
         
        while(!finished){
            ++ timer;
            ++ time_taken;

            dialog.update();

            if(dialog.done()){
                if(bn::keypad::up_held()){
                    hand.set_y(hand.y() - 1);
                } else if (bn::keypad::down_held()){
                    hand.set_y(hand.y() + 1);
                }

                if(bn::keypad::right_held()){
                    hand.set_x(hand.x() + 1);
                } else if (bn::keypad::left_held()){
                    hand.set_x(hand.x() - 1);
                }

                if(bn::abs(bun.x() - 0) < 8 &&
                    bn::abs(bun.y() - 55) < 8){
                        finished = true;

                    }
                
                if(bn::keypad::a_pressed() &&
                    bn::abs(hand.x() - bun.x()) < 32 &&
                    bn::abs(hand.y() - bun.y()) < 16 &&
                    timer > 10){
                        grabbed = true;
                        timer = 0;
                        bun.set_y(hand.y());
                        hand.set_tiles(bn::sprite_items::hand_down.tiles_item().create_tiles(1));
                        x_offset = bun.x() - hand.x();
                }

            }

           

            if(grabbed){
                bun.set_x(hand.x() + x_offset);
                bun.set_y(hand.y());
            }

            bn::core::update();
        }

        int score = 0;
        if(time_taken < 120){
            score = 5;
        } else if(time_taken < 180){
            score = 4;
        } else if(time_taken < 240){
            score = 3;
        } else if(time_taken < 300){
            score = 2;
        } else {
            score = 1;
        }

        return score;
    }

    int place_dog(bn::sprite_text_generator& text_generator){
        int time_taken = 0;
        bool finished = false;

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::blank_bg.create_bg(0, 0);

        //dialog
        DialogSceneLevel1 dialog = DialogSceneLevel1(text_generator, "Place the hotdog in the bun.");
        dialog.start();

        //sprites
        bn::sprite_ptr hotdog = bn::sprite_items::hotdog.create_sprite(-8, -20);
        hotdog.set_bg_priority(2);

        bn::sprite_ptr bun = bn::sprite_items::bun_sprite.create_sprite(0, 55);
        bun.set_bg_priority(3);
        bn::sprite_ptr bun_front = bn::sprite_items::bun_sprite.create_sprite(0, 55,1);
        bun_front.set_bg_priority(1);

        while(!finished){
            ++time_taken;

            dialog.update();

            if(dialog.done()){
                if(bn::keypad::up_held()){
                    hotdog.set_y(hotdog.y() - 1);
                } else if (bn::keypad::down_held()){
                    hotdog.set_y(hotdog.y() + 1);
                }

                if(bn::keypad::right_held()){
                    hotdog.set_x(hotdog.x() + 1);
                } else if (bn::keypad::left_held()){
                    hotdog.set_x(hotdog.x() - 1);
                }

                if(bn::abs(hotdog.x() + 8 - bun.x()) < 16 &&
                    bn::abs(hotdog.y() - bun.y()) < 16){
                        finished = true;
                }

            }
            bn::core::update();
        }

        int score = 0;
        if(time_taken < 120){
            score = 5;
        } else if(time_taken < 180){
            score = 4;
        } else if(time_taken < 240){
            score = 3;
        } else if(time_taken < 300){
            score = 2;
        } else {
            score = 1;
        }

        return score;
    }

    int add_mustard(bn::sprite_text_generator& text_generator){
        int timer = 0;

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::blank_bg.create_bg(0, 0);

         //dialog
        DialogSceneLevel1 dialog = DialogSceneLevel1(text_generator, "Give it some mustard love. 'A' to squirt!");
        dialog.start();

        //sprites
        bn::sprite_ptr hotdog = bn::sprite_items::hotdog.create_sprite(0, 55);
        hotdog.set_bg_priority(2);

        bn::sprite_ptr bun = bn::sprite_items::bun_sprite.create_sprite(0, 55);
        bun.set_bg_priority(3);
        bn::sprite_ptr bun_front = bn::sprite_items::bun_sprite.create_sprite(0, 55,1);
        bun_front.set_bg_priority(1);

        bn::sprite_ptr mustard = bn::sprite_items::mustard.create_sprite(0, 16);
        mustard.set_bg_priority(0);


        while(!bn::keypad::start_pressed()){
            ++timer;
            dialog.update();

            if(dialog.done()){
                if(bn::keypad::right_held()){
                    mustard.set_x(mustard.x() + 1);
                } else if (bn::keypad::left_held()){
                    mustard.set_x(mustard.x() - 1);
                }
            }
                
            bn::core::update();
        }
    }

    int add_onion(bn::sprite_text_generator& text_generator){
        int timer = 0;

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::level1.create_bg(0, 0);
         
        while(!bn::keypad::start_pressed()){
            ++timer;
            bn::core::update();
        }
    }

    int serve(bn::sprite_text_generator& text_generator){
        int timer = 0;

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::level1.create_bg(0, 0);
         
        while(!bn::keypad::start_pressed()){
            ++timer;
            bn::core::update();
        }
    }

    SceneType Level1::execute(){
        int score = 0;
        show_loading_screen(*_text_generator);
        score += grab_bun(*_text_generator);
        score += place_dog(*_text_generator);
        score += add_mustard(*_text_generator);
        score += add_onion(*_text_generator);
        score += serve(*_text_generator);
        return SceneType::Level1;
    }
}