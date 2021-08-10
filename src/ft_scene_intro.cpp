#include "ft_scene_intro.h"
#include "ft_dialog.h"

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_display.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_optional.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_blending_actions.h"


#include "ft_dialog_scene_intro.h"

//assets
#include "bn_regular_bg_items_intro_bg.h"
#include "bn_sprite_items_van_80.h"
#include "bn_sprite_items_police_80.h"
#include "bn_sprite_items_police_person.h"
#include "bn_sprite_items_menu_bg.h"


namespace ft
{
    Intro::Intro(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    enum class PlayerActions{
        StartGame,
        Options
    };

    //utility for looping map width
    bn::fixed loop(bn::fixed current, bn::fixed increment) {
        current += increment;
        if(current > 256) {
            return 0;
        } 
        else if(current < 0) {
            return 256;
        } 
        else {
            return current;
        }
    }

    int get_player_selection(int currentInput){
        if(bn::keypad::left_pressed()){
            --currentInput;
        } else if(bn::keypad::right_pressed()){
            ++currentInput;
        }
        if(currentInput > 2){
            currentInput = 0;
        } else if(currentInput < 0){
            currentInput = 2;
        }
        return currentInput;
    }

    SceneType show_title_screen(bn::sprite_text_generator& text_generator)
    {

        // map
        bn::regular_bg_ptr map = bn::regular_bg_items::intro_bg.create_bg(0, 0);

        // van sprite
        bn::sprite_ptr van = bn::sprite_items::van_80.create_sprite(-80, 60);
        van.set_tiles(bn::sprite_items::van_80.tiles_item().create_tiles(48));
        van.set_bg_priority(1);

        // police car sprite
        bn::sprite_ptr police = bn::sprite_items::police_80.create_sprite(-300, 60);
        bn::sprite_animate_action<2> police_animate_action = bn::create_sprite_animate_action_forever(
                            police, 10, bn::sprite_items::police_80.tiles_item(), 0,1);

        // police sprite
        bn::sprite_ptr police_person = bn::sprite_items::police_person.create_sprite(-20, 55);
        police_person.set_visible(false);
        police_person.set_bg_priority(0);
        bn::sprite_animate_action<4> police_person_animate_action = bn::create_sprite_animate_action_forever(
                            police_person, 15, bn::sprite_items::police_person.tiles_item(), 0,1,2,3);


        // sprite actions
        bn::optional<bn::sprite_move_to_action> van_move_action;
        bn::optional<bn::sprite_move_to_action> police_move_action;
        bn::optional<bn::sprite_move_to_action> police_person_move_action;

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        // text bg sprites
        bn::sprite_ptr menu_bg[6] = {
            bn::sprite_items::menu_bg.create_sprite(8, 40, 0),
            bn::sprite_items::menu_bg.create_sprite(24, 40, 1),
            bn::sprite_items::menu_bg.create_sprite(40, 40, 1),
            bn::sprite_items::menu_bg.create_sprite(56, 40, 1),
            bn::sprite_items::menu_bg.create_sprite(72, 40, 1),
            bn::sprite_items::menu_bg.create_sprite(88, 40, 0)
        };
        menu_bg[5].set_horizontal_flip(true);

        //dialog
        DialogSceneIntro intro_dialog = DialogSceneIntro(text_generator);

        // hbe for scrolling bg
        bn::array<bn::fixed, bn::display::height()> horizontal_deltas;
        bn::regular_bg_position_hbe_ptr horizontal_hbe =
                bn::regular_bg_position_hbe_ptr::create_horizontal(map, horizontal_deltas);

        bn::fixed offset_bottom = 0;
        bn::fixed offset_mid_bottom = 0;
        bn::fixed offset_mid_top = 0;
        bn::fixed offset_top = 0;

        bn::fixed offset_mid_top_speed = 0.2;
        bn::fixed offset_mid_bottom_speed = 0.3;
        bn::fixed offset_bottom_speed = 2;

        int timer = 0;

        bn::random random = bn::random();

        int menuOptionSelected = 0;

        // text sprites
        bn::optional<bn::blending_transparency_alpha_to_action> transparency_action;
        

        while(true){ 
            //menu item selection
            menuOptionSelected = get_player_selection(menuOptionSelected);
            if(!transparency_action.has_value()){
                text_sprites.clear();
                if(menuOptionSelected == 0){
                    text_generator.generate(0, 40, "< New Game >", text_sprites);
                } else if(menuOptionSelected == 1){
                    text_generator.generate(0, 40, "< Options  >", text_sprites);
                } else {
                    text_generator.generate(0, 40, "< Credits  >", text_sprites);
                }
            }

            
            intro_dialog.update();

            if(menuOptionSelected == 0 && bn::keypad::a_pressed() && !van_move_action.has_value()){
                for(bn::sprite_ptr sprite : text_sprites){
                    sprite.set_bg_priority(3);
                    sprite.set_blending_enabled(true);
                }
                for(bn::sprite_ptr sprite : menu_bg){
                    sprite.set_blending_enabled(true);
                }
                timer = 0;
                transparency_action = bn::blending_transparency_alpha_to_action(100, 0);
                van_move_action = bn::sprite_move_to_action(van, 400, 40, 55);
                police_move_action = bn::sprite_move_to_action(police, 400, -20, 55);
            }

            if(police_move_action.has_value() && police_move_action->done() && !police_person.visible()){
                if(timer % 500 == 0){
                    police_person.set_visible(true);
                    police_person_move_action = bn::sprite_move_to_action(police_person, 250, 65, 55);
                }
            }



            if(van_move_action.has_value() && !van_move_action->done()){
                van_move_action->update();
            }

            if(transparency_action.has_value() && !transparency_action->done()){
                transparency_action->update();
            }

            if(police_move_action.has_value() && !police_move_action->done()){
                police_move_action->update();
            }

            if(police_person_move_action.has_value() && !police_person_move_action->done()){
                police_person_move_action->update();
            }

            
            police_animate_action.update();
            if(police_person.visible() && police_person_move_action.has_value() && !police_person_move_action->done()){
                police_person_animate_action.update();
            } else if(police_person.visible() && !intro_dialog.has_started() && !intro_dialog.done()){
                police_person.set_tiles(bn::sprite_items::police_person.tiles_item().create_tiles(4));
                intro_dialog.start();
            }

            if(intro_dialog.done() && police_person_move_action->done()){
                police_person.set_horizontal_flip(true);
                police_person_move_action = bn::sprite_move_to_action(police_person, 250, -20, 55);
            } else if(intro_dialog.done() && police_person.x() < -19){
                police_person.set_visible(false);
            }

            if(intro_dialog.done() && !police_person.visible()){
                police_move_action = bn::sprite_move_to_action(police, 140, -300, 55);
                van_move_action = bn::sprite_move_to_action(van, 80, -60, 55);
                offset_mid_top_speed = 0.2;
                offset_mid_bottom_speed = 0.3;
                offset_bottom_speed = 2;
            }
            
            if(intro_dialog.done() && !police_person.visible() && van.x() < -55){
                return SceneType::Level1;
            }

            //hbe effects
            // offset_top = loop(offset_top, 0.5); //top doesn't move
            offset_mid_top = loop(offset_mid_top, offset_mid_top_speed);
            offset_mid_bottom = loop(offset_mid_bottom, offset_mid_bottom_speed);
            offset_bottom = loop(offset_bottom, offset_bottom_speed);

            for(int index = 0, limit = bn::display::height()    ; index < limit; ++index){
                if( index > 106){
                    horizontal_deltas[index] = offset_bottom;
                } 
                else if(index > 98){
                    horizontal_deltas[index] = offset_mid_bottom;
                }
                else if(index > 86){
                    horizontal_deltas[index] = offset_mid_top;
                }
                else if(index > 68){
                    horizontal_deltas[index] = offset_top;
                }
            }

            horizontal_hbe.reload_deltas_ref();

            if(!van_move_action.has_value() && !intro_dialog.done()){

                // subtle van movement before animation begins
                if(timer % 200 == 0){
                    van.set_tiles(bn::sprite_items::van_80.tiles_item().create_tiles(47));
                } else if(timer % 300 == 0){
                    van.set_tiles(bn::sprite_items::van_80.tiles_item().create_tiles(48));
                } else if(timer % 400 == 0){
                    van.set_tiles(bn::sprite_items::van_80.tiles_item().create_tiles(49));
                }
                if(random.get() % 100 < 3){
                    van.set_y(van.y() - 1);
                } else {
                    van.set_y(60);
                }
            } else {
                //slow down bg
                if(offset_mid_top_speed > 0){
                    offset_mid_top_speed -= 0.001;
                } else {
                    offset_mid_top_speed = 0;
                }

                if(offset_mid_bottom_speed > 0){
                    offset_mid_bottom_speed -= 0.001;
                } else {
                    offset_mid_bottom_speed = 0;
                }

                if(offset_bottom_speed > 0){
                    offset_bottom_speed -= 0.005;
                } else {
                    offset_bottom_speed = 0;
                }
            }

            ++timer;
            bn::core::update();
        }
    }

    SceneType Intro::execute(){
        return show_title_screen(*_text_generator);
    }

    
}