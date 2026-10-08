# G0 Combat Verification (2026-10-08)

The local G0 combat revision builds with devkitARM/Butano and boots in bundled mGBA.

Verified in emulator:
- Native 240x160 captures at frame 100 (idle) and frame 140 (scripted movement and three A presses).
- Scripted sequence: RIGHT held frames 0-74, A pressed frames 75, 95 and 115.
- Combat screenshot visibly reports ENEMY DEFEATED; idle and combat captures have different SHA-256 digests.
- The local revision also adds pursuit AI, collision with pillars, player HP damage, invulnerability, player death/restart, and a bobbing movement effect.

**Repository status caveat:** The locally tested revised `src/main.cpp` has not yet been synced to GitHub. The prior G0 source on main is older. This document records the verified local test, not a claim that main already contains the revision.

Still pending: final art, directional animation frames, HP UI updates, loot and equipment, enemy packs.
