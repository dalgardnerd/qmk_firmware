
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define FN_ESC LT(1, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_F13,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PSCR,
        KC_F14,   FN_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT, KC_PGUP,
        KC_F15,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_F16,   KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                    MO(1),                       KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_all(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______,  KC_DEL,
        UG_TOGG,  _______, UG_PREV, UG_VALU, UG_NEXT, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
        _______,  QK_LOCK, UG_HUED, UG_VALD, UG_HUEU, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______,                            QK_LEAD,                   _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
    ),

    [2] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),

};

static bool left_shift_pressed = false;
static bool right_shift_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FN_ESC:
            if (record->event.pressed) {
                // Turn off Caps Lock when Esc is pressed
                if (host_keyboard_led_state().caps_lock) {
                    tap_code(KC_CAPS);
                }
            }
            break;
        case KC_LSFT:
            left_shift_pressed = record->event.pressed;
            break;
        case KC_RSFT:
            right_shift_pressed = record->event.pressed;
            break;

    }

    if (left_shift_pressed && right_shift_pressed) {
        tap_code(KC_CAPS); // Toggle Caps Lock
        // Reset the state to prevent multiple triggers
        left_shift_pressed = false;
        right_shift_pressed = false;
    }

    return true;
}

// bool encoder_update_user(uint8_t index, bool clockwise) {
//   // Encoder is mapped to volume functions by default
//   if (clockwise) {
//     tap_code(KC_VOLU);
//   } else {
//     tap_code(KC_VOLD);
//   }
//     return true;
// }

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {

    if (leader_sequence_three_keys(KC_T,KC_I,KC_G)) {
        // Leader, f => Types the below string
        SEND_STRING("thatiphoneguy@gmail.com");
    } else if (leader_sequence_three_keys(KC_B, KC_I, KC_T)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING("Nothing is real, smooth jazz fails.");
    } else if (leader_sequence_three_keys(KC_L, KC_E, KC_T)) {
        // Leader, d, d, s => Types the below string
        SEND_STRING("Lethal Military Android");
    }
}
