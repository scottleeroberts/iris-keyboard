## Building

Dependencies for linux: avrdude, avr-gcc, avr-libc

Note: avrdude is needed for iris as the caterina boot loader

 [qmk]: https://github.com/jackhumbert/qmk_firmware

```
$ git clone https://github.com/jackhumbert/qmk_firmware.git
$ cd qmk_firmware
$ git clone https://github.com/scottleeroberts/iris.git \keyboards/iris/keymaps/scottleeroberts
$ sudo make iris/rev2:scottleeroberts:avrdude
