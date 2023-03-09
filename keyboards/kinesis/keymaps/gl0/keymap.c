#include QMK_KEYBOARD_H


#define DVORAK0      0
#define QWERTY0      1
#define NAVIUTIL0    2
#define NAVIUTIL1    3
#define EMACS0       4
#define EMACS1       5
#define MEDIAWM0     6
#define NUMPAD0      7


enum custom_keycodes {
  ST_MACRO_0 = SAFE_RANGE,    // SM0;  Emacs new line (C-q C-j)
  ST_MACRO_1,                 // SM1:  Emacs kill current buffer (C-x k enter)
  ST_MACRO_2,                 // SM2:  Emacs open file (C-x C-f)
  ST_MACRO_3,                 // SM3:  Emacs run code block in Python/R (C-c C-c) 
  ST_MACRO_4,                 // SM4:  Emacs save file (C-x C-f)
  ST_MACRO_5,                 // SM5:  Emacs list buffers  (C-x C-b)
  ST_MACRO_6,                 // SM6:  Emacs write file (C-x C-w)
  ST_MACRO_7,                 // SM7:  emacs org-mode show-all-tab
  ST_MACRO_8,                 // SM8:  emacs org-mode next-heading
  ST_MACRO_9,                 // SM9:  emacs org-mode previous heading
  ST_MACRO_10,                // SM10: emacs org-mode next heading some level
  ST_MACRO_11,                // SM11: emacs org-mode previous heading same level
  ST_MACRO_12,                // SM12: emacs org-mode back to higher level heading 
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_Q)) SS_DELAY(20) SS_LCTL(SS_TAP(X_J)));
      }
      break;
    case ST_MACRO_1:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_X)) SS_DELAY(20) SS_TAP(X_K)  SS_DELAY(20) SS_TAP(X_ENTER));
      }
      break;
    case ST_MACRO_2:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_X)) SS_DELAY(20) SS_LCTL(SS_TAP(X_F)));
      }
      break;
    case ST_MACRO_3:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(20) SS_LCTL(SS_TAP(X_C)));
      }
      break;
    case ST_MACRO_4:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_X)) SS_DELAY(20) SS_LCTL(SS_TAP(X_S)));
      }
      break;
    case ST_MACRO_5:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_X)) SS_DELAY(20) SS_LCTL(SS_TAP(X_B)));
      }
      break;
    case ST_MACRO_6:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_X)) SS_DELAY(20) SS_LCTL(SS_TAP(X_W)));
      }
      break;
    case ST_MACRO_7:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_U)) SS_DELAY(20) SS_LCTL(SS_TAP(X_U)) SS_DELAY(20) SS_LCTL(SS_TAP(X_U) SS_DELAY(20) SS_TAP(X_TAB)));
      }
      break;
    case ST_MACRO_8:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(20) SS_LCTL(SS_TAP(X_P)));
      }
      break;
    case ST_MACRO_9:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(20) SS_LCTL(SS_TAP(X_N)));
      }
      break;
    case ST_MACRO_10:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(20) SS_LCTL(SS_TAP(X_B)));
      }
      break;
    case ST_MACRO_11:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(20) SS_LCTL(SS_TAP(X_F)));
      }
      break;
    case ST_MACRO_12:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(20) SS_LCTL(SS_TAP(X_U)));
      }
      break;
  }
  return true;
}

typedef struct {
  bool is_press_action;
  uint8_t step;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,   
  DOUBLE_HOLD,        // Actually tap then hold  
  DOUBLE_SINGLE_TAP,
  MORE_TAPS
};


uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

static tap dance_state[36];

enum tap_dance_codes {
  DANCE_0,       // TD0:  tap/hold: L-Ctrl; tap-then-hold: LO(NUMPAD0) 
  DANCE_1,       // TD1:  tap/hold: R-Ctrl; tap-then-hold: LO(NAVIUTIL0) 
  DANCE_2,       // TD2:  tap/hold: L-Alt; tap-then-hold: LO(MEDIAWM0) 
  DANCE_3,       // TD3:  tap/hold: R-Alt; tap-then-hold: LO(EMACS0) 
  DANCE_4,       // TD4:  tap: Home; hold: LO(NAVIUTIL0); double-tap: LCTL(HOME), tap-then-hold: LO(MEDIAWM0) 
  DANCE_5,       // TD5:  tap: PgUp; hold: LO(NAVIUTIL0); double-tap: LCTL(PgUP); tap-then-hold: LO(MEDIAWM0) 
  DANCE_6,       // TD6:  tap: End; hold: LO(EMACS0); double-tap: RCTL(END); tap-then-hold: LO(EMACS1) 
  DANCE_7,       // TD7:  tap: PgDn; hold: LO(EMACS0); double-tap: RCTL(PGDN); tap-then-hol: LO(EMACS1) 
  DANCE_8,       // TD8:  tap: Left; double-tap: L-Ctrl(Left); hold: Home; tap-then-hold: L-Ctrl(Home)    only use when physical navi keys are not available 
  DANCE_9,       // TD9:  tap: Right; double-tap: L-Ctrl(Right); hold: End; tap-then-hold: L-Ctrl(End)    only use when physical navi keys are not available     
  DANCE_10,      // TD10: tap: Up; double-tap: L-Ctrl(Up); hold: PgUp; tap-then-hold: R-Ctrl(PgUp)    only use when physical navi keys are not available 
  DANCE_11,      // TD11: tap: Down; double-tap: L-Ctrl(Down); hold: PgDn; tap-then-hold: R-Ctrl(PgDn)    only use when physical navi keys are not available 
  DANCE_12,      // TD12: tap: F1, hold: L-Alt(F1)
  DANCE_13,      // TD13: tap: F2, hold: L-Alt(F2)
  DANCE_14,      // TD14: tap: F3, hold: L-Alt(F3)
  DANCE_15,      // TD15: tap: F4, hold: L-Alt(F4)
  DANCE_16,      // TD16: tap: F5, hold: L-Alt(F5)
  DANCE_17,      // TD17: tap: F6, hold: L-Alt(F6)
  DANCE_18,      // TD18: tap: F7, hold: L-Alt(F7)
  DANCE_19,      // TD19: tap: F8, hold: L-Alt(F8)
  DANCE_20,      // TD20: tap: F9, hold: L-Alt(F9)
  DANCE_21,      // TD21: tap: F10, hold: L-Alt(F10)
  DANCE_22,      // TD22: tap: F11, hold: L-Alt(F11)
  DANCE_23,      // TD23: tap: F12, hold: L-Alt(F12)
  DANCE_24,      // TD24: tap: L-Ctrl(F1), hold: L-Alt(F1)
  DANCE_25,      // TD25: tap: L-Ctrl(F2), hold: L-Ctrl-Alt(F2)
  DANCE_26,      // TD26: tap: L-Ctrl(F3), hold: L-Ctrl-Alt(F3)
  DANCE_27,      // TD27: tap: L-Ctrl(F4), hold: L-Ctrl-Alt(F4)
  DANCE_28,      // TD28: tap: L-Ctrl(F5), hold: L-Ctrl-Alt(F5)
  DANCE_29,      // TD29: tap: L-Ctrl(F6), hold: L-Ctrl-Alt(F6)
  DANCE_30,      // TD30: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F7)
  DANCE_31,      // TD31: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F8)
  DANCE_32,      // TD32: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F9)
  DANCE_33,      // TD33: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F10)
  DANCE_34,      // TD34: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F11)
  DANCE_35,      // TD35: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F12)
};                                                                                                     


void dance_0_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[0].step = dance_step(state);
  switch (dance_state[0].step) {
    case SINGLE_TAP: register_code16(KC_LCTL); break;
    case SINGLE_HOLD: register_code16(KC_LCTL); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_on(NUMPAD0); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_LCTL); register_code16(KC_LCTL);
    case MORE_TAPS: break;
  }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[0].step) {
    case SINGLE_TAP: unregister_code16(KC_LCTL); break;
    case SINGLE_HOLD: unregister_code16(KC_LCTL); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(NUMPAD0); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_LCTL); break;
  }
  dance_state[0].step = 0;
}


void dance_1_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[1].step = dance_step(state);
  switch (dance_state[1].step) {
    case SINGLE_TAP: register_code16(KC_RCTL); break;
    case SINGLE_HOLD: register_code16(KC_RCTL); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_on(NAVIUTIL0); break; 
    case DOUBLE_SINGLE_TAP: tap_code16(KC_RCTL); register_code16(KC_RCTL);
    case MORE_TAPS: break;
  }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[1].step) {
    case SINGLE_TAP: unregister_code16(KC_RCTL); break;
    case SINGLE_HOLD: unregister_code16(KC_RCTL); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(NAVIUTIL0); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_RCTL); break;
    case MORE_TAPS: break;
  }
  dance_state[1].step = 0;
}


void dance_2_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[2].step = dance_step(state);
  switch (dance_state[2].step) {
    case SINGLE_TAP: register_code16(KC_LALT); break;
    case SINGLE_HOLD: register_code16(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_on(MEDIAWM0); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_LALT); register_code16(KC_LALT);
    case MORE_TAPS: break;
  }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[2].step) {
    case SINGLE_TAP: unregister_code16(KC_LALT); break;
    case SINGLE_HOLD: unregister_code16(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(MEDIAWM0); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_LALT); break;
    case MORE_TAPS: break;
  }
  dance_state[2].step = 0;
}


void dance_3_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[3].step = dance_step(state);
  switch (dance_state[3].step) {
    case SINGLE_TAP: register_code16(KC_RALT); break;
    case SINGLE_HOLD: register_code16(KC_RALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_on(EMACS0); break; 
    case DOUBLE_SINGLE_TAP: tap_code16(KC_RALT); register_code16(KC_RALT);
    case MORE_TAPS: break;
  }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[3].step) {
    case SINGLE_TAP: unregister_code16(KC_RALT); break;
    case SINGLE_HOLD: unregister_code16(KC_RALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(EMACS0); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_RALT); break;
    case MORE_TAPS: break;
  }
  dance_state[3].step = 0;
}


void dance_4_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[4].step = dance_step(state);
  switch (dance_state[4].step) {
    case SINGLE_TAP: register_code16(KC_HOME); break;
    case SINGLE_HOLD: layer_on(NAVIUTIL0); break;
    case DOUBLE_TAP: register_code16(LCTL(KC_HOME)); break;
    case DOUBLE_HOLD: layer_on(MEDIAWM0); break;      
    case DOUBLE_SINGLE_TAP: tap_code16(KC_HOME); register_code16(KC_HOME);
    case MORE_TAPS: break;
  }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[4].step) {
    case SINGLE_TAP: unregister_code16(KC_HOME); break;
      // case SINGLE_HOLD: unregister_code16(KC_HOME); break;
    case SINGLE_HOLD: layer_off(NAVIUTIL0); break;
    case DOUBLE_TAP: unregister_code16(LCTL(KC_HOME)); break;
    case DOUBLE_HOLD: layer_off(MEDIAWM0); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_HOME); break;
    case MORE_TAPS: break;
  }
  dance_state[4].step = 0;
}


void dance_5_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[5].step = dance_step(state);
  switch (dance_state[5].step) {
    case SINGLE_TAP: register_code16(KC_PGUP); break;
    // case SINGLE_HOLD: register_code16(KC_PGUP); break;
    case SINGLE_HOLD: layer_on(NAVIUTIL0); break;
    case DOUBLE_TAP: register_code16(RCTL(KC_PGUP)); break;
    case DOUBLE_HOLD: layer_on(MEDIAWM0); break; 
    case DOUBLE_SINGLE_TAP: tap_code16(KC_PGUP); register_code16(KC_PGUP);
    case MORE_TAPS: break;
  }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[5].step) {
    case SINGLE_TAP: unregister_code16(KC_PGUP); break;
    // case SINGLE_HOLD: unregister_code16(KC_PGUP); break;
    case SINGLE_HOLD: layer_off(NAVIUTIL0); break;
    case DOUBLE_TAP: unregister_code16(RCTL(KC_PGUP)); break;
    case DOUBLE_HOLD: layer_off(MEDIAWM0); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_PGUP); break;
    case MORE_TAPS: break;
  }
  dance_state[5].step = 0;
}

void dance_6_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[6].step = dance_step(state);
  switch (dance_state[6].step) {
    case SINGLE_TAP: register_code16(KC_END); break;
    case SINGLE_HOLD: layer_on(EMACS0); break;
    case DOUBLE_TAP: register_code16(LCTL(KC_END)); break;
    case DOUBLE_HOLD: layer_on(EMACS1); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_END); register_code16(KC_END);
  }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[6].step) {
    case SINGLE_TAP: unregister_code16(KC_END); break;
    case SINGLE_HOLD: layer_off(EMACS0); break;
    case DOUBLE_TAP: unregister_code16(LCTL(KC_END)); break;
    case DOUBLE_HOLD: layer_off(EMACS1); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_END); break;
    case MORE_TAPS: break;
  }
  dance_state[6].step = 0;
}


void dance_7_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[7].step = dance_step(state);
  switch (dance_state[7].step) {
    case SINGLE_TAP: register_code16(KC_PGDN); break;
    case SINGLE_HOLD: layer_on(EMACS0); break;
    case DOUBLE_TAP: register_code16(RCTL(KC_PGDN)); break;
    case DOUBLE_HOLD: layer_on(EMACS1); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_PGDN); register_code16(KC_PGDN);
    case MORE_TAPS: break;
  }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[7].step) {
    case SINGLE_TAP: unregister_code16(KC_PGDN); break;
    case SINGLE_HOLD: layer_off(EMACS0); break;
    case DOUBLE_TAP: unregister_code16(RCTL(KC_PGDN)); break;
    case DOUBLE_HOLD: layer_off(EMACS1); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_PGDN); break;
    case MORE_TAPS: break;
  }
  dance_state[7].step = 0;
}


void dance_8_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[8].step = dance_step(state);
  switch (dance_state[8].step) {
    case SINGLE_TAP: register_code16(KC_LEFT); break;
    case SINGLE_HOLD: register_code16(KC_HOME); break;
    case DOUBLE_TAP: register_code16(LCTL(KC_LEFT)); break;
    case DOUBLE_HOLD: register_code16(LCTL(KC_HOME)); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT); register_code16(KC_LEFT);
    case MORE_TAPS: break;
  }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[8].step) {
    case SINGLE_TAP: unregister_code16(KC_LEFT); break;
    case SINGLE_HOLD: unregister_code16(KC_HOME); break;
    case DOUBLE_TAP: unregister_code16(LCTL(KC_LEFT)); break;
    case DOUBLE_HOLD: unregister_code16(LCTL(KC_HOME)); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT); break;
    case MORE_TAPS: break;
  }
  dance_state[8].step = 0;
}


void dance_9_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[9].step = dance_step(state);
  switch (dance_state[9].step) {
    case SINGLE_TAP: register_code16(KC_RGHT); break;
    case SINGLE_HOLD: register_code16(KC_END); break;
    case DOUBLE_TAP: register_code16(LCTL(KC_RGHT)); break;
    case DOUBLE_HOLD: register_code16(LCTL(KC_END)); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_RGHT); register_code16(KC_RGHT);
    case MORE_TAPS: break;
  }
}

void dance_9_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[9].step) {
    case SINGLE_TAP: unregister_code16(KC_RGHT); break;
    case SINGLE_HOLD: unregister_code16(KC_END); break;
    case DOUBLE_TAP: unregister_code16(LCTL(KC_RGHT)); break;
    case DOUBLE_HOLD: unregister_code16(LCTL(KC_END)); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_RGHT); break;
    case MORE_TAPS: break;
  }
  dance_state[9].step = 0;
}


void dance_10_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[10].step = dance_step(state);
  switch (dance_state[10].step) {
    case SINGLE_TAP: register_code16(KC_UP); break;
    case SINGLE_HOLD: register_code16(KC_PGUP); break;
    case DOUBLE_TAP: register_code16(RCTL(KC_UP)); break;
    case DOUBLE_HOLD: register_code16(RCTL(KC_PGUP)); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_UP); register_code16(KC_UP);
    case MORE_TAPS: break;
  }
}

void dance_10_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[10].step) {
    case SINGLE_TAP: unregister_code16(KC_UP); break;
    case SINGLE_HOLD: unregister_code16(KC_PGUP); break;
    case DOUBLE_TAP: unregister_code16(RCTL(KC_UP)); break;
    case DOUBLE_HOLD: unregister_code16(RCTL(KC_PGUP)); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_UP); break;
    case MORE_TAPS: break;
  }
  dance_state[10].step = 0;
}


void dance_11_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[11].step = dance_step(state);
  switch (dance_state[11].step) {
    case SINGLE_TAP: register_code16(KC_DOWN); break;
    case SINGLE_HOLD: register_code16(KC_PGDN); break;
    case DOUBLE_TAP: register_code16(RCTL(KC_DOWN)); break;
    case DOUBLE_HOLD: register_code16(RCTL(KC_PGDN)); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_DOWN); register_code16(KC_DOWN);
    case MORE_TAPS: break;
  }
}

void dance_11_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[11].step) {
    case SINGLE_TAP: unregister_code16(KC_DOWN); break;
    case SINGLE_HOLD: unregister_code16(KC_PGDN); break;
    case DOUBLE_TAP: unregister_code16(RCTL(KC_DOWN)); break;
    case DOUBLE_HOLD: unregister_code16(RCTL(KC_PGDN)); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOWN); break;
    case MORE_TAPS: break;
  }
  dance_state[11].step = 0;
}

void dance_12_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[12].step = dance_step(state);
  switch (dance_state[12].step) {
    case SINGLE_TAP: register_code16(KC_F1); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F1)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_12_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[12].step) {
    case SINGLE_TAP: unregister_code16(KC_F1); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F1)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[12].step = 0;
}


void dance_13_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[13].step = dance_step(state);
  switch (dance_state[13].step) {
    case SINGLE_TAP: register_code16(KC_F2); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F2)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_13_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[13].step) {
    case SINGLE_TAP: unregister_code16(KC_F2); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F2)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[13].step = 0;
}

void dance_14_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[14].step = dance_step(state);
  switch (dance_state[14].step) {
    case SINGLE_TAP: register_code16(KC_F3); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F3)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_14_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[14].step) {
    case SINGLE_TAP: unregister_code16(KC_F3); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F3)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[14].step = 0;
}

void dance_15_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[15].step = dance_step(state);
  switch (dance_state[15].step) {
    case SINGLE_TAP: register_code16(KC_F4); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F4)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_15_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[15].step) {
    case SINGLE_TAP: unregister_code16(KC_F4); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F4)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[15].step = 0;
}

void dance_16_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[16].step = dance_step(state);
  switch (dance_state[16].step) {
    case SINGLE_TAP: register_code16(KC_F5); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F5)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_16_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[16].step) {
    case SINGLE_TAP: unregister_code16(KC_F5); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F5)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[16].step = 0;
}

void dance_17_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[17].step = dance_step(state);
  switch (dance_state[17].step) {
    case SINGLE_TAP: register_code16(KC_F6); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F6)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_17_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[17].step) {
    case SINGLE_TAP: unregister_code16(KC_F6); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F6)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[17].step = 0;
}

void dance_18_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[18].step = dance_step(state);
  switch (dance_state[18].step) {
    case SINGLE_TAP: register_code16(KC_F7); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F7)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_18_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[18].step) {
    case SINGLE_TAP: unregister_code16(KC_F7); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F7)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[18].step = 0;
}

void dance_19_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[19].step = dance_step(state);
  switch (dance_state[19].step) {
    case SINGLE_TAP: register_code16(KC_F8); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F8)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_19_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[19].step) {
    case SINGLE_TAP: unregister_code16(KC_F8); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F8)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[19].step = 0;
}

void dance_20_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[20].step = dance_step(state);
  switch (dance_state[20].step) {
    case SINGLE_TAP: register_code16(KC_F9); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F9)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_20_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[20].step) {
    case SINGLE_TAP: unregister_code16(KC_F9); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F9)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[20].step = 0;
}

void dance_21_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[21].step = dance_step(state);
  switch (dance_state[21].step) {
    case SINGLE_TAP: register_code16(KC_F10); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F10)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_21_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[21].step) {
    case SINGLE_TAP: unregister_code16(KC_F10); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F10)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[21].step = 0;
}

void dance_22_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[22].step = dance_step(state);
  switch (dance_state[22].step) {
    case SINGLE_TAP: register_code16(KC_F11); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F11)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_22_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[22].step) {
    case SINGLE_TAP: unregister_code16(KC_F11); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F11)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[22].step = 0;
}


void dance_23_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[23].step = dance_step(state);
  switch (dance_state[23].step) {
    case SINGLE_TAP: register_code16(KC_F12); break;
    case SINGLE_HOLD: register_code16(LALT(KC_F12)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_23_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[23].step) {
    case SINGLE_TAP: unregister_code16(KC_F12); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_F12)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[23].step = 0;
}

void dance_24_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[24].step = dance_step(state);
  switch (dance_state[24].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F1)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F1)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_24_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[24].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F1)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F1)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[24].step = 0;
}

void dance_25_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[25].step = dance_step(state);
  switch (dance_state[25].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F2)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F2)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_25_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[25].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F2)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F2)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[25].step = 0;
}

void dance_26_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[26].step = dance_step(state);
  switch (dance_state[26].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F3)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F3)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_26_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[26].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F3)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F3)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[26].step = 0;
}

void dance_27_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[27].step = dance_step(state);
  switch (dance_state[27].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F4)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F4)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_27_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[27].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F4)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F4)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[27].step = 0;
}

void dance_28_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[28].step = dance_step(state);
  switch (dance_state[28].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F5)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F5)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_28_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[28].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F5)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F5)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[28].step = 0;
}

void dance_29_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[29].step = dance_step(state);
  switch (dance_state[29].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F6)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F6)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_29_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[29].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F6)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F6)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[29].step = 0;
}

void dance_30_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[30].step = dance_step(state);
  switch (dance_state[30].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F7)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F7)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_30_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[30].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F7)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F7)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[30].step = 0;
}

void dance_31_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[31].step = dance_step(state);
  switch (dance_state[31].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F8)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F8)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_31_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[31].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F8)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F8)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[31].step = 0;
}

void dance_32_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[32].step = dance_step(state);
  switch (dance_state[32].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F9)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F9)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_32_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[32].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F9)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F9)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[32].step = 0;
}

void dance_33_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[33].step = dance_step(state);
  switch (dance_state[33].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F10)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F10)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_33_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[33].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F10)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F10)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[33].step = 0;
}

void dance_34_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[34].step = dance_step(state);
  switch (dance_state[34].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F11)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F11)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_34_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[34].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F11)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F11)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[34].step = 0;
}

void dance_35_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[35].step = dance_step(state);
  switch (dance_state[35].step) {
    case SINGLE_TAP: register_code16(LCTL(KC_F12)); break;
    case SINGLE_HOLD: register_code16(LCA(KC_F12)); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
}

void dance_35_reset(tap_dance_state_t *state, void *user_data) {
  switch (dance_state[35].step) {
    case SINGLE_TAP: unregister_code16(LCTL(KC_F12)); break;
    case SINGLE_HOLD: unregister_code16(LCA(KC_F12)); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: break;
    case MORE_TAPS: break;
  }
  dance_state[35].step = 0;
}


tap_dance_action_t tap_dance_actions[] = {
  [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
  [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
  [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),
  [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset),
  [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_4_finished, dance_4_reset),
  [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_finished, dance_5_reset),
  [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_6_finished, dance_6_reset),
  [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_7_finished, dance_7_reset),
  [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_8_finished, dance_8_reset),
  [DANCE_9] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_9_finished, dance_9_reset),
  [DANCE_10] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_10_finished, dance_10_reset),
  [DANCE_11] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_11_finished, dance_11_reset),
  [DANCE_12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_12_finished, dance_12_reset),
  [DANCE_13] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_13_finished, dance_13_reset),
  [DANCE_14] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_14_finished, dance_14_reset),
  [DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_15_finished, dance_15_reset),
  [DANCE_16] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_16_finished, dance_16_reset),
  [DANCE_17] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_17_finished, dance_17_reset),
  [DANCE_18] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_18_finished, dance_18_reset),
  [DANCE_19] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_19_finished, dance_19_reset),
  [DANCE_20] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_20_finished, dance_20_reset),
  [DANCE_21] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_21_finished, dance_21_reset),
  [DANCE_22] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_22_finished, dance_22_reset),
  [DANCE_23] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_23_finished, dance_23_reset),
  [DANCE_24] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_24_finished, dance_24_reset),
  [DANCE_25] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_25_finished, dance_25_reset),
  [DANCE_26] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_26_finished, dance_26_reset),
  [DANCE_27] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_27_finished, dance_27_reset),
  [DANCE_28] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_28_finished, dance_28_reset),
  [DANCE_29] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_29_finished, dance_29_reset),
  [DANCE_30] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_30_finished, dance_30_reset),
  [DANCE_31] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_31_finished, dance_31_reset),
  [DANCE_32] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_32_finished, dance_32_reset),
  [DANCE_33] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_33_finished, dance_33_reset),
  [DANCE_34] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_34_finished, dance_34_reset),
  [DANCE_35] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_35_finished, dance_35_reset),
};

// Combos
/* enum combo_events {   */
/*   DOT_SPC, */
/*   SPC_DOT, */
/*   E_SPC, */
/*   SPC_E, */
/*   COMBO_LENGTH */
/* }; */

/* uint16_t COMBO_LEN = COMBO_LENGTH; */

/* const uint16_t PROGMEM dot_spc_combo[] = { KC_DOT, KC_SPC, COMBO_END }; */
/* const uint16_t PROGMEM spc_dot_combo[] = { KC_SPC, KC_DOT, COMBO_END }; */
/* const uint16_t PROGMEM e_spc_combo[] = { KC_E, KC_SPC, COMBO_END }; */
/* const uint16_t PROGMEM spc_e_combo[] = { KC_SPC, KC_E, COMBO_END }; */



/* combo_t key_combos[] = { */
/*   [DOT_SPC] = COMBO(dot_spc_combo, KC_NO), */
/*   [SPC_DOT] = COMBO(spc_dot_combo, KC_NO), */
/*   [E_SPC] = COMBO(e_spc_combo, KC_NO), */
/*   [SPC_E] = COMBO(spc_e_combo, KC_NO) */
/* }; */



/****************************************************************************************************
 *
 * Empty Keymap Template for Kinesis Advantage 
 *
 * ,-------------------------------------------------------------------------------------------------------------------.
 * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
 *          |      |      |      |      |                                         |      |      |      |      |
 *          `---------------------------'                                         `---------------------------'
 *                                        ,-------------.         ,-------------.
 *                                        |      |      |         |      |      |
 *                                 ,------|------|------|         |------+------+------.
 *                                 |      |      |      |         |      |      |      |
 *                                 |      |      |------|         |------|      |      |
 *                                 |      |      |      |         |      |      |      |
 *                                 `--------------------'         `--------------------'
 *    Tap Dances: 
 *    TD0:  tap/hold: L-Ctrl; double-tap: "("; tap-then-hold: LO(NAVIUTIL0)
 *    TD1:  tap/hold: R-Ctrl; double-tap: ")"; tap-then-hold: LO(NAVIUTIL0)
 *    TD2:  tap/hold: L-Alt; double-tap: "{"; tap-then-hold: LO(EMACS0)
 *    TD3:  tap/hold: L-Alt; double-tap: "}"; tap-then-hold: LO(EMACS0)
 *    TD4:  tap: Home; double-tap: L-CtrL(HOME); hold: L-Alt; tap-then-hold: LO(EMACS0)
 *    TD5:  tap: PgUp; double-tap: L-Ctrl(PgUp); hold: R-Alt; tap-then-hold: LO(EMACS0)
 *    TD6:  tap: End; double-tap: L-Ctrl(End); hold: L-Ctrl; tap-then-hold: LO(NAVIUTIL0)
 *    TD7:  tap: PgDn; double-tap: L-Ctrl(PgDn); hold: R-Ctrl; tap-then-hold: LO(NAVIUTIL0)
 *    TD8:  tap: Left; double-tap: L-Ctrl(Left); hold: Home; tap-then-hold: L-Ctrl(Home)
 *    TD9:  tap: Right; double-tap: L-Ctrl(Right); hold: End; tap-then-hold: L-Ctrl(End)
 *    TD11: tap: Up; double-tap: L-Ctrl(Up); hold: PgUp; tap-then-hold: R-Ctrl(PgUp)
 *    TD11: tap: Down; double-tap: L-Ctrl(Down); hold: PgDn; tap-then-hold: R-Ctrl(PgDn)
 *
 *    Macros: 
 *    SM0;  Emacs new line (C-q C-j)                        
 *    SM1:  Emacs kill current buffer (C-x k enter)     
 *    SM2:  Emacs open file (C-x C-f)                   
 *    SM3:  Emacs run code block in Python/R (C-c C-c)  
 *    SM4:  Emacs save file (C-x C-f)                   
 *    SM5:  Emacs list buffers  (C-x C-b)               
 *    SM6:  Emacs write file (C-x C-w)                  
 *
 */

/*  keycode template 
[] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       // Left Top Rubber Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Left Second Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Left Third Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Left Fourth Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Left Fifth Row
            KC_NO, KC_NO, KC_NO, KC_NO,                                          // Left Bottom Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Left Thumb Cluster
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       // Right Top Rubber Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Right Second Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Right Third Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Right Fourth Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            // Right Fifth Row
            KC_NO, KC_NO, KC_NO, KC_NO,                                          // Right Bottom Row
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),                           // Right Thumb Cluster            
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /****************************************************************************************************
   *
   * Keymap: Default Layer in Dvorak
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * | ESC    |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | \|     |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * | Tab    |  '"  |  ,<  |  .>  |   P  |   Y  |                           |   F  |   G  |   C  |   R  |   L  | /?     |
   * |--------+------+------+------+------+--- --|                           |------+------+------+------+------+--------|
   * | =+     |   A  |   O  |   E  |   U  |   I  |                           |   D  |   H  |   T  |   N  |   S  | -_     |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * | OSMSfL |  ;:  |   Q  |   J  |   K  |   X  |                           |   B  |   M  |   W  |   V  |   Z  | OSMSfR |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |LT4(`)| GT(M)| Left |Right |                                         |  Up  | Down | GT([)|LT4(])|
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        | TD0  | TD2  |         | TD3  | TD1  |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      | TD4  |         | TD5  |      |      |
   *                                 |Space | BkSp |------|         |------|Return| Space|
   *                                 |      |      | TD6  |         | TD7  |      |      |
   *                                 `--------------------'         `--------------------'
   *
   *    Tap Dances:
   *    TD0:  tap/hold: L-Ctrl; double-tap: "("; tap-then-hold: LO(NAVIUTIL0)
   *    TD1:  tap/hold: R-Ctrl; double-tap: ")"; tap-then-hold: LO(NAVIUTIL0)
   *    TD2:  tap/hold: L-Alt; double-tap: "{"; tap-then-hold: LO(EMACS0)
   *    TD3:  tap/hold: L-Alt; double-tap: "}"; tap-then-hold: LO(EMACS0)
   *    TD4:  tap: Home; double-tap: L-CtrL(HOME); hold: L-Alt; tap-then-hold: LO(EMACS0)
   *    TD5:  tap: PgUp; double-tap: L-Ctrl(PgUp); hold: R-Alt; tap-then-hold: LO(EMACS0)
   *    TD6:  tap: End; double-tap: L-Ctrl(End); hold: L-Ctrl; tap-then-hold: LO(NAVIUTIL0)
   *    TD7:  tap: PgDn; double-tap: L-Ctrl(PgDn); hold: R-Ctrl; tap-then-hold: LO(NAVIUTIL0)
   *    
   */
  [DVORAK0] = LAYOUT(KC_NO,                 KC_F1,          KC_F2,           KC_F3,                  KC_F4,   KC_F5,       KC_F6,   KC_F7, KC_F8,   // Left Top Rubber Row
                     KC_ESC,                KC_1,           KC_2,            KC_3,                   KC_4,    KC_5,                                 // Left Second Row
                     KC_TAB,                KC_QUOT,        KC_COMM,         KC_DOT,                 KC_P,    KC_Y,                                 // Left Third Row 
                     KC_EQL,                KC_A,           KC_O,            KC_E,                   KC_U,    KC_I,                                 // Left Fourth Row
                     KC_LSFT,               KC_SCLN,        KC_Q,            KC_J,                   KC_K,    KC_X,                                 // Left Fifth Row 
                     LT(NAVIUTIL1, KC_GRV), LGUI_T(KC_APP), KC_LEFT,         KC_RGHT,                                                               // Left Bottom Row  
                     TD(DANCE_0),           TD(DANCE_2),    TD(DANCE_4),     KC_SPC,                 KC_BSPC, TD(DANCE_6),                          // Left Thumb Cluster
                     KC_F9,                 KC_F10,         KC_F11,          KC_F12,                 KC_PSCR, KC_SCRL,     KC_PAUS, KC_NO, KC_NO,   // Right Top Rubber Row
                     KC_6,                  KC_7,           KC_8,            KC_9,                   KC_0,    KC_BSLS,                              // Right Second Row
                     KC_F,                  KC_G,           KC_C,            KC_R,                   KC_L,    KC_SLSH,                              // Right Third Row 
                     KC_D,                  KC_H,           KC_T,            KC_N,                   KC_S,    KC_MINS,                              // Right Fourth Row
                     KC_B,                  KC_M,           KC_W,            KC_V,                   KC_Z,    KC_RSFT,                              // Right Fifth Row
                     KC_UP,                 KC_DOWN,        LGUI_T(KC_LBRC), LT(NAVIUTIL1, KC_RBRC),                                                // Right Bottom Row
                     TD(DANCE_3),           TD(DANCE_1),    TD(DANCE_5),     TD(DANCE_7),            KC_ENT,  KC_SPC),                              // Right Thumb Cluster

  /****************************************************************************************************
   *
   * Keymap: Default Layer in Qwerty
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * | ESC    |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * | =+     |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * | OSMSfL |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | OSMSfR |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          | `~   | GT(M)| Left | Right|                                         | Up   | Down |LG([) |LT4(])|
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        | TD0  | TD2  |         | TD3  | TD1  |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      | TD4  |         | TD5  |      |      |
   *                                 | Space| BkSp |------|         |------|Return| Space|
   *                                 |      |      | TD6  |         | TD7  |      |      |
   *                                 `--------------------'         `--------------------'
   *
   *    Tap Dances: 
   *    TD0:  tap/hold: L-Ctrl; double-tap: "("; tap-then-hold: LO(NAVIUTIL0)
   *    TD1:  tap/hold: R-Ctrl; double-tap: ")"; tap-then-hold: LO(NAVIUTIL0)
   *    TD2:  tap/hold: L-Alt; double-tap: "{"; tap-then-hold: LO(EMACS0)
   *    TD3:  tap/hold: L-Alt; double-tap: "}"; tap-then-hold: LO(EMACS0)
   *    TD4:  tap: Home; double-tap: L-CtrL(HOME); hold: L-Alt; tap-then-hold: LO(EMACS0)
   *    TD5:  tap: PgUp; double-tap: L-Ctrl(PgUp); hold: R-Alt; tap-then-hold: LO(EMACS0)
   *    TD6:  tap: End; double-tap: L-Ctrl(End); hold: L-Ctrl; tap-then-hold: LO(NAVIUTIL0)
   *    TD7:  tap: PgDn; double-tap L-Ctrl(PgDn); hold: R-Ctrl; tap-then-hold: LO(NAVIUTIL0)
   *    
   */
  [QWERTY0] = LAYOUT(KC_NO,                 KC_F1,          KC_F2,           KC_F3,                 KC_F4,   KC_F5,       KC_F6, KC_F7, KC_F8,     // Left Top Rubber Row   
                     KC_ESC,                KC_1,           KC_2,            KC_3,                  KC_4,    KC_5,                                 // Left Second Row       
                     KC_TAB,                KC_Q,           KC_W,            KC_E,                  KC_R,    KC_T,                                 // Left Third Row        
                     KC_RBRC,               KC_A,           KC_S,            KC_D,                  KC_F,    KC_G,                                 // Left Fourth Row       
                     KC_LSFT,               KC_Z,           KC_X,            KC_C,                  KC_V,    KC_B,                                 // Left Fifth Row        
                     LT(NAVIUTIL1, KC_GRV), LGUI_T(KC_APP), KC_LEFT,         KC_RGHT,                                                              // Left Bottom Row       
                     TD(DANCE_0),           TD(DANCE_2),    TD(DANCE_4),     KC_SPC,                KC_BSPC, TD(DANCE_6),                          // Left Thumb Cluster
                     KC_F9,                 KC_F10,         KC_F11,          KC_F12,                KC_PSCR, KC_SCRL,     KC_PAUS, KC_NO, KC_NO,   // Right Top Rubber Row  
                     KC_6,                  KC_7,           KC_8,            KC_9,                  KC_0,    KC_BSLS,                              // Right Second Row      
                     KC_Y,                  KC_U,           KC_I,            KC_O,                  KC_P,    KC_LBRC,                              // Right Third Row       
                     KC_H,                  KC_J,           KC_K,            KC_L,                  KC_SCLN, KC_QUOT,                              // Right Fourth Row      
                     KC_N,                  KC_M,           KC_COMM,         KC_DOT,                KC_SLSH, KC_RSFT,                              // Right Fifth Row       
                     KC_UP,                 KC_DOWN,        LGUI_T(KC_MINS), LT(NAVIUTIL1, KC_EQL),                                                // Right Bottom Row
                     TD(DANCE_3),           TD(DANCE_1),    TD(DANCE_5),     TD(DANCE_7),           KC_ENT,  KC_SPC),                              // Right Thumb Cluster

  /****************************************************************************************************
   *
   * Keymap: Default Layer in Naviutil0 
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * |  TD12  | TD13 | DT14 | TD15 | TD16 | TD17 |                           | TD18 | TD19 | TD20 | TD21 | TD22 | TD23   |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * | DF(0)  |      |  MB2 |  MU  | MB1  |  MWU |                           |      |      |      |      |      | DF(1)  |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * | DF(7)  |  MWL |  ML  |  MD  |  MR  |  MWR |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      | BRBW | BREF | BRFW |  MWD |                           |  MB1 |      |      |      |      |        |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |      |      |      |      |                                         |      |      |      |      |
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        |      |      |         |      |      |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      |      |         |      |      |      |
   *                                 |      |      |------|         |------|      |      |
   *                                 |      |      |      |         |      |      |      |
   *                                 `--------------------'         `--------------------'
   *
   *      Keys:
   *      BRBW: browser backward
   *      BRBF: browser forward
   *      BRSC: broswer refresh
   *
   *      Combo:
   *      CAD: Ctrl+Alt+Delete
   *
   *      Tap Dance: 
   *      TD12: tap: F1, hold: L-Alt(F1)              
   *      TD13: tap: F2, hold: L-Alt(F2)              
   *      TD14: tap: F3, hold: L-Alt(F3)              
   *      TD15: tap: F4, hold: L-Alt(F4)              
   *      TD16: tap: F5, hold: L-Alt(F5)              
   *      TD17: tap: F6, hold: L-Alt(F6)              
   *      TD18: tap: F7, hold: L-Alt(F7)              
   *      TD19: tap: F8, hold: L-Alt(F8)              
   *      TD20: tap: F9, hold: L-Alt(F9)              
   *      TD21: tap: F10, hold: L-Alt(F10)            
   *      TD22: tap: F11, hold: L-Alt(F11)            
   *      TD23: tap: F12, hold: L-Alt(F12)
   *
   */
  [NAVIUTIL0] = LAYOUT(KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO, KC_NO, KC_NO,  // Left Top Rubber Row   
                       TD(DANCE_12), TD(DANCE_13), TD(DANCE_14), TD(DANCE_15), TD(DANCE_16), TD(DANCE_17),                       // Left Second Row       
                       DF(DVORAK0),  KC_NO,        KC_BTN2,      KC_MS_U,      KC_BTN1,      KC_WH_U,                            // Left Third Row        
                       DF(NUMPAD0),  KC_WH_L,      KC_MS_L,      KC_MS_D,      KC_MS_R,      KC_WH_R,                            // Left Fourth Row       
                       KC_NO,        KC_NO,        KC_WBAK,      KC_WREF,      KC_WFWD,      KC_WH_D,                            // Left Fifth Row        
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                          // Left Bottom Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                              // Left Thumb Cluster    
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO, KC_NO, KC_NO,  // Right Top Rubber Row  
                       TD(DANCE_18), TD(DANCE_19), TD(DANCE_20), TD(DANCE_21), TD(DANCE_22), TD(DANCE_23),                       // Right Second Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        DF(QWERTY0),                        // Right Third Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                              // Right Fourth Row      
                       KC_BTN1,      KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                              // Right Fifth Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,                                                          // Right Bottom Row      
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO),                             // Right Thumb Cluster
  
  /****************************************************************************************************
   *
   * Keymap: Default Layer in NAVIUTLI1
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * |  TD24  | TD25 | DT26 | TD27 | TD28 | TD29 |                           | TD30 | TD31 | TD32 | TD33 | TD34 | TD35   |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |      |      | CAL  | CAR  |                                         | CAU  | CAD  |      |      |
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        |      |      |         |      |       |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      |      |         |      |      |      |
   *                                 |      | CAD  |------|         |------|      |      |
   *                                 |      |      |      |         |      |      |      |
   *                                 `--------------------'         `--------------------'
   *      Tap Dance: 
   *      TD24: tap: L-Ctrl(F1), hold: L-Alt(F1)      
   *      TD25: tap: L-Ctrl(F2), hold: L-Ctrl-Alt(F2) 
   *      TD26: tap: L-Ctrl(F3), hold: L-Ctrl-Alt(F3) 
   *      TD27: tap: L-Ctrl(F4), hold: L-Ctrl-Alt(F4) 
   *      TD28: tap: L-Ctrl(F5), hold: L-Ctrl-Alt(F5) 
   *      TD29: tap: L-Ctrl(F6), hold: L-Ctrl-Alt(F6) 
   *      TD30: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F7) 
   *      TD31: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F8) 
   *      TD32: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F9) 
   *      TD33: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F10)
   *      TD34: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F11)
   *      TD35: tap: L-Ctrl(F7), hold: L-Ctrl-Alt(F12)
   */

  [NAVIUTIL1] = LAYOUT(KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO, KC_NO, KC_NO,    // Left Top Rubber Row   
                       TD(DANCE_24), TD(DANCE_25), TD(DANCE_26), TD(DANCE_27), TD(DANCE_28), TD(DANCE_29),                         // Left Second Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                // Left Third Row        
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                // Left Fourth Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                                // Left Fifth Row        
                       KC_NO,        KC_NO,        LCA(KC_LEFT), LCA(KC_RGHT),                                                     // Left Bottom Row       
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        LCA(KC_DEL),  KC_NO,                                // Left Thumb Cluster    
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO, KC_NO, KC_NO,    // Right Top Rubber Row  
                       TD(DANCE_30), TD(DANCE_31), TD(DANCE_32), TD(DANCE_33), TD(DANCE_34), TD(DANCE_35),                         // Right Second Row      
                       KC_NO,        KC_NO, KC_NO, KC_NO,        KC_NO,        KC_NO,                                              // Right Third Row
                       KC_NO,        KC_NO, KC_NO, KC_NO,        KC_NO,        KC_NO,                                              // Right Fourth Row
                       KC_NO,        KC_NO, KC_NO, KC_NO,        KC_NO,        KC_NO,                                              // Right Fifth Row
                       LCA(KC_UP),   LCA(KC_DOWN), KC_NO,        KC_NO,                                                            // Right Bottom Row      
                       KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO),                               // Right Thumb Cluster   

  /****************************************************************************************************
   *
   * Keymap for layer EMACS0
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |  OF  |      |  RC  |      |      |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |  SF  |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |  NL  |      |  KB  |      |                           |  LB  |      |  SA  |      |      |        |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |      |      |      |      |                                         |      |      |      |      |
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        |      |      |         |       |      |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      |      |         |      |      |      |
   *                                 |      |      |------|         |------|      |      |
   *                                 |      |      |      |         |      |      |      |
   *                                 `--------------------'         `--------------------'
   *
   *       Macros:                                               
   *       SM0;  Emacs new line (C-q C-j)                    
   *       SM1:  Emacs kill current buffer (C-x k enter)     
   *       SM2:  Emacs open file (C-x C-f)                   
   *       SM3:  Emacs run code block in Python/R (C-c C-c)  
   *       SM4:  Emacs save file (C-x C-f)                   
   *       SM5:  Emacs list buffers  (C-x C-b)               
   *       SM6:  Emacs write file (C-x C-w)                  
   *
   */
  [EMACS0] = LAYOUT(KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO,          // Left Top Rubber Row   
                    KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO,                               // Left Second Row       
                    KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO,                               // Left Third Row        
                    KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO,                               // Left Fourth Row       
                    KC_NO,      KC_NO, ST_MACRO_0, KC_NO, ST_MACRO_1, KC_NO,                               // Left Fifth Row        
                    KC_NO,      KC_NO, KC_NO,      KC_NO,                                                  // Left Bottom Row       
                    KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO,                               // Left Thumb Cluster    
                    KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO,          // Right Top Rubber Row  
                    KC_NO,      KC_NO, ST_MACRO_3, KC_NO, KC_NO,      KC_NO,                               // Right Second Row      
                    ST_MACRO_2, KC_NO, ST_MACRO_3, KC_NO, KC_NO,      KC_NO,                               // Right Third Row       
                    KC_NO,      KC_NO, KC_NO,      KC_NO, ST_MACRO_4, KC_NO,                               // Right Fourth Row      
                    ST_MACRO_5, KC_NO, ST_MACRO_6, KC_NO, KC_NO,      KC_NO,                               // Right Fifth Row       
                    KC_NO,      KC_NO, KC_NO,      KC_NO,                                                  // Right Bottom Row      
                    KC_NO,      KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO),                                   // Right Thumb Cluster   

  /****************************************************************************************************
   *
   * Keymap EMACS1, mostly for org-mode 
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * | SM7    |      | SM12 | SM8  |      |      |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * |        |      | SM10 | SM9  | SM11 |      |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |      |      |      |      |                                         |      |      |      |      |
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        |      |      |         |      |      |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      |      |         |      |      |      |
   *                                 |      |      |------|         |------|      |      |
   *                                 |      |      |      |         |      |      |      |
   *                                 `--------------------'         `--------------------'
   *    Tap Dances: 
   *
   *    Macros:
   *    SM7:   C-u C-u C-u tab show all drawer
   *    SM8:   C-c C-p previous heading
   *    SM9:   C-c C-n next heading
   *    SM10:  C-c C-b prvious heding same level
   *    SM11:  C-C C-f next heading same level
   *    SM12:  C-c C-u back to higher level heading 
   *
   */
  [EMACS1] = LAYOUT(KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO,        // Left Top Rubber Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Left Second Row
                    ST_MACRO_7, KC_NO, ST_MACRO_12, ST_MACRO_8, KC_NO,       KC_NO,                             // Left Third Row
                    KC_NO,      KC_NO, ST_MACRO_10, ST_MACRO_9, ST_MACRO_11, KC_NO,                             // Left Fourth Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Left Fifth Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,                                                      // Left Bottom Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Left Thumb Cluster
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO,        // Right Top Rubber Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Right Second Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Right Third Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Right Fourth Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO,                             // Right Fifth Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,                                                      // Right Bottom Row
                    KC_NO,      KC_NO, KC_NO,       KC_NO,      KC_NO,       KC_NO),                            // Right Thumb Cluster
 

  /****************************************************************************************************
   *
   * Keymap for MEDIAWM0
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * | BOOT   |      |      |      |      |      |                           |      |      |      |      |      | PWR    |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * |        | BRIU | MYC  |      | PLR  |      |                           |  VU  |      |  CLC |      |      | Sleep  |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      | SCH  |      |      |      |                           |  MU  |  PRV | STP  | PLY  | NXT  | Wake   |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        | BRID |      |      |      |      |                           |  VD  |  MIL | EJCT |      |      |        |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |      |      |      |      |                                         |      |      |      |      |
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        |      |      |         |      |      |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      |      |         |      |      |      |
   *                                 |      |      |------|         |------|      |      |
   *                                 |      |      |      |         |      |      |      |
   *                                 `--------------------'         `--------------------'
   *    Tap Dances: 
   *
   *    Macros: 
   *
   */

  [MEDIAWM0] = LAYOUT(KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,        // Left Top Rubber Row
                      QK_BOOT,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                               // Left Second Row
                      KC_NO,        KC_BRIU, KC_MYCM, KC_NO,   KC_MSEL, KC_NO,                               // Left Third Row
                      KC_NO,        KC_NO,   KC_WSCH, KC_NO,   KC_NO,   KC_NO,                               // Left Fourth Row
                      KC_NO,        KC_BRID, KC_NO,   KC_NO,   KC_NO,   KC_NO,                               // Left Fifth Row
                      KC_NO,        KC_NO,   KC_NO,   KC_NO,                                                 // Left Bottom Row
                      KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                               // Left Thumb Cluster
                      KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,        // Right Top Rubber Row
                      KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PWR,                              // Right Second Row
                      KC_VOLU,      KC_NO,   KC_CALC, KC_NO,   KC_NO,   KC_SLEP,                             // Right Third Row       
                      KC_MUTE,      KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_WAKE,                             // Right Fourth Row      
                      KC_VOLD,      KC_MAIL, KC_EJCT, KC_NO,   KC_NO,   KC_NO,                               // Right Fifth Row       
                      KC_NO,        KC_NO,   KC_NO,   KC_NO,                                                 // Right Bottom Row
                      KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),                              // Right Thumb Cluster            

  /****************************************************************************************************
   *
   * Empty Keymap Template for Kinesis Advantage 
   *
   * ,-------------------------------------------------------------------------------------------------------------------.
   * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
   * | DF(0)  |      |      |  Up  |      |      |                           |      |  NL  |  =   |   /  |  *   | DF(1)  |
   * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
   * |        |      | Left | Down |Right |      |                           |      |  7   |  8   |   9  |  -   |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |      |  4   |  5   |  6   |  +   |        |
   * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                           |   0  |  1   |  2   |  3   |Enter |        |
   * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
   *          |      |      |      |      |                                         |      |      |   .  |Enter |
   *          `---------------------------'                                         `---------------------------'
   *                                        ,-------------.         ,-------------.
   *                                        |      |      |         |      |      |
   *                                 ,------|------|------|         |------+------+------.
   *                                 |      |      |      |         |      |      |      |
   *                                 |Space | Bksp |------|         |------|Enter |Space |
   *                                 |      |      |      |         |      |      |      |
   *                                 `--------------------'         `--------------------'
   *    Tap Dances:
   *    
   */  
  [NUMPAD0] = LAYOUT(KC_NO,       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO, KC_NO, KC_NO,  // Left Top Rubber Row
                     DF(DVORAK0), KC_NO,  KC_NO,   KC_UP,   KC_NO,   KC_NO,                             // Left Second Row
                     KC_NO,       KC_NO,  KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,                             // Left Third Row
                     KC_NO,       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,                             // Left Fourth Row
                     KC_LSFT,     KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,                             // Left Fifth Row
                     KC_NO,       KC_NO,  KC_NO,   KC_NO,                                               // Left Bottom Row
                     KC_NO,       KC_NO,  KC_NO,   KC_SPC,  KC_BSPC, KC_NO,                             // Left Thumb Cluster
                     KC_NO,       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO, KC_NO, KC_NO,  // Right Top Rubber Row
                     KC_NO,       KC_NUM, KC_EQL,  KC_SLSH, KC_ASTR, DF(QWERTY0),                       // Right Second Row
                     KC_NO,       KC_7,   KC_8,    KC_9,    KC_MINS, KC_NO,                             // Right Third Row
                     KC_NO,       KC_4,   KC_5,    KC_6,    KC_PLUS, KC_NO,                             // Right Fourth Row
                     KC_0,        KC_1,   KC_2,    KC_3,    KC_ENT,  KC_RSFT,                           // Right Fifth Row
                     KC_NO,       KC_NO,  KC_DOT,  KC_ENT,                                              // Right Bottom Row
                     KC_NO,       KC_NO,  KC_NO,   KC_NO,   KC_ENT,  KC_SPC)                            // Right Thumb Cluster            
};
