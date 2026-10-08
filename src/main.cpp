#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_crypt.h"
#include "bn_sprite_items_hero_anim.h"
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
    bn::sprite_ptr player = bn::sprite_items::hero_anim.create_sprite(-56, 0);
    bn::sprite_ptr enemy = bn::sprite_items::fiend.create_sprite(42, -4);
    bn::sprite_ptr slash = bn::sprite_items::slash.create_sprite(0, 0);
    slash.set_visible(false);
    bn::sprite_font font(bn::sprite_items::common_variable_8x8_font);
    bn::sprite_text_generator text(font);
    bn::vector<bn::sprite_ptr, 32> labels;
    text.generate(-112, -73, "GRINDUNGEONIA G0", labels);
    text.generate(-112, 68, "DPAD MOVE  A STRIKE", labels);
    bn::vector<bn::sprite_ptr, 16> hearts;
    text.generate(44, -73, "HP 5", hearts);
    bn::vector<bn::sprite_ptr, 16> death_text;
    text.generate(0, -28, "FALLEN  START RETRY", death_text);
    for(auto& s : death_text) s.set_visible(false);
    bn::vector<bn::sprite_ptr, 16> clear_text;
    text.generate(0, -28, "ENEMY DEFEATED", clear_text);
    for(auto& s : clear_text) s.set_visible(false);
    bn::fixed px = -56, py = 0;
    bn::fixed ex = 42, ey = -4;
    int facing = 1, direction = 2, walk_ticks = 0, attack = 0, cooldown = 0, hp = 5, enemy_hp = 3;
    int enemy_hit = 0, invulnerable = 0, enemy_attack_cd = 0, frame = 0;
    while(true)
    {
        ++frame;
        if(hp > 0)
        {
            bn::fixed dx = 0, dy = 0;
            if(bn::keypad::left_held()) { dx -= 1; facing = -1; direction = 2; }
            if(bn::keypad::right_held()) { dx += 1; facing = 1; direction = 2; }
            if(bn::keypad::up_held()) { dy -= 1; direction = 1; }
            if(bn::keypad::down_held()) { dy += 1; direction = 0; }
            bn::fixed nx = px + dx, ny = py + dy;
            if(nx < -96) nx = -96;
            if(nx > 96) nx = 96;
            if(ny < -54) ny = -54;
            if(ny > 50) ny = 50;
            bool blocked = (bn::abs(nx + 57) < 15 && bn::abs(ny + 20) < 15) ||
                           (bn::abs(nx - 73) < 15 && bn::abs(ny - 4) < 15) ||
                           (bn::abs(nx) < 15 && bn::abs(ny - 36) < 15);
            if(!blocked) { px = nx; py = ny; }
            if(dx != 0 || dy != 0) ++walk_ticks; else walk_ticks = 0;
            if(cooldown > 0) --cooldown;
            if(attack > 0) --attack;
            if(invulnerable > 0) --invulnerable;
            if(enemy_hit > 0) --enemy_hit;
            if(enemy_attack_cd > 0) --enemy_attack_cd;
            if(bn::keypad::a_pressed() && cooldown == 0)
            {
                attack = 9;
                cooldown = 17;
                if(enemy_hp > 0 && bn::abs(px + facing * 14 - ex) < 24 && bn::abs(py - ey) < 19)
                {
                    --enemy_hp;
                    enemy_hit = 10;
                    if(enemy_hp == 0)
                    {
                        enemy.set_visible(false);
                        for(auto& s : clear_text) s.set_visible(true);
                    }
                }
            }
            if(enemy_hp > 0 && enemy_hit == 0 && frame % 3 == 0)
            {
                if(bn::abs(px - ex) > 9) ex += (px > ex) ? bn::fixed(0.5) : bn::fixed(-0.5);
                if(bn::abs(py - ey) > 9) ey += (py > ey) ? bn::fixed(0.5) : bn::fixed(-0.5);
            }
            if(enemy_hp > 0 && bn::abs(px - ex) < 13 && bn::abs(py - ey) < 13 &&
               invulnerable == 0 && enemy_attack_cd == 0)
            {
                --hp;
                invulnerable = 50;
                enemy_attack_cd = 65;
                for(auto& s : hearts) s.set_visible(false);
                if(hp == 0) for(auto& s : death_text) s.set_visible(true);
            }
        }
        if(hp == 0 && bn::keypad::start_pressed())
        {
            hp = 5; enemy_hp = 3; px = -56; py = 0; ex = 42; ey = -4;
            attack = 0; cooldown = 0; enemy_hit = 0; invulnerable = 0;
            enemy.set_visible(true);
            for(auto& s : death_text) s.set_visible(false);
            for(auto& s : clear_text) s.set_visible(false);
            for(auto& s : hearts) s.set_visible(true);
        }
        player.set_position(px, py + ((frame / 12) % 2 && hp > 0 ? 1 : 0));
        player.set_horizontal_flip(direction == 2 && facing < 0);
        player.set_tiles(bn::sprite_items::hero_anim.tiles_item(), direction * 2 + ((walk_ticks / 9) % 2));
        player.set_visible(invulnerable == 0 || frame % 4 < 2);
        enemy.set_position(ex, ey);
        enemy.set_horizontal_flip(enemy_hit > 0 && frame % 4 < 2);
        slash.set_visible(attack > 0 && hp > 0);
        slash.set_position(px + facing * 14, py);
        slash.set_horizontal_flip(facing < 0);
        bn::core::update();
    }
}
