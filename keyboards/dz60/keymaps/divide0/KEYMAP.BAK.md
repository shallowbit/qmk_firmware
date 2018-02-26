#include "dz60.h"
#include "action_layer.h"

// #if (__has_include("secret.h"))
// #include "secret.h"
// #else
// const char secret[][64] = {
//   "test1",
//   "test2",
//   "test3",
//   "test4",
//   "test5"
// };
// #endif

#define KEYMAP_REV "1.00 "

enum map_layers
{
  _QWER = 0,
  _COLE,
  _WORK,
  _DVOR,
  _FKEY, // RAISE?
  _PNTR, // LOWER?
  _LEDS, // ADJUST?
  _MDIA

};

enum map_keycodes
{
  //LAYER KEYS
  QWER = SAFE_RANGE
  COLE,
  WORK,
  DVOR,
  FKEY,
  PNTR,
  LEDS,
  MDIA,
  //SPECIAL KEYS & MACROS
  SPACE_R, // Right space
  SPACE_M, // Middle space
  SPACE_L, // Left space
  MAKE,
  VERS,
  TILSLSH,
  DEREF,
  EQRIGHT,
  EPRM
};

#define ______ KC_TRNS
#define _______ KC_TRNS
#define ________ KC_TRNS
#define XXXXXXX KC_NO

// ONESHOT F-Keys
// #define FKEY_LAYER _FKEYS
// #define OSL()

// #define KC_1F LT(_L1, KC_1)
// #define KC_2F LT(_L1, KC_2)
// #define KC_3F LT(_L1, KC_3)
// #define KC_4F LT(_L1, KC_4)
// #define KC_5F LT(_L1, KC_5)
// #define KC_6F LT(_L1, KC_6)
// #define KC_7F LT(_L1, KC_7)
// #define KC_8F LT(_L1, KC_8)
// #define KC_9F LT(_L1, KC_9)
// #define KC_10F LT(_L1, KC_0)
// #define KC_11F LT(_L1, KC_MINS) // These are different on Dvorak
// #define KC_12F LT(_L1, KC_EQL) // These are different on Dvorak


/*
 * template
 * [_L1] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
 *      ______,______,______,______,______,______,______,______,______,______,______,______,_________,    ______,
 *      _________,    ______,______,______,______,______,______,______,______,______,______,______,______,______,
 *      _________,    ______,______,______,______,______,______,______,______,______,______,______,_________,   ,
 *      _________,    ______,______,______,______,______,______,______,______,______,______,______,______,______,
 *      ______,_________,    ______,_________,    _________,    _________,    ______,______,______,______,______,
 *
 *    ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   _________,          ______,
 *    _________,          ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,
 *    _________,          ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,
 *    _________,          ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,
 *    ______,   ______,   _________,                    ______,   ______,   _________,                    ______,   ______,   ______,   ______,   ______
 *
 *      ,-----------------------------------------------------------------------------------------.
 *      |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
 *      |-----------------------------------------------------------------------------------------+
 *      |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
 *      |-----------------------------------------------------------------------------------------+
 *      |         |     |     |     |     |     |     |     |     |     |     |     |             |
 *      |-----------------------------------------------------------------------------------------+
 *      |           |     |     |     |     |     |     |     |     |     |     |     |     |     |
 *      |-----------------------------------------------------------------------------------------+
 *      |       |       |       |            |       |              |     |     |     |     |     |
 *      `----------------------------------------------------------------------------------------'
 *
 *      Colemak http://colemak.com
 *      Workman http://xahlee.info/kbd/dvorak_vs_colemak_vs_workman.html
 *      Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard


 Keymap _L2: (Layer 2) This is function layer 2
 This layer is activated while the Fn2 key is being held down.
 LCA(KC_TAB) = Hold Left Control and Alt and press kc_tab which cycles trough open apps.
 MEH(KC_TAB) = Hold Left Control, Shift and Alt and press kc_TAB to cycle backwards through apps.

 This layer has a key set to MO(_L1) which means when held down Layer 1 will become active, If Layer 1 does not h ave anything set for tat key is will revert to uing the key set at layer 0.
 LT(_L1, KC_1) means that when the "1" key is long touched then it will activate the layer _L1 key(F1) but if the key is just tapped it will activate the "1" key.
 KC_GESC = Escape when tapped, ` when pressed with Shift or GUI
 KC_LSPO = Left Shift when held, ( when tapped
 TD(TD_SPC_ENT) tap dance space and enter
 TD(LT(_L3,KC_SPACE)) = This is a test... hoping it will tap dance if double tapped it does enter if single tap it does space if long hold down it does _L3(Layer 3).
 LT(_L3,KC_SPACE) = if tapped it does space, is long touch it does _L3(Layer 3)

 */

// SHORTEN STUFF
#define TD_SPC TD(LT(_FKEY,SPACE_M))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  	[_QWER] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
  		KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
  		KC_TAB,               KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   KC_RALT,
  		KC_LCTL,              KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
  		KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     MO(_FKEY),
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         SPACE_L,   TD_SPC,    SPACE_R,                         MO(_LEDS) ,MO(_PNTR), KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    /*
     [_COLE] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      KC_TAB,               KC_Q,      KC_W,      KC_F,      KC_P,      KC_G,      KC_J,      KC_L,      KC_U,      KC_Y,      KC_SCLN,   KC_LBRC,   KC_RBRC,   KC_RALT,
      KC_LCTL,              KC_A,      KC_R,      KC_S,      KC_T,      KC_D,      KC_H,      KC_N,      KC_E,      KC_I,      KC_O,      KC_QUOT,   KC_ENT,
      KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_K,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     MO(_FN),
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPC,    RESET,     KC_SPC,                          MO(_RGB),  MO(_RST),  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    [_WORK] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      KC_TAB,               KC_Q,      KC_D,      KC_R,      KC_W,      KC_B,      KC_J,      KC_F,      KC_U,      KC_P,      KC_SCLN,   KC_LBRC,   KC_RBRC,   KC_RALT ,
      KC_LC TL,             KC_A,      KC_ S,     KC _H,     KC_T,      KC_G,      KC_Y,      KC_N,      KC_E,      KC_O,      KC_I,      KC_QUOT,   KC_ENT,
      KC_LSFT,              KC_Z,      KC_X,      KC_M,      KC_C,      KC_V,      KC_K,      KC_L,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     MO(_FN),
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPC,    RESET,     KC_SPC,                          MO(_RGB),  MO(_RST),  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    [_DVOR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_E SC,    KC_ 1,    KC_2 ,     KC _3,     K C_4,     KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_LBRC,   KC_RBRC,              KC_BSPC,
      KC_TAB,               KC_QUOT,   KC_COMM,   KC_DOT,    KC_P,      KC_Y,      KC_F,      KC_G,      KC_C,      KC_R,      KC_L,      KC_SLSH,   KC_EQL,    KC_RALT,
      KC_LCTL,              KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,      KC_MINS,   KC_ENT,
      KC_LSFT,              KC_SCLN,   KC_Q,      KC_J,      KC_K,      KC_X,      KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,      KC_BSLS,   KC_UP,     MO(_FN),
      KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPC,    RESET,     KC_SPC,                          MO(_RGB),  MO(_RST),  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    */
     [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      RESET,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_DEL,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_PGUP,   _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, KC_HOME,   KC_PGDN,   KC_END
    ),
    [_FKEY2] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      RESET,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_DEL,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_PGUP,   ______,
      _________, _________, _________,                       TD_L2_L3,  TD_L0_L1,  TD_L3_L4,                        _________, _________, KC_HOME,   KC_PGDN,   KC_END
    ),
  	[_MDIA] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_MUTE,   KC_WSCH,   KC_MAIL,   KC_CALC,   KC_MYCM ,  KC_WREF,   KC_WSTP,   _________, _________, _________, _________, KC_SLEP,   KC_WAKE,              KC_MSTP,
  		_________,            _________, _________, _________, KC_WREF,   _________, _________, _________, _________, _________, _________, _________, _________, _________,
  		_________,            KC_WBAK,   _________, _________, _________, KC_WFWD,   KC_WBAK,   _________, _________, KC_WFWD,   _________, _________,            KC_MPLY,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_WFAV,   _________, KC_VOLU,   _________,
  		_________, _________, _________,                       _________, _________, _________,                       _________, _________, KC_MPRV,   KC_VOLD,   KC_MNXT
    ),
  	[_LEDS] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		RGB_TOG,   RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_S W, RGB_M_SN,  RGB_M_K,   RGB_M_X,   RGB_M_G,   _________, _________, _________, _________,            _________,
  		RGB_MOD,              RGB_HUI,   RGB_SAI,   RGB_VAI,   _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
  		_________,            RGB_HUD,   RGB_SAD,   RGB_VAD,   _________, _________, _________, _________, _________, _________, _________, _________, _________,
  		_________,            _________, _________, BL_DEC,    BL_TOGG,   BL_INC,    _________, _________, _________, _________, _________, _________, _________, _________,
  		_________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ),
    [_PNTR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		_________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,            _________,
  		_________,            KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   _________, _________, _________, _________, _________, _________, _________, _________, _________,
  		_________,            KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   KC_ACL0,   KC_ACL2,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_BTN1,   KC_MS_U,   KC_BTN2,
  		_________, _________, _________,                       KC_BTN1,   _________, KC_BTN2,                         KC_WH_D,   KC_WH_U,   KC_MS_L,   KC_MS_D,   KC_MS_R
    )

  };

//Tap Dance Declarations
enum {
  TD_L0_L1 = 0,
  TD_L2_L3,
  TD_L4_L5
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {

  //1) Right Shift 2) Caps Lock
  [TD_L0_L1]  = ACTION_TAP_DANCE_DOUBLE(QWER, FKEY)
  //Tap once for space, tap twice for enter
  [TD_L1_L2]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
  //1) Left Shift 2) Caps Lock
  [TD_L3_L4]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  //1) Home 2) End
  [TD_HOME_END]  = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) { // KEY IS DOWN
    switch(keycode) {
      // LAYER SWITCHING
      case QWER: {
        persistent_default_layer_set(1UL<<_QWER);
        return false;
      }
      case COLE: {
        persistent_default_layer_set(1UL<<_COLE);
        return false;
      }
      case WORK: {
        persistent_default_layer_set(1UL<<_WORK);
        return false;
      }
      case DVOR: {
        persistent_default_layer_set(1UL<<_DVOR);
        return false;
      }
      // EVERTYIHNG ELSE
      case VERS: {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP ":v" KEYMAP_REV);
        return false;
      }
      case SPACE_L: {
        SEND_STRING (" ");
        return false;
      }
      case SPACE_M: {
        SEND_STRING (" ");
        return false;
      }
      case SPACE_R: {
        SEND_STRING (" ");
        return false;
      }
      case MAKE: {
        SEND_STRING ("make " QMK_KEYBOARD ":" QMK_KEYMAP);
        return false;
      }
      case TILSLSH: {
        SEND_STRING ("~/.");
        return false;
      }
      case DEREF: {
        SEND_STRING (z"->");
        return false;;
      }
      case EQRIGHT: {
        SEND_STRING ("=>");
        return false;
      }
      case EPRM: {
        eeconfig_init();
        return false;
      }
      case LOWER: {
        layer_on(_LOWER);
        #ifdef BACKLIGHT_ENABLE
            breathing_period_set(2);
            breathing_pulse();
        #endif
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      }
      case RAISE: {
        layer_on(_RAISE);
        #ifdef BACKLIGHT_ENABLE
            breathing_period_set(2);
            breathing_pulse();
        #endif
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      }
    }
  } else { // KEY IS UP
    switch(keycode) {
      case LOWER: {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      }
      case RAISE: {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      }
    }
  }
  return true;
};

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
          rgblight_init();
        #endif
        break;
      case 1:
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
         #endif
        break;
      case 3:
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

    return state;
};
