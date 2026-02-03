# Scott's Iris Keyboard Layout

Custom QMK firmware for Keebio Iris Rev5 with home-row modifiers and tmux integration.

## Features

- **Home-row modifiers**: Alt, Cmd, Ctrl, Shift on home row (ASDF / JKL;)
- **4 layers**: Base (QWERTY), Symbols, Tmux shortcuts, Numbers/RGB
- **Tmux integration**: Custom macros for window management (Ctrl+Space prefix)
- **RGB lighting**: Full control via Numbers layer

## Building

```bash
# From QMK firmware root directory
qmk compile -kb keebio/iris/rev5 -km scottleeroberts

# Or with Docker
./util/docker_build.sh keebio/iris/rev5:scottleeroberts
```

## Flashing

1. Copy resulting `keebio_iris_rev5_scottleeroberts.hex` to your machine
2. Open QMK Toolbox
3. Select the .hex file and choose atmega32u4
4. Enable "Auto Flash"
5. Press reset button on keyboard (on bottom of PCB)
6. **Important**: Flash each keyboard half independently by plugging each in via USB

## Layer Guide

### BASE (Layer 0)
Standard QWERTY with home-row modifiers:
- `A`: Alt when held
- `S`: Cmd/GUI when held
- `D`: TMUX layer when held
- `F`: Ctrl when held
- `G`: Shift when held
- `H`: Shift when held (right side)
- `J`: Ctrl when held (right side)
- `L`: Cmd/GUI when held (right side)
- `;`: Alt when held (right side)

### SYMB (Layer 1)
Symbols and navigation - activated by right thumb key:
- Top row: `! @ # $ % ^ & * ( ) |`
- Home row: `[ ] { }` and arrow keys
- Parentheses and question mark

### TMUX (Layer 2)
Tmux shortcuts - activated by holding `D` key:
- All macros send Ctrl+Space prefix
- Windows 1-5: Select tmux windows
- Copy mode: Enter tmux copy mode
- Split horizontal/vertical: Split panes
- New window: Create new tmux window

### NUMBERS (Layer 3)
Number pad, function keys, and RGB controls - activated by left thumb key:
- Right side: Number pad (789, 456, 123, 0)
- Left side: RGB controls (toggle, mode, hue, saturation, brightness)
- Top left: Reset/bootloader mode
- Media keys: Mute, Volume up/down

## Customization

To modify tmux prefix or add new shortcuts, edit `keymap.c`:
1. Add new keycode to `custom_keycodes` enum
2. Add case to `process_record_user` switch statement
3. Use `send_tmux_key("your_key")` helper function

## Changelog

- 2026-02: Modernized to latest QMK, hybrid macro system
- 2021-11: Original implementation with deprecated macro API
