# Scott's Iris Keyboard Layout

Custom QMK firmware for Keebio Iris Rev5 with home-row modifiers and tmux integration.

## Features

- **Home-row modifiers**: Alt, Cmd, Ctrl, Shift on home row (ASDF / JKL;)
- **4 layers**: Base (QWERTY), Symbols, Tmux shortcuts, Numbers/RGB
- **Tmux integration**: Custom macros for window management (Ctrl+Space prefix)
- **RGB lighting**: Full control via Numbers layer
- **Home-row combos**: J+H = Escape, K+J = Backspace, D+F = Tab
- **Key overrides**: Shift+Backspace = Delete
- **Chordal Hold + Flow Tap**: Anti-misfire for home-row mods
- **Modern QMK**: Updated for latest QMK firmware (Feb 2026)

## Quick Start

### Building and Flashing

**Complete instructions: [MANUAL_BUILD_FLASH.md](MANUAL_BUILD_FLASH.md)**

The manual provides full step-by-step instructions for:
- Installing Docker and dfu-programmer (Ubuntu/Debian or Arch/Manjaro)
- Building firmware using QMK's official Docker image
- Flashing both keyboard halves with dfu-programmer
- Troubleshooting common issues

**Quick reference** (if you've already done the setup):
```bash
# Build (from build/qmk_firmware directory)
docker run --rm -v $(pwd):/qmk_firmware -w /qmk_firmware ghcr.io/qmk/qmk_cli \
  make keebio/iris/rev5:scottleeroberts

# Flash each half (press RESET button first)
sudo dfu-programmer atmega32u4 erase --force
sudo dfu-programmer atmega32u4 flash --force keebio_iris_rev5_scottleeroberts.hex
sudo dfu-programmer atmega32u4 reset
```

## Layer Guide

### BASE (Layer 0) - Default QWERTY

Standard QWERTY layout with home-row modifiers:

```
┌───┬───┬───┬───┬───┬───┐           ┌───┬───┬───┬───┬───┬───┐
│Esc│ 1 │ 2 │ 3 │ 4 │ 5 │           │ 6 │ 7 │ 8 │ 9 │ 0 │BkSp│
├───┼───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┼───┤
│ ` │ Q │ W │ E │ R │ T │           │ Y │ U │ I │ O │ P │ - │
├───┼───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┼───┤
│Ctl│ A │ S │ D │ F │ G │           │ H │ J │ K │ L │ ; │ ' │
│   │Alt│Cmd│Tmx│Ctl│Sft│           │Sft│Ctl│   │Cmd│Alt│   │
├───┼───┼───┼───┼───┼───┼───┐   ┌───┼───┼───┼───┼───┼───┼───┤
│Sft│ Z │ X │ C │ V │ B │Ent│   │   │ N │ M │ , │ . │ / │ = │
└───┴───┴───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┴───┴───┘
            ┌───┬───┬───┐           ┌───┬───┬───┐
            │Cmd│Num│Ent│           │Spc│Sym│Tab│
            └───┴───┴───┘           └───┴───┴───┘
```

**Home-row modifiers** (tap for letter, hold for modifier):
- **Left hand:** Alt(A), Cmd(S), Tmux-layer(D), Ctrl(F), Shift(G)
- **Right hand:** Shift(H), Ctrl(J), Cmd(L), Alt(;)

### SYMB (Layer 1) - Symbols & Navigation

Activated by holding right thumb key:

- **Top row:** `~ ! @ # $ % ^ & * ( ) |`
- **Home row:** `[ ] { }` + Arrow keys (←↓↑→)
- **Bottom row:** Parentheses `( )`
- **Special:** `? \` on right side

### TMUX (Layer 2) - Terminal Multiplexer

Activated by holding D key. All macros send Ctrl+Space prefix:

| Key | Action | Sends |
|-----|--------|-------|
| U | Copy mode | Ctrl+Space [ |
| I | Split horizontal | Ctrl+Space " |
| O | Split vertical | Ctrl+Space % |
| J | Window 1 | Ctrl+Space 1 |
| K | Window 2 | Ctrl+Space 2 |
| L | Window 3 | Ctrl+Space 3 |
| ; | Window 4 | Ctrl+Space 4 |
| ' | Window 5 | Ctrl+Space 5 |
| N | New window | Ctrl+Space c |

### NUMBERS (Layer 3) - Numpad & RGB

Activated by holding left thumb key:

**Right side - Number pad:**
```
    7  8  9
    4  5  6
    1  2  3
Tab 0
```

**Left side - RGB controls:**
- **Row 2:** Plain mode (static), Breathing mode
- **Row 3:** Toggle, Next mode, Hue↑, Speed↑, Brightness↑
- **Row 4:** Prev mode, Hue↓, Speed↓, Brightness↓

**Top left:** Reset/Bootloader (QK_BOOT)

**Right side - Media:** Mute, Volume Up/Down

## Configuration Details

### Split Keyboard Settings

- **Handedness:** EE_HANDS (stored in EEPROM per half)
- **Communication:** Serial (default for Iris Rev5)
- **Each half must be flashed independently**

### Home-Row Modifiers

- **Tapping term:** 200ms (QMK default)
- **Chordal Hold:** Same-hand tap-hold + next key resolves as tap (prevents misfires)
- **Flow Tap:** Keys pressed within 150ms of each other always tap (fast typing protection)

### Combos

Press two keys simultaneously for common actions:

| Combo | Action |
|-------|--------|
| J + H | Escape |
| K + J | Backspace |
| D + F | Tab |

### Key Overrides

| Input | Output |
|-------|--------|
| Shift + Backspace | Delete |

### RGB Lighting

- **LEDs:** 12 per side (24 total)
- **Default mode:** Static light
- **Effects:** Breathing, Rainbow, Snake, Knight, and more
- **Controls:** Hue, Saturation, Value (brightness), Speed
- **Settings persist** across reboots

### Tmux Configuration

**Default prefix:** Ctrl+Space (customize in keymap.c if needed)

All tmux macros use the helper function:
```c
void send_tmux_key(const char* key) {
    SEND_STRING(SS_LCTL(" "));  // Ctrl+Space prefix
    send_string(key);
}
```

To change the prefix, modify the `send_tmux_key` function.

## Customization

### Adding New Tmux Macros

1. Add keycode to enum in `keymap.c`:
   ```c
   enum custom_keycodes {
       TMUX_WIN_1 = SAFE_RANGE,
       TMUX_YOUR_MACRO,  // Add here
       // ...
   };
   ```

2. Add case to `process_record_user`:
   ```c
   case TMUX_YOUR_MACRO:
       send_tmux_key("x");  // Send Ctrl+Space x
       return false;
   ```

3. Add to keymap in TMUX layer

### Changing Tapping Term

Add to `config.h`:
```c
#define TAPPING_TERM 175  // Lower = faster modifier activation (default: 200ms)
```

### RGB Effects

Enable/disable effects in `config.h`:
```c
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
// ... etc
```

## Troubleshooting

**See [MANUAL_BUILD_FLASH.md](MANUAL_BUILD_FLASH.md) for detailed troubleshooting.**

Common issues:

**Bootloader not detected:**
- Press and release RESET button quickly
- Try different USB port
- Check: `ls /dev/ttyACM*`

**Flash permission denied:**
```bash
# Add udev rule
sudo tee /etc/udev/rules.d/50-keyboards.rules > /dev/null <<EOF
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", MODE:="0666"
EOF
sudo udevadm control --reload-rules
```

**Keys not working after flash:**
- Verify BOTH halves are flashed
- Check TRRS cable connection
- Unplug and replug USB

**Home-row mods triggering accidentally:**
- Chordal Hold and Flow Tap are already enabled to prevent most misfires
- Adjust `FLOW_TAP_TERM` in config.h (default 150ms) to tune fast-typing protection
- Add `#define TAPPING_TERM <value>` to config.h (default is 200ms, try 225ms)

## Files

| File | Purpose |
|------|---------|
| `keymap.c` | Main keymap and macro definitions |
| `config.h` | Keyboard configuration settings |
| `rules.mk` | Build rules and feature enables |
| `MANUAL_BUILD_FLASH.md` | Complete build and flash instructions |
| `VERIFICATION_REPORT.md` | Firmware testing and verification results |
| `.gitignore` | Excludes build artifacts from git |

## Resources

- **QMK Documentation:** https://docs.qmk.fm/
- **Keebio Iris:** https://keeb.io/products/iris-keyboard-split-ergonomic-keyboard
- **QMK Discord:** https://discord.gg/qmk
- **My config repository:** This repository!

## Changelog

### 2026-02-02 - Modernize for Latest QMK
- Update from QMK Nov 2021 → Feb 2026
- Modernize tmux macro system (action_get_macro → process_record_user)
- Update RGB keycodes (RGB_* → UG_*)
- Replace deprecated config settings
- Add manual build and flash instructions
- Bug fixes:
  - Remove broken layer switching code
  - Fix EEPROM reset on boot
  - Update deprecated keycodes
- Complete verification with 224 keys tested
- Add comprehensive documentation
- Use manual process for maximum reliability and control

### 2021-11 - Initial Implementation
- Original QMK firmware setup
- Home-row modifiers
- Tmux integration
- 4-layer system

## License

GPL v2 (inherited from QMK Firmware)

## Credits

Based on QMK Firmware by the QMK Community
Keebio Iris keyboard by Keebio
