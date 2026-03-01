# Scott's Iris Keyboard Layout (Legacy)

Custom QMK firmware for Keebio Iris Rev5 (QMK Nov 2021).

## Building

### Prerequisites

- Docker
- dfu-programmer (`sudo apt install dfu-programmer` on Ubuntu/Debian)

### Build

```bash
cd ~/scottleeroberts/iris-keyboard

# Create build directory
mkdir -p build && cd build

# Clone QMK firmware pinned to tested version
QMK_SHA=1989eb17ec391d4f9e8c1c1ea3fc746f96d43942
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
git checkout $QMK_SHA
git submodule update --init --recursive

# Copy keymap files
mkdir -p keyboards/keebio/iris/keymaps/scottleeroberts
cp ../../keymap.c keyboards/keebio/iris/keymaps/scottleeroberts/
cp ../../common_keyboard.h keyboards/keebio/iris/keymaps/scottleeroberts/
cp ../../config.h keyboards/keebio/iris/keymaps/scottleeroberts/
cp ../../rules.mk keyboards/keebio/iris/keymaps/scottleeroberts/

# Workaround: symlink relocated driver file
mkdir -p drivers/led
ln -sf ../../platforms/avr/drivers/ws2812.c drivers/led/ws2812.c

# Build with Docker (must use qmkfm/qmk_firmware image for Python 3.7 compatibility)
docker run --rm \
  -v $(pwd):/qmk_firmware \
  -w /qmk_firmware \
  qmkfm/qmk_firmware \
  bash -c "pip3 install -r requirements.txt >/dev/null 2>&1 && make keebio/iris/rev5:scottleeroberts"

# Copy hex to repo root
cp keebio_iris_rev5_scottleeroberts.hex ../..
cd ../..
```

### Flash (repeat for each half)

```bash
# 1. Plug in one half via USB
# 2. Press the RESET button on the PCB
# 3. Run:
sudo dfu-programmer atmega32u4 erase --force
sudo dfu-programmer atmega32u4 flash --force keebio_iris_rev5_scottleeroberts.hex
sudo dfu-programmer atmega32u4 reset
```

Each half must be flashed independently. Flash left, unplug, then flash right.

## Files

| File | Purpose |
|------|---------|
| `keymap.c` | Main keymap layout |
| `common_keyboard.h` | Layer enum, macros, tmux helpers |
| `config.h` | Keyboard configuration |
| `rules.mk` | Build rules and feature enables |
