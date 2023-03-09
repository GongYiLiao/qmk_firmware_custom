/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


enum custom_keycodes {
    EMACS_OPEN = SAFE_RANGE, 
    EMACS_SAVE,
    EMACS_KILL,
    EMACS_LSTB,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case EMACS_OPEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("xf"));
      } 
      break;
    case EMACS_SAVE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("xs"));
      } 
      break;
    case EMACS_KILL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("x")"k"SS_TAP(X_ENT));
      } 
      break;
    case EMACS_LSTB:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("xb"));
      }
      break;
  }
  return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: Dvorak
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|   |   |
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|   BSP | |MEH|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|   |
     * |MO(2) |  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|  Return|               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |OSM(SFT) |  ;| Q|  J|  K|  X|  B|  M|  W|  V|  Z|  OSM(Sft)|     | ↑ |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|   |
     * |LCTL|Gui|LAlt|     Space     |LAlt|MO(2)|LCA_T(KC_APP)|RCtl| | ← | ↓ | → | |      0|  .|Ent|
     * `-----------------------------------------------------------' `-----------' `---------------'
    */
    [0] = LAYOUT_fullsize_ansi(
        MEH_T(KC_ESC),  LCAG_T(KC_F1), ALL_T(KC_F2), C_S_T(KC_F3), SGUI_T(KC_F4), KC_F5, KC_F6,  KC_F7, KC_F8, SGUI_T(KC_F9), C_S_T(KC_F10), ALL_T(KC_F11), LCAG_T(KC_F12), KC_PSCR, KC_NO,        KC_NO,
        LT(3, KC_GRV),  KC_1,          KC_2,         KC_3,         KC_4,          KC_5,  KC_6,   KC_7,  KC_8,  KC_9,          KC_0,          KC_LBRC,       LT(3, KC_RBRC), KC_BSPC, OSM(MOD_MEH), KC_HOME, KC_PGUP, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        LCA_T(KC_TAB),  KC_QUOT,       KC_COMM,      KC_DOT,       KC_P,          KC_Y,  KC_F,   KC_G,  KC_C,  KC_R,          KC_L,          KC_SLSH,       KC_EQL,         KC_BSLS, KC_DEL,       KC_END,  KC_PGDN, KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        MO(2),          KC_A,          KC_O,         KC_E,         KC_U,          KC_I,  KC_D,   KC_H,  KC_T,  KC_N,          KC_S,          KC_MINS,       KC_ENT,                                                  KC_P4,   KC_P5,  KC_P6,
        OSM(MOD_RSFT),  KC_SCLN,       KC_Q,         KC_J,         KC_K,          KC_X,  KC_B,   KC_M,  KC_W,  KC_V,          KC_Z,          OSM(MOD_RSFT),                                        KC_UP,            KC_P1,   KC_P2,  KC_P3,   KC_PENT,
        KC_LCTL,        KC_LGUI,       KC_LALT,                                          KC_SPC,                              KC_LALT,       MO(2),         LCA_T(KC_APP),  KC_RCTL, KC_LEFT,      KC_DOWN, KC_RGHT, KC_P0,           KC_PDOT
    ),
    /* 1: qwerty
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|   |   |
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   BSP | |   |Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|   |
     * |MO(2) |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |OSM(SFT) |  Z|  X| C|  V|  B|  N|  M|  ,|  .|  /|  OSM(Sft)|     | ↑ |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|   |
     * |LCTL|Gui|LAlt|     Space     |LAlt|MO(2)|LCA_T(KC_APP)|RCtl| | ← | ↓ | → | |      0|  .|Ent|
     * `-----------------------------------------------------------' `-----------' `---------------'
    */    
    [1] = LAYOUT_fullsize_ansi(
        MEH_T(KC_ESC), LCAG_T(KC_F1), ALL_T(KC_F2), C_S_T(KC_F3), SGUI_T(KC_F4), KC_F5, KC_F6,  KC_F7,  KC_F8,   SGUI_T(KC_F9), C_S_T(KC_F10), ALL_T(KC_F11), LCAG_T(KC_F12), KC_PSCR, KC_TRNS,      KC_NO,
        KC_GRV,        KC_1,          KC_2,         KC_3,         KC_4,          KC_5,  KC_6,   KC_7,   KC_8,    KC_9,          KC_0,          KC_MINS,       KC_EQL,         KC_BSPC, OSM(MOD_MEH), KC_HOME, KC_PGUP, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        LCA_T(KC_TAB), KC_Q,          KC_W,         KC_E,         KC_R,          KC_T,  KC_Y,   KC_U,   KC_I,    KC_O,          KC_P,          KC_LBRC,       LT(3, KC_RBRC),   KC_BSLS, KC_DEL,       KC_END,  KC_PGDN, KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        MO(2),         KC_A,          KC_S,         KC_D,         KC_F,          KC_G,  KC_H,   KC_J,   KC_K,    KC_L,          KC_SCLN,       KC_QUOT,       KC_ENT,                                                  KC_P4,  KC_P5,   KC_P6,
        OSM(MOD_LSFT), KC_Z,          KC_X,         KC_C,         KC_V,          KC_B,  KC_N,   KC_M,   KC_COMM, KC_DOT,        KC_SLSH,       OSM(MOD_RSFT),                                        KC_UP,            KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL,       KC_LGUI,       KC_LALT,                                          KC_SPC,                                 KC_RALT,       MO(2),         LCA_T(KC_APP),  KC_RCTL, KC_LEFT,      KC_DOWN, KC_RGHT, KC_P0,           KC_PDOT
    ),
    /* 2: utility
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |   |   |   |   |   |   | |   |   |   |   | |   |   |   |  |  |DF0|DF1|   |
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       | |   |   |   | |   |   |   |   |
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |     |   |   |   |   |   |PgU|  U|  ↑|  O|  P|  [|  ]|     | |   |   |   | |   |   |   |   |
     * |-----------------------------------------------------------| `-----------' |-----------|   |
     * |      |   |   |   |   |   |Hom|  ←|  ↓|  →|End|   |        |               |   |   |   |   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |         | Und|Cut|Cpy|Pst|  |PgD|W←|Fnd|W→|WR|            |     |   |     |   |   |   |   |
     * |-----------------------------------------------------------| ,-----------. |-----------|   |
     * |    |   |    |               |    |     |       |          | |   |   |   | |       |   |   |
     * `-----------------------------------------------------------' `-----------' `---------------'
    */        
    [2] = LAYOUT_fullsize_ansi(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  DF(0), DF(1), KC_NO,
        KC_NO,   KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_PWR, KC_SLEP, KC_NO, KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_PGUP, KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,   KC_NO, KC_NO,
        KC_TRNS, KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_NO,   KC_NO,                              KC_NO,  KC_NO,   KC_NO,
        KC_NO,   KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_SLCT, KC_PGDN, KC_WBAK, KC_FIND, KC_WFWD, KC_WREF, KC_NO,                         KC_NO,        KC_NO,  KC_NO,   KC_NO, KC_NO,
        KC_NO,   KC_NO,   KC_NO,                             KC_NO,                              KC_NO,   KC_TRNS, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO
    ),
    /* 3: emacs
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |   |   |   |   |   |   | |   |   |   |   | |   |   |   |  |  |   |  |   |
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       | |   |   |   | |   |   |   |   |
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |     |   |   |   |   |   |  F|   |   |   |   |   |   |     | |   |   |   | |   |   |   |   |
     * |-----------------------------------------------------------| `-----------' |-----------|   |
     * |      |   |   |   |   |   |   |   |   |   |  s|   |        |               |   |   |   |   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |         |   |   |  |  k|   |  b|   |   |   |   |          |     |   |     |   |   |   |   |
     * |-----------------------------------------------------------| ,-----------. |-----------|   |
     * |    |   |    |               |    |     |       |          | |   |   |   | |       |   |   |
     * `-----------------------------------------------------------' `-----------' `---------------'
    */        
    [3] = LAYOUT_fullsize_ansi(
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, EMACS_OPEN, KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, EMACS_SAVE, KC_NO, KC_NO,                             KC_NO,  KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, EMACS_KILL, KC_NO, EMACS_LSTB, KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO,                      KC_NO,        KC_NO,  KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO,                           KC_NO,                           KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO
                               ),
    
    [4] = LAYOUT_fullsize_ansi(
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                             KC_NO,  KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                      KC_NO,        KC_NO,  KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO,                      KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO
                               )
    
};
