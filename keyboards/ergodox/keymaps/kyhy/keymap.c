/*
 * About this keymap:
 *
 * The layout shown herestems from my early Kinesis years, using the Contour PS/2 with a
 * software layout. Because of this, the RBRC and LBRC were on opposite sides of the board in the corner
 * keys. I've decided to continue using this layout with my ErgoDox.
 *
 * The QWERTY layout shown here is based entirely on the Kinesis Advantage layout, with the additional
 * keys as shown in the diagrams. The Colemak layout is merely an adaptation of that.
 *
 * I've enabled persistent keymaps for Qwerty, and Colemak layers, similar to the default Planck
 * layouts.
 *
 */

#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "action_tapping.h"

extern keymap_config_t keymap_config;

#define _QW 1 // Qwerty layer
#define _CM 2 // Colemak layer
#define _MD 3 // Media Layer
#define _KP 4 // Keypad Layer
#define _SB 5 // Symbol Layer
#define _NB 6 // Number Layer

// Macro name shortcuts
#define QWERTY M(_QW)
#define COLEMAK M(_CM)
#define SYMBOL M(_SB)
#define NUMBER M(_NB)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ______  KC_TRNS
#define _____   KC_TRNS
#define ____    KC_TRNS
#define XXXXXXX KC_NO
#define ___x___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 1: QWERTY
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |  Tab   |   1  |   2  |   3  |   4  |   5  | ESC  | | ESC  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * |   `    |   Q  |   W  |   E  |   R  |   T  |      | |      |   Y  |   U  |   I  |   O  |   P  | Bksp   |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  | Ctrl   |
 * |--------+------+------+------+------+------| _MD  | | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |Hyper |      |      |  Alt |Symbol|                             |Number|  Alt |      |      | RGUI |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RALT | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | Cmd  | Ctrl |------| |------| Bksp | Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 */
[_QW] = KEYMAP(
        // left hand
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,
        KC_GRV, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,
        F(5),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_MD),
  ALL_T(KC_ESC), ____,    ____, KC_LALT,     _SB,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_LGUI, F(5),    KC_END,
        // right hand
        KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, F(6),
        MO(_KP), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                           _NB,   KC_RALT, ______,  _______, ALL_T(KC_ESC),
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, KC_BSPC, KC_SPC
  ),

/* Based on: */
/* Symbol Layer (Lower)
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |      |      |   -  |   =  |  {   |   }  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   %  |   ^  |   &  |   *  |      | Left | Down |  Up  |Right |   :  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   (  |   )  |      |      |      |      |  '   |  <   |  >   |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  Tab |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
  [_SB] = KEYMAP(
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

/* Based on: */
/* Number Layer (Raise)
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |      |      |  _   |   +  |  [   |  ]   | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   5  |   6  |   7  |   8  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   9  |   0  |      |      |      |      |  "   |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_NB] = KEYMAP(
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

/* Layer 2 : Colemak
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  | | ESC  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |      | |      |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | BkSpc  |   A  |   R  |   S  |   T  |   D  |------| |------|   H  |   N  |   E  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------| _MD  | | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   K  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                             |  Up  |  Dn  |   /  |   =  | RGUI |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RALT | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | BkSp | Del  |------| |------| Enter| Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 */
[_CM] = KEYMAP(
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,
        KC_DELT, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    XXXXXXX,
        KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_MD),
        KC_LGUI, KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
                 KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        MO(_KP), KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_RGUI,
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
  ),


/* Layer 3 : Media layer
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | TEENSY |  F1  |  F2  |  F3  |  F4  |  F5  | F11  | |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * |        |      | PrSc | ScLk | Paus |      |      | |      |      | Mute | Vol- | Vol+ |      |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------| |------| Stop | Prev | Play | Next | Sel  |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        |      |      |Qwerty|Colemk|      |      | |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                             |      |      |      |      |      |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      |      |      | |      |      |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      |      | |      |      |      |
 *                               |      |      |------| |------|      |      |
 *                               |      |      |      | |      |      |      |
 *                               `--------------------' `--------------------'
 */
[_MD] = KEYMAP(
        // left hand
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
        _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, ______,  QWERTY,  COLEMAK, _______, _______,
        _______, _______, _______, _______, _______,
                                            _______, _______,
                                                     _______,
                                   _______, _______, _______,
        // right hand
        KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                 KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, _______,
        _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
        _______, _______,
        _______,
        _______, _______, _______
  ),


/* Layer 4 : Keypad layer
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | Power  |      |      |      |      |      |      | |      |      | NmLk | KP = | KP / | KP * |        |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Sleep  |      |      |      |      |      |      | |      |      | KP 7 | KP 8 | KP 9 | KP - |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | Wake   |      |      |      |      |      |------| |------|      | KP 4 | KP 5 | KP 6 | KP + |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      | |      |      | KP 1 | KP 2 | KP 3 |KP Ent|        |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                             | KP 0 |      | KP . |KP Ent|      |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      |      |      | |      |      |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      |      | |      |      |      |
 *                               |      |      |------| |------|      |      |
 *                               |      |      |      | |      |      |      |
 *                               `--------------------' `--------------------'
 */
[_KP] = KEYMAP(
        // left hand
        KC_PWR,  _______, _______, _______, _______, _______, _______,
        KC_SLEP, _______, _______, _______, _______, _______, _______,
        KC_WAKE, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
                                            _______, _______,
                                                     _______,
                                   _______, _______, _______,
        // right hand
        _______, _______, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
        _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
                 _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                          KC_P0,   _______, KC_PDOT, KC_PENT, _______,
        _______, _______,
        _______,
        _______, _______, _______
  ),

};

const uint16_t PROGMEM fn_actions[] = {
  // Layer switching
  //[1] = ACTION_LAYER_TAP_KEY(NAVIGATION_LAYER, KC_SCLN),

  //[2] = ACTION_LAYER_TAP_KEY(NAVIGATION_LAYER, KC_O),
  //[3] = ACTION_LAYER_TAP_KEY(GUI_LAYER, KC_LBRACKET),
  //[4] = ACTION_LAYER_TAP_KEY(GUI_LAYER, KC_RBRACKET),

  // Modifiers
  [5] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
  [6] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _QW:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_CM);
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
