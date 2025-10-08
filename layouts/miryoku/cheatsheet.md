# Miryoku_2 (DZ60RGB ANSI) — One‑Page Cheat Sheet

Layer colors (RGB Matrix):
- BASE white
- NAV blue
- MOUSE yellow
- MEDIA purple
- NUM pink
- SYM green
- FUN red
- GAME off

Legend:
- HRM_X = Mod‑Tap on home row. Tap = letter, Hold = modifier.
  - Left: A=Alt, R=Gui, S=Shift, T=Ctrl
  - Right: N=Ctrl, E=Shift, I=Gui, O=Alt
- LT(LAYER, KEY): Tap = KEY, Hold = switch to LAYER
  - TME_ESC=Esc/Media, TN_SPC=Space/Nav, TMO_TAB=Tab/Mouse
  - TS_ENT=Enter/Sym, TN_BSP=Backspace/Num, TF_DEL=Delete/Fun
- Tap‑dance:
  - Double‑tap “Boot” → reset keyboard
  - Double‑tap a layer TD key (e.g., “U_BASE”, “U_NUM”, …) → set Default Layer

## Base (white)
- Letters: Q W F P G | J L U Y '
- Home‑row mods as above
- Right home row has ALT_MOD key (hold = Alt; while held: tap , → Alt+Tab; tap M → Shift+Alt+Tab)
- Thumbs: Esc/Media, Space/Nav, Tab/Mouse | Enter/Sym, Bksp/Num, Del/Fun

## Nav (blue)
- Arrows: H J K L
- Home/End/PgDn/PgUp + Insert
- CW_TOGG on left of arrows
- Top row has TD keys to set default layer

## Mouse (yellow)
- Cursor: H/J/K/L = ← ↓ ↑ →
- Wheel: L/D/U/R on next row (MS_WHLL/D/U/R)
- Thumbs: BTN2, BTN1, BTN3

## Media (purple)
- Playback: Prev, Vol‑, Vol+, Next
- Thumbs: Stop, Play/Pause, Mute
- Extras: UG_TOGG (RGB), DB_TOGG (debug), OU_AUTO (auto‑shift)

## Num (pink) — numpad under left hand
- Row1: [ 7 8 9 ]
- Row2: ; 4 5 6 =
- Row3: ` 1 2 3 \
- Row4: . 0 -
- Right side carries TD keys and modifiers

## Sym (green) — mirrors Num with symbols
- Row1: { & * ( }
- Row2: : $ % ^ +
- Row3: ~ ! @ # |
- Row4: ( ) _

## Fun (red)
- F‑keys: F12 F7 F8 F9 | F11 F4 F5 F6 | F10 F1 F2 F3
- Print/ScrLk/Pause
- Bottom left: App, Space, Tab (plain)

## Game (off)
- Same letters as Base, but plain (no HRM/LT on left thumbs); right thumbs still Enter/Sym, Bsp/Num, Del/Fun.

## Combos (thumbs)
- Base: Enter + Bksp → Del/Fun
- Base: Space + Tab → Esc/Media
- Nav: Enter + Bksp → Del
- Mouse: BTN2 + BTN1 → BTN3
- Media: Stop + Play → Mute
- Num: 0 + - → .
- Sym: ) + _ → (
- Fun: Space + Tab → App
- Special: Bksp/Num + Del/Fun (on Base) → set Default Layer = BASE

## Caps Word
- Toggle on Nav (CW_TOGG). While active: letters shift; numbers/backspace/delete/_/: continue it.

## Build/flash
```powershell
qmk compile -kb dztech/dz60rgb_ansi -km miryoku_2
qmk flash   -kb dztech/dz60rgb_ansi -km miryoku_2
```

## Optional: generate an SVG card from this keymap
```powershell
pip install keymap-drawer
qmk c2json -kb dztech/dz60rgb_ansi -km miryoku_2 > keymap.json
keymap-drawer draw --qmk keymap.json -o miryoku_2.svg
```
