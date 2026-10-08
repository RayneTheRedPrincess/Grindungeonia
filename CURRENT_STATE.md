# Current State

## G0.0: VERIFIED
The 2026-10-08 toolchain bootstrap, checksum verification, mGBA native capture and input smoke test remain valid.

## Game direction
Original GBA hub-and-modular-dungeon action RPG with Zenonia-inspired direct combat and PoE-inspired buildcraft. No overworld. One hub town, expandable room-piece dungeon library.

## G0 Combat and Visual Prototype: PARTIALLY VERIFIED (2026-10-08)
- Built a GBA ROM using Butano 21.9.0 and devkitARM 16.1.0.
- Emulator captured native 240x160 idle and scripted attack frames.
- Scripted RIGHT movement and three A presses yield ENEMY DEFEATED.
- Player upgraded from 16x16 to 32x32 sprites, with six frames: front/back/side times two walking phases, with side mirrored for left.
- Current C++ includes simple enemy pursuit, melee, HP/death/restart and obstacle collision.
- Visual assets are diagnostic, not approved final art.
- Known defects: HP label does not update numerically; melee direction uses horizontal facing even when moving up/down; sprite animations remain minimal. No loot/equip or enemy packs yet.

Next: repair combat-facing/HP HUD, add attack and hit poses, verify player death/restart, then implement generated loot and equip.
