// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define _______ KC_TRNS
#define ______  KC_TRNS
#define _____   KC_TRNS
#define ____    KC_TRNS
#define XXXXXXX KC_NO
#define ___x___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|  LGui  |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,
        KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    ______,
        F(5),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    ______,
  ALL_T(KC_ESC), ____,    ____, KC_LALT,     MO(SYMB),
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_LGUI, F(5),    KC_END,
        // right hand
        KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        ______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, F(6),
        ______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
                      MO(MDIA),    KC_RALT, ______,  _______, ALL_T(KC_ESC),
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, ALL_T(KC_ESC), KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
        // left hand
        ______,  ____,    ____,    ____,    ____,    ____,    _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  ____,    _______,
        _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, ____,
        _______, KC_LPRN, KC_RPRN, _______, _______, ____,    _______,
        _______, ____,    ____,    _______, _______,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_LGUI, F(5),    KC_END,
        // right hand
        ______,  ____,    ____,    ____,    ____,    ____,    _______,
        ______,  _______, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_DEL,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, S(KC_SCLN), _______,
        ______,  _______, KC_QUOT, S(KC_COMM), S(KC_DOT), KC_BSLS, _______,
                          _______, ____,    ____,    _______, _______,
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, KC_BSPC, KC_TAB
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
        // left hand
        ______,  ____,    ____,    ____,    ____,    ____,    _______,
        KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    ____,    _______,
        _______, KC_5,    KC_6,    KC_7,    KC_8,    ____,
        _______, KC_9,    KC_0,    _______, _______, ____,    _______,
        _______, ____,    ____,    _______, _______,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_LGUI, F(5),    KC_END,
        // right hand
        ______,  ____,    ____,    ____,    ____,    ____,    _______,
        _______, _______, KC_UNDS, KC_PPLS, KC_LBRC, KC_RBRC, KC_DEL,
                 _______, _______, ____,    ____,    _______, _______,
        ______,  ____, S(KC_QUOT), ____,    _______, _______, _______,
                          _______, ____,    ____,    _______, _______,
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, KC_BSPC, KC_TAB
),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
  [5] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
  [6] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
