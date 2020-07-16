#include QMK_KEYBOARD_H

enum my_keycodes {
  FN_RIGHT = SAFE_RANGE,
  FN_CAPSLCK,
  FN_OE_LC,
  FN_UE_LC,
  FN_AE_LC,
  FN_OE_UC,
  FN_UE_UC,
  FN_AE_UC,
  FN_SCHARFES_S,
};

#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT_all(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
                   KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
                   FN_CAPSLCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_ENT,
                   KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, KC_UP, KC_SLSH,
                   KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_DEL, FN_RIGHT, KC_LEFT, KC_DOWN, KC_RGHT),
	[_FL] = LAYOUT_all(KC_GRAVE, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_F12,  _______, _______,
                   _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                   _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, _______, KC_AUDIO_MUTE, KC_PGUP ,KC_MEDIA_PLAY_PAUSE,
                   _______, _______, _______,                            _______,                                     KC_INSERT, _______, KC_HOME, KC_PGDOWN, KC_END)
};

// Loop
void matrix_scan_user(void) {
  // Empty
};

bool is_fn_active = false;
bool is_shift_active = false;

void setFnStatus(bool fnStatus) {
  is_fn_active = fnStatus;
};

void setShiftStatus(bool shiftStatus) {
  is_shift_active = shiftStatus;
};

bool processUmlaut(uint16_t keycode, keyrecord_t *record) {
  if (is_fn_active && record->event.pressed) {
    if(keycode == KC_O) {
      if(is_shift_active){
        unregister_code(KC_LSFT);
        SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_5)SS_TAP(X_KP_3))); //Uppercase OE
        register_code(KC_LSFT);
        return false;
      } else {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_8))); //Lowercase OE
        return false;
      }
    } else if(keycode == KC_A) {
      if(is_shift_active){
        unregister_code(KC_LSFT);
        SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_2))); //Uppercase AE
        register_code(KC_LSFT);
        return false;
      } else {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_2))); //Lowercase AE
        return false;
      }
    } else if(keycode == KC_U) {
      if(is_shift_active){
        unregister_code(KC_LSFT);
        SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_5)SS_TAP(X_KP_4))); //Uppercase UE
        register_code(KC_LSFT);
        return false;
      } else {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_9))); //Lowercase UE
        return false;
      }
    } else if(keycode == KC_S) {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_5))); //Scharfes S
        return false;
    } else if(keycode == KC_E) {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8))); //Scharfes Euro
        return false;
    }
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN_RIGHT:
      if (record->event.pressed) {
        setFnStatus(true);
        layer_on(_FL);
      } else {
        setFnStatus(false);
        layer_off(_FL);
      }
      return false; // Skip all further processing of this key
    case FN_CAPSLCK:
      if (record->event.pressed) {
        setFnStatus(true);
        layer_on(_FL);
      } else {
        setFnStatus(false);
        layer_off(_FL);
      }
      return false; // Skip all further processing of this key
    case KC_LSFT:
      if (record->event.pressed) {
        setShiftStatus(true);
      } else {
        setShiftStatus(false);
      }
      return true;
    default:
      return processUmlaut(keycode, record);
  }
}
