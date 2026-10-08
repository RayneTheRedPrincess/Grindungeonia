# Current State

## G0.0 Project Bootstrap: VERIFIED

Verified 2026-10-08 UTC in the active development environment:
- Development kit package checksum list: 166/166 entries passed.
- devkitARM: GCC/G++ 16.1.0 executes.
- Butano: 21.9.0 builds with the bundled toolchain.
- Bundled mGBA 0.10.5 libretro core executes GBA ROMs headlessly.
- Native capture pipeline outputs 240x160 PNG frames.
- Kit smoke test rebuilt Butano's sprites example and verified scripted input changes output.
- `Grindungeonia.gba` builds and boots.
- G0.0 screen displays GRINDUNGEONIA / G0.0 / DEV BUILD.
- D-pad moves the on-screen input marker; A changes the background, verified by scripted capture.

## Direction Pivot: CANONICAL

On 2026-10-08 the project target changed before G0 architecture was committed:
- Grindungeonia is now a GBA-first loot/buildcraft ARPG rather than a Sephiria-like action game with ARPG progression layered onto it.
- The target fantasy is the full kill -> loot -> build -> harder-content loop, translated to native GBA controls, screen size and hardware budgets.
- Path of Exile remains a mechanical/genre reference only. Grindungeonia uses original content and its own GBA-appropriate solutions.
- Existing verified G0.0 toolchain/build/capture work remains valid.
- Experimental local G0 combat-room work from before this pivot is not considered canonical until rebuilt against the new acceptance target.

Next milestone: **G0 Combat Room**, proving movement, a primary skill, enemy-pack combat, HP/resource, death/restart, loot drop, equip/inspect and a visible stat improvement in one tiny playable room.
