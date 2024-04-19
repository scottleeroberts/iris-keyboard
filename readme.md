## Building

```
$ sudo pacman -S qmk
$ git clone git@github.com/qmk/qmk_firmware
$ cd qmk_firmware
$ git checkout 1989eb17ec391d4f9e8c1c1ea3fc746f96d43942
$ make git-subodule
$ git clone https://github.com/scottleeroberts/iris-keyboard.git \keyboards/keebio/iris/keymaps/scottleeroberts
$ ./util/docker_build.sh keebio/iris/rev5:scottleeroberts

Copy resulting `keebio_iris_rev5_scottleeroberts.hex` to mac, and load firmware with "QMK Toolbox"
NOTE: Each side must be loaded with new firmware by plugging each side in independently.  Reset is on the bottom of the keyboard.  Choose atmega32u4 and "auto flash".

```
