## Building

```
$ sudo pacman -S qmk
$ git clone git@github.com/qmk/qmk_firmware
$ make git-subodule
$ cd qmk_firmware
$ git clone https://github.com/scottleeroberts/iris-keyboard.git \keyboards/keebio/iris/keymaps/scottleeroberts
$ qmk compile -kb keebio/iris/rev5 -km scottleeroberts

Copy resulting `keebio_iris_rev5_scottleeroberts.hex` to mac, and load firmware with "QMK Toolbox client"
NOTE: Each side must be loaded with new firmware.  Reset is on the bottom of the keyboard

```
