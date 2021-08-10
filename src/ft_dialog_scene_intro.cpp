#include "ft_dialog_scene_intro.h"

#include "ft_dialog.h"

namespace ft
{
    DialogSceneIntro::DialogSceneIntro(bn::sprite_text_generator& text_generator){

        bn::vector<DialogLine, 32> dialog_lines_intro;
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Grin, "GOOD AFTERNOON!"));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Your left brake light is out."));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Sad, "I wanted to make sure you knew."));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Can I see your license?"));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Thanks!"));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Okay great, that's all I need."));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Oh"));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "You're taking a Weenie Wagon to Tacotown?"));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Good Luck with that."));
        dialog_lines_intro.push_back(DialogLine(Speaker::Cop, Emotion::Happy, "Drive safe now."));
        _dialog = Dialog(dialog_lines_intro, text_generator);
        _dialog->set_visible(false);
    }

    void DialogSceneIntro::start(){
        _started = true;
        _dialog->set_visible(true);
    }

    bool DialogSceneIntro::has_started(){
        return _started;
    }

    bool DialogSceneIntro::done(){
        return _done;
    }

    void DialogSceneIntro::update(){
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
