#include QMK_KEYBOARD_H
#include "common_keyboard.h"
extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE,KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTRL,MY_A,    MY_S,    MY_D,    MY_F,    KC_G,                               KC_H,    MY_J,    KC_K,    MY_L,    MY_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     _______,         _______  ,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,KC_EQUAL,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴   ┬────┘        └───┬   ─┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT,MO(NUMBERS),KC_ENT,                  KC_SPC,  MO(SYMB),KC_TAB
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TILD, KC_EXLM , KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LBRC, KC_RBRC,LSFT(KC_LBRC),LSFT(KC_RBRC),_______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______, _______,_______, KC_LEFT_PAREN,KC_RIGHT_PAREN,_______, _______,   _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴   ┬────┘        └───┬    ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [TMUX] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                           _______, _______,M_TMUX_COPY_MODE,M_TMUX_SP,M_TMUX_VS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, M_TMUX_1, M_TMUX_2, M_TMUX_3, M_TMUX_4, M_TMUX_5,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, M_TMUX_NEW, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴   ┬────┘        └───┬    ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [NUMBERS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET  , _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_7   , KC_8   , KC_9   , _______, KC__MUTE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_4   , KC_5   , KC_6   , _______, KC__VOLUP,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_1   , KC_2   , KC_3   , _______, KC__VOLDOWN,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴   ┬────┘        └───┬    ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, KC_0,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(BASE);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
        layer_on(SYMB);
        update_tri_layer(SYMB, TMUX, NUMBERS);
      } else {
        layer_off(SYMB);
        update_tri_layer(SYMB, TMUX, NUMBERS);
      }
      return false;
      break;
    case TMUX:
      if (record->event.pressed) {
        layer_on(TMUX);
        update_tri_layer(SYMB, TMUX, NUMBERS);
      } else {
        layer_off(TMUX);
        update_tri_layer(SYMB, TMUX, NUMBERS);
      }
      return false;
      break;
    case NUMBERS:
      if (record->event.pressed) {
        layer_on(NUMBERS);
      } else {
        layer_off(NUMBERS);
      }
      return false;
      break;
  }
  return true;
}
