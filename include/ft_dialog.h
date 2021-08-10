#ifndef FT_DIALOG_H
#define FT_DIALOG_H

#include "bn_string_view.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"

namespace ft
{
    enum class Speaker
    {
        Player,
        Cop
    };

    enum class Emotion
    {
        Happy,
        Sad,
        Grin
    };

    class Decision
    {
        private:
            bn::vector<bn::string_view, 4> _options;
            bn::string_view _outcome;
        public:
            Decision(bn::vector<bn::string_view, 4> options);
    };

    class DialogLine
    {
        private:
            Speaker _speaker;
            Emotion _emotion;
            bn::string_view _text;
            bn::optional<Decision> _decision;
        public:
            DialogLine(Speaker speaker, Emotion emotion, bn::string_view text);
            DialogLine(Speaker speaker, Emotion emotion, bn::string_view text, Decision decision);
            void set_speaker(Speaker speaker);
            void set_emotion(Emotion emotion);
            void set_text(bn::string_view text);
            Speaker speaker();
            Emotion emotion();
            bn::string_view text();
    };

    class Dialog
    {
        private:
            bn::sprite_text_generator* _text_generator;
            bn::vector<DialogLine, 32>* _dialog_lines;
            bn::sprite_ptr _dialog_bgs[4];
            bn::optional<bn::sprite_ptr> _speaker_sprite;
            bn::vector<bn::sprite_ptr, 20> _top_text_sprites;
            bn::vector<bn::sprite_ptr, 20> _middle_text_sprites;
            bn::vector<bn::sprite_ptr, 20> _bottom_text_sprites;

            int _currentLine;
            int _currentChar;
            bn::string_view _currentChars = "";

            bool _done = false;

            bool _has_decision = false;
            bn::string_view _last_decision_outcome = "";
        public:
            Dialog(bn::vector<DialogLine, 32>& dialog_lines, bn::sprite_text_generator& text_generator);
            void update();
            bool done();
            void set_visible(bool visible);
    };
}

#endif