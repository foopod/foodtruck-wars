#ifndef FT_DIALOG_SCENE_INTRO_H
#define FT_DIALOG_SCENE_INTRO_H

#include "bn_sprite_text_generator.h"

#include "ft_dialog.h"

namespace ft
{
    class DialogSceneIntro
    {
        private:
            bool _started = false;
            bool _done = false;
            bn::optional<Dialog> _dialog;
        public:
            DialogSceneIntro(bn::sprite_text_generator& text_generator);
            void start();
            bool has_started();
            bool done();
            void update();
    };
}

#endif