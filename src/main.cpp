#include "bn_bg_palettes.h"
#include "bn_color.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"

#include "bn_sprite_font.h"
#include "bn_sprite_items_common_variable_8x8_font.h"

namespace
{
    constexpr bn::color idle_color(3, 5, 9);
    constexpr bn::color active_color(4, 11, 8);

    void move_sprites(bn::vector<bn::sprite_ptr, 16>& sprites, int dx, int dy)
    {
        for(bn::sprite_ptr& sprite : sprites)
        {
            sprite.set_x(sprite.x() + dx);
            sprite.set_y(sprite.y() + dy);
        }
    }
}

int main()
{
    bn::core::init();
    bn::bg_palettes::set_transparent_color(idle_color);

    bn::sprite_font font(bn::sprite_items::common_variable_8x8_font);
    bn::sprite_text_generator text(font);
    text.set_center_alignment();

    bn::vector<bn::sprite_ptr, 32> static_text;
    text.generate(0, -48, "GRINDUNGEONIA", static_text);
    text.generate(0, -26, "G0.0", static_text);
    text.generate(0, -12, "DEV BUILD", static_text);
    text.generate(0, 46, "DPAD MOVES  A LIGHTS", static_text);

    bn::vector<bn::sprite_ptr, 16> input_marker;
    text.generate(0, 16, "[ INPUT ]", input_marker);

    while(true)
    {
        int dx = 0;
        int dy = 0;

        if(bn::keypad::left_held())  { dx = -1; }
        if(bn::keypad::right_held()) { dx = 1; }
        if(bn::keypad::up_held())    { dy = -1; }
        if(bn::keypad::down_held())  { dy = 1; }

        if(dx || dy)
        {
            move_sprites(input_marker, dx, dy);
        }

        bn::bg_palettes::set_transparent_color(bn::keypad::a_held() ? active_color : idle_color);
        bn::core::update();
    }
}
