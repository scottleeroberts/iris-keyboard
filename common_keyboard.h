enum {
 BASE,
 SYMB,
 TMUX,
 NUMBERS
};

#define _______ KC_TRNS

#define MY_G LSFT_T(KC_G)
#define MY_S LGUI_T(KC_S)
#define MY_D LT(TMUX,KC_D)
#define MY_F CTL_T(KC_F)
#define MY_V RCTL(KC_V)
#define MY_J CTL_T(KC_J)
#define MY_L LGUI_T(KC_L)
#define MY_H LSFT_T(KC_H)

#define M_TMUX M(0)
#define M_TMUX_1 M(1)
#define M_TMUX_2 M(2)
#define M_TMUX_3 M(3)
#define M_TMUX_4 M(4)
#define M_TMUX_5 M(5)
#define M_TMUX_COPY_MODE M(6)
#define M_TMUX_SP M(7)
#define M_TMUX_VS M(8)
#define M_TMUX_NEW M(9)

void do_tmux_key(keyrecord_t *record, uint8_t code, uint8_t modifier) {
  if (record->event.pressed) {
    register_code(KC_LCTRL);
    register_code(KC_B);
    unregister_code(KC_B);
    unregister_code(KC_LCTRL);
    register_code(modifier);
    register_code(code);
    unregister_code(code);
    unregister_code(modifier);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTRL);
      }
      break;
    case 1: do_tmux_key(record, KC_1, KC_NO); break;
    case 2: do_tmux_key(record, KC_2, KC_NO); break;
    case 3: do_tmux_key(record, KC_3, KC_NO); break;
    case 4: do_tmux_key(record, KC_4, KC_NO); break;
    case 5: do_tmux_key(record, KC_5, KC_NO); break;
    case 6: do_tmux_key(record, KC_LBRC, KC_NO); break;
    case 7: do_tmux_key(record, KC_QUOT, KC_LSFT); break;
    case 8: do_tmux_key(record, KC_5, KC_LSFT); break;
    case 9: do_tmux_key(record, KC_C, KC_NO); break;
  }
  return MACRO_NONE;
};
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  eeconfig_init();
};
