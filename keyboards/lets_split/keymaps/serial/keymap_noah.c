#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"
#include "keymap_plover.h"
#include "action_tapping.h"

extern keymap_config_t keymap_config;

// Keymap layers
#define BASE_QWERTY_LAYER 0
#define BASE_COLEMAK_LAYER 1
#define BASE_STENO_LAYER 2
#define LOWER_LAYER 3
#define RAISE_LAYER 4
#define NAVIGATION_LAYER 5
#define GUI_LAYER 6
#define KEYBOARD_LAYER 7

// Key aliases for legibility
#define _______ KC_TRNS
#define ___x___ KC_NO

// Macros
#define LALT_BRACE 0
#define RALT_BRACE 1

// Special key codes
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  STENO,
  LOWER,
  RAISE,
  PV_EXIT,
  PV_LOOK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer (Qwerty)
   *                ,-----------------------------------------------------------------------.
   *                | Tab | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | '   |
   *                |-----------------------------------------------------------------------|
   * Tap for Esc -- |Ctrl | A   | S   | D   | F   | G   | H   | J   | K   | L   |; Fn4|Ctrl | -- Tap for Enter
   *                |-----------------------------------------------------------------------|
   *   Tap for ( -- |Shift| Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |Shift| -- Tap for )
   *                |-----------------------------------------------------------------------|
   *   Tap for [ -- | Fn3 |Hyper| Alt |Super| Fn1 |   Space   | Fn2 |Super| Alt |Hyper| Fn3 | -- Tap for ]
   *                `-----------------------------------------------------------------------'
   *                        /                                                     /
   *   Tap for { } --------'-----------------------------------------------------'
   */
  [BASE_QWERTY_LAYER] = {
    {KC_TAB,  KC_Q,           KC_W,          KC_E,    KC_R,  KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,          KC_P,           KC_QUOT},
    {F(5),    KC_A,           KC_S,          KC_D,    KC_F,  KC_G,   KC_H,    KC_J,  KC_K,    KC_L,          F(1),           F(6)},
    {KC_LSPO, KC_Z,           KC_X,          KC_C,    KC_V,  KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,        KC_SLSH,        KC_RSPC},
    {F(3),    ALL_T(KC_LBRC), M(LALT_BRACE), KC_LGUI, LOWER, KC_SPC, KC_BSPC, RAISE, KC_RGUI, M(RALT_BRACE), ALL_T(KC_RBRC), F(4)}
  },

  /* Numeric layer
   *                ,-----------------------------------------------------------------------.
   * Application -- |D-Grv| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | #   |
   *      window    |-----------------------------------------------------------------------|
   *    switcher    |     | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   |     |
   *                |-----------------------------------------------------------------------|
   *                |     | -   | =   | `   | \   | a   | b   | c   | d   | e   | f   |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     | Backspace |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [LOWER_LAYER] = {
    {LGUI(KC_GRV), KC_F1,          KC_F2,         KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7, KC_F8,   KC_F9,         KC_F10,         S(KC_3)},
    {F(5),         KC_1,           KC_2,          KC_3,    KC_4,    KC_5,    KC_6,    KC_7,  KC_8,    KC_9,          KC_0,           F(6)},
    {KC_LSPO,      KC_MINS,        KC_EQL,        KC_GRV,  KC_BSLS, KC_A,    KC_B,    KC_C,  KC_D,    KC_E,          KC_F,           KC_RSPC},
    {F(3),         ALL_T(KC_LBRC), M(LALT_BRACE), KC_LGUI, LOWER,   KC_BSPC, KC_BSPC, RAISE, KC_RGUI, M(RALT_BRACE), ALL_T(KC_RBRC), F(4)}
  },

  /* Symbol layer
   *                ,-----------------------------------------------------------------------.
   *                |     | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 | #   |
   *                |-----------------------------------------------------------------------|
   *                |     | !   | @   | #   | $   | %   | ^   | &   | *   | '   | "   |     | \
   *                |-----------------------------------------------------------------------|  |-- Mostly shifted version
   *                |     | _   | +   | ~   | |   |     |ndash|mdash|     |     |     |     | /    of lower layer
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |  Delete   |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [RAISE_LAYER] = {
    {_______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,        KC_F17,           KC_F18,  KC_F19,  KC_F20,     S(KC_3)},
    {_______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6),       S(KC_7),          S(KC_8), KC_QUOT, S(KC_QUOT), _______},
    {_______, KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE, ___x___, LALT(KC_MINS), S(LALT(KC_MINS)), ___x___, ___x___, ___x___,    _______},
    {_______, _______, _______, _______, _______, KC_DEL,  KC_DEL,        _______,          _______, _______, _______,    _______}
  },

  /* Directional navigation layer
   *
   *         Large movements -----/```````````````````\   /```````````````````\----- Vim-style arrow keys
   *                ,-----------------------------------------------------------------------.
   *                |     |     |     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |Home |PgUp |PgDn | End |Left |Down | Up  |Right|     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |           |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [NAVIGATION_LAYER] = {
    {___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___},
    {_______, ___x___, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, F(1),    _______},
    {_______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, _______},
    {_______, _______, _______, _______, ___x___, ___x___, ___x___, ___x___, _______, _______, _______, _______}
  },

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
  [GUI_LAYER] = {
    {_______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, ___x___, ___x___, LCTL(LALT(LGUI(KC_LEFT))), LCTL(LGUI(KC_LEFT)),    LALT(LGUI(KC_UP)),   LCTL(LGUI(KC_RGHT)),    _______},
    {_______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, ___x___, ___x___, LALT(LGUI(KC_F)),          LALT(LGUI(KC_LEFT)),    LALT(LGUI(KC_C)),    LALT(LGUI(KC_RGHT)),    _______},
    {_______, KC_WH_L, KC_BTN3, KC_WH_R, ___x___, ___x___, ___x___, LCTL(LALT(LGUI(KC_RGHT))), S(LCTL(LGUI(KC_LEFT))), LALT(LGUI(KC_DOWN)), S(LCTL(LGUI(KC_RGHT))), _______},
    {_______, KC_MPRV, KC_MPLY, KC_MNXT, KC_SLCK, KC_SLEP, KC_SLEP, KC_PAUS,                   KC_MUTE,                KC_VOLD,             KC_VOLU,                _______}
  },

  /* Keyboard settings layer
   *                ,-----------------------------------------------------------------------.
   *    Firmware -- |     |Reset|     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *   Set layer -- |     |Qwert|Colem|Steno| ... |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *       Audio -- |     |Voic-|Voic+|Mus +|Mus -|MIDI+|MIDI-|     |     |Aud +|Aud -|     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |  Toggle   |     |Toggl| BL- | BL+ |     |
   *                `-----------------------------------------------------------------------'
   *                                                    \_____________\_ Backlight _/
   */
  [KEYBOARD_LAYER] = {
    {___x___, RESET,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___},
    {___x___, QWERTY,  COLEMAK, STENO,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___},
    {___x___, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  ___x___, ___x___, AU_ON,   AU_OFF,  ___x___},
    {___x___, ___x___, ___x___, ___x___, LOWER,   BL_TOGG, BL_TOGG, RAISE,   BL_TOGG, BL_DEC,  BL_INC,  ___x___}
  }
};

const uint16_t PROGMEM fn_actions[] = {
  // Layer switching
  [1] = ACTION_LAYER_TAP_KEY(NAVIGATION_LAYER, KC_SCOLON),
  [2] = ACTION_LAYER_TAP_KEY(NAVIGATION_LAYER, KC_O),
  [3] = ACTION_LAYER_TAP_KEY(GUI_LAYER, KC_LBRACKET),
  [4] = ACTION_LAYER_TAP_KEY(GUI_LAYER, KC_RBRACKET),

  // Modifiers
  [5] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
  [6] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case LALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_LALT);
        record->tap.interrupted = 0;
      } else {
        unregister_mods(MOD_LALT);

        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
    case RALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_RALT);
        record->tap.interrupted = 0;
      } else {
        unregister_mods(MOD_RALT);

        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
  }
  return MACRO_NONE;
}

#ifdef AUDIO_ENABLE

float tone_startup[][2]   = SONG(STARTUP_SOUND);
float tone_qwerty[][2]    = SONG(QWERTY_SOUND);
float tone_colemak[][2]   = SONG(COLEMAK_SOUND);
float tone_plover[][2]    = SONG(PLOVER_SOUND);
float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]    = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]   = SONG(GOODBYE_SOUND);

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
        persistant_default_layer_set(1UL<<BASE_QWERTY_LAYER);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_colemak, false, 0);
#endif
        persistant_default_layer_set(1UL<<BASE_COLEMAK_LAYER);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(LOWER_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      } else {
        layer_off(LOWER_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(RAISE_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      } else {
        layer_off(RAISE_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      }
      return false;
    case STENO:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_NOTE_ARRAY(tone_plover, false, 0);
#endif
        layer_off(RAISE_LAYER);
        layer_off(LOWER_LAYER);
        layer_off(KEYBOARD_LAYER);
        layer_on(BASE_STENO_LAYER);
        if (!eeconfig_is_enabled()) {
          eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
        plover_resume();
      }
      return false;
    case PV_EXIT:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
#endif
        plover_suspend();
        layer_off(BASE_STENO_LAYER);
      }
      return false;
    case PV_LOOK:
      if (record->event.pressed) {
        plover_lookup();
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
  startup_user();
#endif
}

// Send PHROPB ({PLOVER:RESUME}).
void plover_resume() {
  register_code(PV_LP);
  register_code(PV_LH);
  register_code(PV_LR);
  register_code(PV_O);
  register_code(PV_RP);
  register_code(PV_RB);
  unregister_code(PV_LP);
  unregister_code(PV_LH);
  unregister_code(PV_LR);
  unregister_code(PV_O);
  unregister_code(PV_RP);
  unregister_code(PV_RB);
}

// Send PHROF ({PLOVER:SUSPEND}).
void plover_suspend() {
  register_code(PV_LP);
  register_code(PV_LH);
  register_code(PV_LR);
  register_code(PV_O);
  register_code(PV_RF);
  unregister_code(PV_LP);
  unregister_code(PV_LH);
  unregister_code(PV_LR);
  unregister_code(PV_O);
  unregister_code(PV_RF);
}

// Send PHROBG ({PLOVER:LOOKUP}).
void plover_lookup() {
  register_code(PV_LP);
  register_code(PV_LH);
  register_code(PV_LR);
  register_code(PV_O);
  register_code(PV_RB);
  register_code(PV_RG);
  unregister_code(PV_LP);
  unregister_code(PV_LH);
  unregister_code(PV_LR);
  unregister_code(PV_O);
  unregister_code(PV_RB);
  unregister_code(PV_RG);
}

#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20); // gets rid of tick
  PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
  PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
