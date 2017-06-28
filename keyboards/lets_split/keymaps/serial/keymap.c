#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_plover.h"
#include "action_tapping.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define NAVIGATION_LAYER 5
#define GUI_LAYER 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define ___x___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer (Qwerty)
 *                ,-----------------------------------------------------------------------.
 *                | `   | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   |Bksp |
 *                |-----------------------------------------------------------------------|
 * Tap for Esc -- |Ctrl | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   |Ctrl | -- Tap for Enter
 *                |-----------------------------------------------------------------------|
 *   Tap for ( -- |Shift| Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |Shift| -- Tap for )
 *                |-----------------------------------------------------------------------|
 *   Tap for [ -- |Hyper|     |     | Alt |Lower| Cmd |Space|Raise| Alt |     |     |Hyper| -- Tap for ]
 *                `-----------------------------------------------------------------------'
 *                        /                                                     /
 *   Tap for { } --------'-----------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_GRV,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC, \
  F(5),    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, F(6),    \
  KC_LSPO, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, \
  ALL_T(KC_ESC),  _______, _______, KC_LALT, LOWER,   KC_LGUI, KC_SPC, RAISE,    KC_RALT, _______, _______, ALL_T(KC_ESC)\
),



/* SYMBOL_LAYER(Lower)
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |      |      |   -  |   =  |  [   |   ]  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   %  |   ^  |   &  |   *  |      | Left | Down |  Up  |Right |   :  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   (  |   )  |      |      |      |      |  '   |  <   |  >   |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  Tab |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  _______, _______, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_P, \
  _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, S(KC_SCLN), _______, \
  _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, KC_QUOT, S(KC_COMM), S(KC_DOT), KC_BSLS, _______, \
  _______, _______, _______, _______, _______, _______,  KC_TAB, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |      |      |  _   |   +  |  [   |  ]   | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   5  |   6  |   7  |   8  |      |Left  |Down  |  Up  |Right |  :   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   9  |   0  |      |      |      |      |  "   |      |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    _______, _______, KC_UNDS, KC_PPLS, KC_LBRC, KC_RBRC, KC_P, \
  _______, KC_5,    KC_6,    KC_7,    KC_8,    _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, S(KC_SCLN), _______, \
  _______, KC_9,    KC_0,    _______, _______, _______, _______, S(KC_QUOT), _______, _______, KC_BSLS, _______, \
  _______, _______, _______, _______, _______, _______, KC_TAB,  _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* NAVIGATION_LAYER
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Home  |PgUp  |PgDn  |End   |Left  |Down  |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[NAVIGATION_LAYER] =  KEYMAP( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* GUI (window management/mouse/media controls) layer
 *
 *        Mouse keys -----/```````````````````\               /```````````````````\----- Window manager
 *                ,-----------------------------------------------------------------------.
 *                |     |Ms B2|Ms Up|Ms B1|Ms WD|     |     |Prev | TL  | Top | TR  |     |
 *                |-----------------------------------------------------------------------|
 *                |     |Ms L |Ms Dn|Ms R |Ms WU|     |     |Full |Left |Centr|Right|     |
 *                |-----------------------------------------------------------------------|
 *                |     |Ms WL|Ms B3|Ms WR|     |     |     |Next | BL  | Bot | BR  |     |
 *                |-----------------------------------------------------------------------|
 *                |     |Prev |Play |Next |Brig-|   Sleep   |Brig+|Mute |Vol- |Vol+ |     |
 *                `-----------------------------------------------------------------------'
 *                        \___ Media ___/   \___ Screen/sleep __/   \___ Volume __/
 */
[GUI_LAYER] = KEYMAP( \
  _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, XXXXXXX, XXXXXXX, LCTL(LALT(LGUI(KC_LEFT))), LCTL(LGUI(KC_LEFT)),    LALT(LGUI(KC_UP)),   LCTL(LGUI(KC_RGHT)),    _______, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, XXXXXXX, XXXXXXX, LALT(LGUI(KC_F)),          LALT(LGUI(KC_LEFT)),    LALT(LGUI(KC_C)),    LALT(LGUI(KC_RGHT)),    _______, \
  _______, KC_WH_L, KC_BTN3, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, LCTL(LALT(LGUI(KC_RGHT))), S(LCTL(LGUI(KC_LEFT))), LALT(LGUI(KC_DOWN)), S(LCTL(LGUI(KC_RGHT))), _______, \
  _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_SLCK, KC_SLEP, KC_SLEP, KC_PAUS,                   KC_MUTE,                KC_VOLD,             KC_VOLU,                _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, \
  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)
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

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
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
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
