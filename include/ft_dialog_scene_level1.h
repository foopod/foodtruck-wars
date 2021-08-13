#ifndef FT_DIALOG_SCENE_Level1_H
#define FT_DIALOG_SCENE_Level1_H

#include "bn_sprite_text_generator.h"

#include "ft_dialog.h"
#include "bn_string_view.h"

namespace ft
{
    class DialogSceneLevel1
    {
        private:
            bool _started = false;
            bool _done = false;
            bn::optional<Dialog> _dialog;
        public:
            DialogSceneLevel1(bn::sprite_text_generator& text_generator, bn::string_view line);
            void start();
            bool has_started();
            bool done();
            void update();
    };
}

#endif