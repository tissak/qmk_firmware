/* This is the Atreus62 keyboard layout by Xyverz aka u/Zrevyx on r/mk
   I've blatantly stolen what works for me from the Planck and Preonic
   layouts and modified this file to fit me. Initial credet goes to
   u/profet23 for the doing all the work and adding this keyboard to
   QMK in the first place.

   I've got Dvorak, Qwerty, and Colemak layouts at this time, with the
   possibility of adding more in the future.

   The bottom row is fairly Kinesis-ish since the Contour and Advantage
   keyboards have been my daily drivers for the last 17 years. I hope
   You can get some enjoyment out of this layout should you chose it!

CHANGELOG:

 0.1 - Initial commit. Based off of Profet's default keymap.
 0.2 - Converted to a more Planck/Preonic keymap style file with
       persistent layers enabled. Renamed layers to reflect OLKB maps.
       Added a TODO list.

TODO:

 * Make the layout more efficient, even if it means changing the RAISE
   and LOWER functionality.
 * Add legends in comments for each layer. Maybe.
 * Add a gaming layer.

*/

// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
#include "atreus62.h"
#include "action_layer.h"
#include "eeconfig.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _WOW 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 16

enum atreus52_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = { /* qwerty */
        { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS },
        { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
        { KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
        { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ENT,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT  },
        { ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_BSPC, KC_LGUI,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT }
    },

    [_LOWER] = {
        { KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12  },
        { KC_TILD, KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
        { _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,},
        { _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______ },
        { _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, KC_INS,  _______, _______, KC_PGUP, KC_PGDN, _______ }
    },
    [_RAISE] = {
        { KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12  },
        { KC_TILD, KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
        { _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS },
        { _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______ },
        { _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, KC_INS,  _______, _______, KC_VOLU, KC_VOLD, _______ }
    },
    [_ADJUST] = {
        { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
        { _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
        { _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,  _______, _______, _______, _______},
        { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
        { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
    },

};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case ADJUST:
          if (record->event.pressed) {
            layer_on(_ADJUST);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_ADJUST);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};
