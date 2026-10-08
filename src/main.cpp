#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_crypt.h"
#include "bn_sprite_items_hero.h"
#include "bn_sprite_items_fiend.h"
#include "bn_sprite_items_slash.h"
#include "bn_sprite_items_common_variable_8x8_font.h"
#include "bn_sprite_font.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_vector.h"
#include "bn_fixed.h"
#include "bn_math.h"

int main()
{
    bn::core::init();
    bn::regular_bg_ptr room = bn::regular_bg_items::crypt.create_bg(0, 0);
    bn::sprite_ptr player = bn::sprite_items::hero.create_sprite(-56, 0);
    bn::sprite_ptr enemy = bn::sprite_items::fiend.create_sprite(42, -4);
    bn::sprite_ptr slash = bn::sprite_items::slash.create_sprite(0, 0);
    slash.set_visible(false);
    bn::sprite_font font(bn::sprite_items::common_variable_8x8_font);
    bn::sprite_text_generator text(font);
    bn::vector<bn::sprite_ptr, 32> labels;
    text.generate(-112, -73, "GRINDUNGEONIA G0", labels);
    text.generate(-112, 68, "DPAD MOVE  A STRIKE", labels);
    bn::fixed px = -56, py = 0;
    int facing = 1, attack = 0, cooldown = 0, hp = 5, enemy_hp = 3, enemy_hit = 0;
    while(true)
    {
        if(bn::keypad::left_held()) { px -= 1; facing = -1; }
        if(bn::keypad::right_held()) { px += 1; facing = 1; }
        if(bn::keypad::up_held()) { py -= 1; }
        if(bn::keypad::down_held()) { py += 1; }
        if(px < -96) px = -96;
        if(px > 96) px = 96;
        if(py < -54) py = -54;
        if(py > 50) py = 50;
        player.set_position(px, py);
        player.set_horizontal_flip(facing < 0);
        if(cooldown > 0) --cooldown;
        if(attack > 0) --attack;
        if(enemy_hit > 0) --enemy_hit;
        if(bn::keypad::a_pressed() && cooldown == 0)
        {
            attack = 9; cooldown = 17;
            if(enemy_hp > 0 && bn::abs(px + facing * 14 - enemy.x()) < 24 && bn::abs(py - enemy.y()) < 19)
            {
                --enemy_hp; enemy_hit = 8;
                if(enemy_hp == 0) enemy.set_visible(false);
            }
        }
        slash.set_visible(attack > 0);
        slash.set_position(px + facing * 14, py);
        slash.set_horizontal_flip(facing < 0);
        if(enemy_hit > 0) enemy.set_horizontal_flip(enemy_hit % 2);
        if(enemy_hp > 0 && bn::abs(px - enemy.x()) < 12 && bn::abs(py - enemy.y()) < 12 && cooldown == 0)
        {
            if(hp > 0) --hp;
            cooldown = 35;
        }
        if(hp == 0 && bn::keypad::start_pressed()) { hp = 5; enemy_hp = 3; enemy.set_visible(true); px = -56; py = 0; }
        bn::core::update();
    }
}
