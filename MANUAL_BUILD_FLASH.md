# Manual Build & Flash Instructions for Linux

**No scripts, full control, no surprises.**

Compatible with Ubuntu, Debian, Arch, Manjaro, and other Linux distributions.

## Overview

This guide uses:
- **Docker** - to build the firmware (uses QMK's official pre-built image, no Dockerfile needed)
- **dfu-programmer** - to flash the firmware to your keyboard

You don't need to install Python, QMK CLI, or the full AVR toolchain. Docker handles the build environment, and dfu-programmer is a single package install.

---

## Prerequisites

### Ubuntu / Debian

```bash
# Install Docker (if not already installed)
sudo apt update
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker

# Add yourself to docker group (to run without sudo)
sudo usermod -aG docker $USER
# Log out and back in for group to take effect

# Install flashing tool
sudo apt install dfu-programmer
```

### Arch / Manjaro

```bash
# Install Docker (if not already installed)
sudo pacman -S docker
sudo systemctl start docker
sudo systemctl enable docker

# Add yourself to docker group (to run without sudo)
sudo usermod -aG docker $USER
# Log out and back in for group to take effect

# Install flashing tool
sudo pacman -S dfu-programmer
```

---

## Part 1: Build Firmware

### Step 1: Check you're in the right directory

```bash
cd ~/scottleeroberts/iris-keyboard
ls -la keymap.c config.h rules.mk
# All three files should exist
```

### Step 2: Create build directory

```bash
mkdir -p build
cd build
```

### Step 3: Clone QMK firmware (first time only)

```bash
# If you haven't cloned QMK yet:
git clone --depth 1 https://github.com/qmk/qmk_firmware.git

# If you already have it, optionally update:
cd qmk_firmware
git pull
cd ..
```

**This takes 2-5 minutes depending on your internet.**

### Step 4: Initialize submodules (first time only)

```bash
cd qmk_firmware
git submodule update --init --recursive

# This takes 5-10 minutes and downloads ~2GB
# You'll see progress messages
```

### Step 5: Copy your keymap files

```bash
# Create keymap directory
mkdir -p keyboards/keebio/iris/keymaps/scottleeroberts

# Copy your files
cp ../../keymap.c keyboards/keebio/iris/keymaps/scottleeroberts/
cp ../../config.h keyboards/keebio/iris/keymaps/scottleeroberts/
cp ../../rules.mk keyboards/keebio/iris/keymaps/scottleeroberts/
cp ../../readme.md keyboards/keebio/iris/keymaps/scottleeroberts/

# Verify they're there
ls -la keyboards/keebio/iris/keymaps/scottleeroberts/
```

### Step 6: Build with Docker

```bash
# Make sure you're in build/qmk_firmware directory
pwd
# Should show: .../iris-keyboard/build/qmk_firmware

# Run the build
docker run --rm \
  -v $(pwd):/qmk_firmware \
  -w /qmk_firmware \
  ghcr.io/qmk/qmk_cli \
  make keebio/iris/rev5:scottleeroberts
```

**This takes 2-3 minutes.** You'll see compilation messages scrolling by.

Success looks like:
```
Linking: .build/keebio_iris_rev5_scottleeroberts.elf
Creating load file for flashing: .build/keebio_iris_rev5_scottleeroberts.hex
Size: 24924/28672 (86%)
```

### Step 7: Copy firmware out

```bash
# Copy the .hex file to parent directory
cp keebio_iris_rev5_scottleeroberts.hex ../..

# Go back to main directory
cd ../..

# Verify it's there
ls -lh keebio_iris_rev5_scottleeroberts.hex
# Should be ~69KB
```

**Build complete!** You now have: `keebio_iris_rev5_scottleeroberts.hex`

---

## Part 2: Flash Firmware (LEFT half)

### Step 1: Connect LEFT keyboard half

1. Unplug both halves if connected
2. Connect ONLY the LEFT half via USB
3. Wait 2 seconds

### Step 2: Put keyboard in bootloader mode

1. Flip the keyboard over
2. Find the small RESET button on the PCB
3. Press it ONCE (you'll hear USB disconnect/reconnect sound)

**You have ~8 seconds before bootloader times out.**

### Step 3: Check bootloader is detected

```bash
# Check for DFU device
lsusb | grep -i "atmel\|dfu"

# Should see something like: "Atmel Corp. atmega32u4 DFU bootloader"
# If not, press RESET again
```

### Step 4: Flash LEFT half

**Run these three commands immediately after entering bootloader mode:**

```bash
# Erase the chip
sudo dfu-programmer atmega32u4 erase --force

# Flash the firmware
sudo dfu-programmer atmega32u4 flash keebio_iris_rev5_scottleeroberts.hex

# Reset to exit bootloader and run the firmware
sudo dfu-programmer atmega32u4 reset
```

**This takes 5-10 seconds.** Success looks like:

```
Erasing flash...  Success
Checking memory from 0x0 to 0x6FFF...  Empty.
Validating...  Success
0x6144 bytes written into 0x7000 bytes memory (85.34%).
```

### Step 5: Test LEFT half

1. Keyboard should automatically reconnect after reset
2. Type some keys - they should work
3. If not working, unplug and replug USB

---

## Part 3: Flash Firmware (RIGHT half)

**Repeat the exact same process for the RIGHT half:**

### Step 1: Connect RIGHT keyboard half

1. Unplug LEFT half
2. Connect ONLY the RIGHT half via USB
3. Wait 2 seconds

### Step 2: Put keyboard in bootloader mode

1. Flip the keyboard over
2. Press the RESET button

### Step 3: Check bootloader is detected

```bash
lsusb | grep -i "atmel\|dfu"
```

### Step 4: Flash RIGHT half

```bash
# Erase the chip
sudo dfu-programmer atmega32u4 erase --force

# Flash the firmware
sudo dfu-programmer atmega32u4 flash keebio_iris_rev5_scottleeroberts.hex

# Reset to exit bootloader
sudo dfu-programmer atmega32u4 reset
```

### Step 5: Test RIGHT half

1. Keyboard should automatically reconnect
2. Connect both halves with TRRS cable
3. Connect LEFT half to computer
4. Test all keys work

---

## Done!

Both halves are now flashed. Your keyboard is ready to use.

---

## Troubleshooting

### "Permission denied" when running dfu-programmer

**Option 1: Use sudo (shown above)**

This is the simplest approach and what we use in the instructions.

**Option 2: Add udev rule (permanent fix, no sudo needed)**

```bash
# Create udev rule for Atmel DFU bootloader
sudo tee /etc/udev/rules.d/50-keyboards.rules > /dev/null <<EOF
# Atmel DFU Bootloader (ATmega32U4)
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
EOF

# Reload rules
sudo udevadm control --reload-rules
sudo udevadm trigger

# Now unplug and replug keyboard, then enter bootloader mode
# You can run dfu-programmer without sudo after this
```

### "No device present" error

**Cause:** Keyboard is not in bootloader mode or bootloader timed out.

**Solution:**
1. Press RESET button on keyboard
2. Immediately run the dfu-programmer commands within 8 seconds
3. If you see "Atmel Corp. atmega32u4 DFU bootloader" in `lsusb`, the device is ready

**Check if bootloader is active:**
```bash
lsusb | grep -i atmel
# Should show: "Atmel Corp. atmega32u4 DFU bootloader"
```

### No DFU device appears in lsusb

**Check USB connection:**
```bash
lsusb
# Look for "Atmel" in the device list
```

**If not found:**
- Try different USB port (some ports have power issues)
- Press and hold RESET for 1 second, then release
- Check USB cable is fully connected
- Try a different USB cable

### "Could not open USB device" error

The device was found but cannot be accessed.

**Solution:** Add the udev rule (see "Permission denied" section above) or use sudo.

### Bootloader timeout / keyboard doesn't enter bootloader

**Symptoms:** Pressing RESET does nothing, or device doesn't show in lsusb

**Solutions:**
1. Ensure USB cable is data-capable (not charge-only)
2. Try pressing RESET button twice quickly
3. Hold RESET for 1-2 seconds then release
4. Unplug USB, wait 5 seconds, plug back in, then press RESET

### Docker permission denied

```bash
# Add yourself to docker group
sudo usermod -aG docker $USER

# Log out and back in
```

Or run Docker with sudo:
```bash
sudo docker run --rm \
  -v $(pwd):/qmk_firmware \
  -w /qmk_firmware \
  ghcr.io/qmk/qmk_cli \
  make keebio/iris/rev5:scottleeroberts
```

### Build fails with "submodule not found"

```bash
cd build/qmk_firmware
git submodule update --init --recursive --force
cd ../..
```

### Keys don't work after flashing

1. Make sure BOTH halves are flashed
2. Check TRRS cable is connected
3. Try unplugging and replugging
4. Try reflashing

---

## Quick Reference Card

**Build:**
```bash
cd ~/scottleeroberts/iris-keyboard
mkdir -p build && cd build
git clone --depth 1 https://github.com/qmk/qmk_firmware.git  # first time
cd qmk_firmware
git submodule update --init --recursive  # first time
mkdir -p keyboards/keebio/iris/keymaps/scottleeroberts
cp ../../{keymap.c,config.h,rules.mk,readme.md} keyboards/keebio/iris/keymaps/scottleeroberts/
docker run --rm -v $(pwd):/qmk_firmware -w /qmk_firmware ghcr.io/qmk/qmk_cli make keebio/iris/rev5:scottleeroberts
cp keebio_iris_rev5_scottleeroberts.hex ../..
cd ../..
```

**Flash (repeat for each half):**
```bash
# Press RESET button
lsusb | grep -i atmel  # Check DFU bootloader is active
sudo dfu-programmer atmega32u4 erase --force
sudo dfu-programmer atmega32u4 flash keebio_iris_rev5_scottleeroberts.hex
sudo dfu-programmer atmega32u4 reset
```

---

## Notes

- **Each build is clean** - no cached state to corrupt
- **You see every command** - no hidden operations
- **Easy to debug** - if something fails, you know exactly where
- **No scripts to trust** - you control everything

The manual process is actually simpler and more reliable than scripts for one-off builds.
