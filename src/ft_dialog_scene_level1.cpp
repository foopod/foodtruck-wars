#include "ft_dialog_scene_level1.h"

#include "ft_dialog.h"

namespace ft
{
    DialogSceneLevel1::DialogSceneLevel1(bn::sprite_text_generator& text_generator, bn::string_view line){

        bn::vector<DialogLine, 32> dialog_lines;
        dialog_lines.push_back(DialogLine(Speaker::Bob, Emotion::Grin, line));
        // dialog_lines.push_back(DialogLine(Speaker::Bob, Emotion::Grin, "Move the bun to your work area!"));
        _dialog = Dialog(dialog_lines, text_generator);
        _dialog->set_visible(false);
    }

    void DialogSceneLevel1::start(){
        _started = true;
        _dialog->set_visible(true);
    }

    bool DialogSceneLevel1::has_started(){
        return _started;
    }

    bool DialogSceneLevel1::done(){
        return _done;
    }

    void DialogSceneLevel1::update(){
        if(_started && !_done){
            if(_dialog.has_value() && !_dialog->done()){
                _dialog->update();
            } else if(_dialog.has_value() && _dialog->done()){
                _done = true;
                _dialog->set_visible(false);
            }
        }
    }

}
