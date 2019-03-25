## Building

To build it you will need [qmk_firmware][qmk] checked out. Then check
out this repo to something like `keyboards/ergodox/keymaps/scottleeroberts`.

 [qmk]: https://github.com/jackhumbert/qmk_firmware

```
$ git clone https://github.com/jackhumbert/qmk_firmware.git
$ cd qmk_firmware
$ git clone https://github.com/scottleeroberts/iris.git \keyboards/iris/keymaps/scottleeroberts
$ sudo make iris/rev2:scottleeroberts
$ Use QMK GUI Loader to flash both sides of the board
