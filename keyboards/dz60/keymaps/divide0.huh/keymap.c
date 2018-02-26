#include "dz60.h"
#include "action_layer.h"
//#include "dynamic_macro.h"
#include "mousekey.h"
#include "version.h"
#include "eeconfig.h"

#define KEYMAP_REV "1.01"
/*
NOTES:

  add ctl+directions/alt+directions/top/bottom/word-del-forward/ to left hand on _FKEYS instead of mouse movement?
  actually overlay not clear arrow cluster for temp mouse/pgup.dn/next.prev\top.bottom for sigle FN press cluster switching
    FN(1 tap) for hoome/end 2 taps back/forw 3 taps top/bottom? hold to clear?

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
     *      Colemak http://colemak.com
     *      Workman http://xahlee.info/kbd/dvorak_vs_colemak_vs_workman.html
     *      Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard

*/

enum map_layers {
  _QWER = 0,
  _COLE = 1,  // 1
  _WORK = 2,  // 2
  _DVOR = 3,  // 3
  _FKEY = 11, // 11 RAISE?
  _PNTR = 12, // 12 LOWER?
  _LEDS = 13, // 13 ADJUST?
  _SYMB = 14, // 14
  _MDIA = 15, // 15
  _MACR = 16  // 16
  // _TMUX
  // _VIM
  // _META,HYPER
  // _WINDOWS
  // _LINUX
};

enum map_keycodes {
  //LAYER KEYS
  QWER = SAFE_RANGE,
  COLE,
  WORK,
  DVOR,
  FKEY,
  PNTR,
  LEDS,
  SYMB,
  MDIA,
  MACR,
  BASE, // CLEAR ALL LAYERS
  //SPECIAL KEYS & MACROS
  //SPACE_R, // Right space
  SPACE_M, // Middle space
  //SPACE_L, // Left space
  A_MUL,   // Mouse Upper left diagonal
  A_MUR,   // Mouse Upper right diagonal
  A_MDL,   // Mouse Lower left diagonal
  A_MDR,   // Mouse Lower right diagonal
  MAKE,
  VERS,
  TILSLSH,
  DEREF,
  EQRIGHT,
  EPRM,
  //DYNAMIC_MACRO_RANGE // Must be last
};

enum map_dances {
  TD_L10 = 0,
  TD_L23,
  TD_L45,
  TD_Q_R,
  TD_TEST
};

//TAPDANCE CALLS
// #define TD_10 TD(TD_L10) // TODO change this for layer 0 only?
// #define TD_L23 TD(TD_L23)
// #define TD_L45 TD(TD_L45)

// SHORTEN STUFF
#define _________ KC_TRNS
#define ________ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Edits x,c,v,z
#define CUT     KC_CUT // KC_CUT??
#define COPY    KC_COPY
#define PAST    KC_PASTE
#define UNDO    KC_UNDO // #define UNDO    RCTL(KC_Z)
#define REDO    KC_AGAIN // #define REDO    RCTL(RSFT(KC_Z))
// Double Modifier ONLY hold
#define ALT_SHFT LSFT(KC_LALT)
#define CTR_SHFT LSFT(KC_LCTL)
// Navigation
#define TOP     RCTL(KC_PGUP)
#define BOT     RCTL(KC_PGDN)
#define WINL    LGUI(KC_LEFT)
#define WINR    LGUI(KC_RIGHT)
#define WINUP   LGUI(KC_UP)
#define WINDN   LGUI(KC_DOWN)
#define ALEFT   RALT(KC_LEFT)
#define ARIGHT  RALT(KC_RIGHT)
#define CLEFT   RCTL(KC_LEFT)
#define CRIGHT  RCTL(KC_RIGHT)
#define PTAB    LCTL(LSFT(KC_TAB))
#define NTAB    LCTL(KC_TAB)
#define VDRIGHT LCTL(LGUI(KC_RIGHT))
#define VDLEFT  LCTL(LGUI(KC_LEFT))
//MISC
#define PSCR  KC_PSCREEN
#define CAD   LCTL(LALT(KC_DEL))
#define TASK  LCTL(LSFT(KC_ESC))
//MACRO REC
// #define REC1 DYN_REC_START1
// #define REC2 DYN_REC_START2
// #define PLAY1 DYN_MACRO_PLAY1
// #define PLAY2 DYN_MACRO_PLAY2
// #define RECSTOP DYN_REC_STOP
//RGB EXTRAS
#ifdef RGBLIGHT_ENABLE
  const uint16_t RGBLED_GRADIENT_RANGES[] PROGMEM = {360, 240, 180, 120, 90}; // These control which colors are selected for the gradient mode
  const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};       // How long (in ms) to wait between animation steps for the breathing mode
  const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};      // How long (in ms) to wait between animation steps for the rainbow mode
  const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};     // How long (in ms) to wait between animation steps for the swirl mode
  const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};             // How long (in ms) to wait between animation steps for the snake mode
  const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {127, 63, 31};            // How long (in ms) to wait between animation steps for the knight modes
#endif
//SPECIAL
//SHORTEN SOME FUNCTION CALLS

#define FKEY_ESC LT(MO(_FKEY),KC_ESC)         // fkey(HELD)          esc(TAPPED)
//#define FKEY_CTL LT(MO(_FKEY),OSM(KC_LCTL)) // fkey(HELD)          control(TAPPED)
#define FKEY_HME LT(MO(_FKEY),KC_HOME) // WORKS fkeys(HELD)    home(TAPPED)
#define PNTR_END LT(MO(_PNTR),KC_END)  // WORKS pntr(HELD)    end(TAPPED)
#define SHFT_BLS RSFT_T(KC_BSLS)       // WORKS shfit(HELD)   bslash(TAPPED) .. hopefully this will be shifted to pipe as well
#define CTL_ESC  LCTL_T(KC_ESC)        // WORKS control(HELD) esc(TAPPED)
#define LEDS_TAB LT(_LEDS,KC_TAB)      // WORKS leds(HELD)    tab(TAPPED) .. eventually use quad tap func .. ALSO, ctrl+tab is kinda screwy with both being doubdle taps
//#define INS_FKEY = LT(_FKEY,_K)      // insert(HELD)  ???(TAPPED)
//#define ENTER = SFT_T(KC_ENT)
//#define _HCSESC C_S_T(KC_ESC) // HELD(LCTRL+SHFT) TAPPED(ESC)

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //                      A          S          D          F          G          H          J          K          L          :          '          ENTER
  	[_QWER] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
  		KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
  		LEDS_TAB,             KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   RESET,
  		FKEY_ESC,             KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
  		KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   SHFT_BLS,  KC_UP,     BASE,
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPACE,  TD(TD_TEST),KC_SPACE,                       FKEY_HME,  PNTR_END,  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    /*
    [_QWER] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
  		KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
  		KC_TAB,               KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   RESET,
  		KC_LCTL,              KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
  		LSFT_T(FKEYS)         KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     SYMB,
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         SPACE_L,   TD_L10,    SPACE_R,                         FKEY,      PNTR,      KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),


     [_COLE] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      KC_TAB,               KC_Q,      KC_W,      KC_F,      KC_P,      KC_G,      KC_J,      KC_L,      KC_U,      KC_Y,      KC_SCLN,   KC_LBRC,   KC_RBRC,   RESET,
      KC_LCTL,              KC_A,      KC_R,      KC_S,      KC_T,      KC_D,      KC_H,      KC_N,      KC_E,      KC_I,      KC_O,      KC_QUOT,   KC_ENT,
      KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_K,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     MO(_FN),
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         TD_L23,    TD_L10,    TD_L45,                          MO(_RGB),  MO(_RST),  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    [_WORK] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      KC_TAB,               KC_Q,      KC_D,      KC_R,      KC_W,      KC_B,      KC_J,      KC_F,      KC_U,      KC_P,      KC_SCLN,   KC_LBRC,   KC_RBRC,   RESET,
      KC_LC TL,             KC_A,      KC_ S,     KC _H,     KC_T,      KC_G,      KC_Y,      KC_N,      KC_E,      KC_O,      KC_I,      KC_QUOT,   KC_ENT,
      KC_LSFT,              KC_Z,      KC_X,      KC_M,      KC_C,      KC_V,      KC_K,      KC_L,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     MO(_FN),
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         TD_L23,    TD_L10,    TD_L45,                          MO(_RGB),  MO(_RST),  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    [_DVOR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_ 1,     KC_2 ,     KC _3,     K C_4,     KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_LBRC,   KC_RBRC,              KC_BSPC,
      KC_TAB,               KC_QUOT,   KC_COMM,   KC_DOT,    KC_P,      KC_Y,      KC_F,      KC_G,      KC_C,      KC_R,      KC_L,      KC_SLSH,   KC_EQL,    RESET,
      KC_LCTL,              KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,      KC_MINS,   KC_ENT,
      KC_LSFT,              KC_SCLN,   KC_Q,      KC_J,      KC_K,      KC_X,      KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,      KC_BSLS,   KC_UP,     MO(_FN),
      KC_LCTL,   KC_LGUI,   KC_LALT,                         TD_L23,    TD_L10,    TD_L45,                          MO(_RGB),  MO(_RST),  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_GESC,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_BSPC,
      _________,            KC_WH_U,   KC_HOME,   KC_PGUP,   KC_END,    _________, _________, KC_HOME,   KC_PGUP,   KC_END,    KC_WH_U,   _________, _________, RESET,
      _________,            KC_WH_D,   KC_LEFT,   KC_UP,     KC_DOWN,   KC_RIGHT,  KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  KC_WH_D,   _________, KC_ENT,
      _________,            _________, KC_DEL,    KC_PGDN,   KC_INS,    KC_BTN1,   KC_BTN2,   KC_INS,    KC_PGDN,   KC_DEL,    _________, _________, KC_PGUP,   _________,
      _________, _________, _________,                       TD_L23,    TD_L10,    QWER,                            KC_SPACE,  _________, KC_HOME,   KC_PGDN,   KC_END
    ),
    */
    [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_GESC,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_DEL,
      _________,            KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   _________, COPY,      KC_HOME,   KC_PGUP,   KC_END,    KC_WH_U,   PAST,      _________, TD(TD_Q_R),
      _________,            KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  KC_WH_D,   UNDO,      KC_ENT,
      _________,            UNDO,      CUT,       COPY,      PAST,      KC_BTN1,   KC_BTN2,   KC_INS,    KC_PGDN,   KC_DEL,    VERS,      _________, KC_PGUP,   _________,
      _________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            TOP,       BOT,       KC_HOME,   KC_PGDN,   KC_END
    ),
    [_PNTR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   KC_BTN1,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________, _________, _________, KC_ACL0,   KC_ACL1,   KC_ACL2,              _________,
  		_________,            KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   _________, _________, _________, _________, _________, _________, _________, _________, RESET,
  		_________,            KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   KC_ACL0,   KC_ACL2,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_BTN1,   KC_MS_U,   KC_BTN2,
  		_________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, KC_MS_L,   KC_MS_D,   KC_MS_R
    ),
  	[_LEDS] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,  RGB_M_SN,  RGB_M_K,   RGB_M_X,   RGB_M_G,   _________, _________, RGB_RMOD,  RGB_MOD,              RGB_TOG,
  		_________,            RGB_HUI,   RGB_SAI,   RGB_VAI,   _________, _________, _________, QWER,      COLE,      WORK,      DVOR,      _________, _________, RESET,
  		_________,            RGB_HUD,   RGB_SAD,   RGB_VAD,   _________, _________, _________, FKEY,      PNTR,      LEDS,      MDIA,      MACR,      _________,
      _________,            _________, _________, BL_DEC,    BL_TOGG,   BL_INC,    _________, SYMB,      _________, _________, _________, _________, _________, _________,
  		_________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, _________, _________, _________
    ),
  	[_MDIA] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   KC_WSCH,   KC_MAIL,   KC_CALC,   KC_MYCM ,  KC_WREF,   KC_WSTP,   _________, _________, _________, _________, KC_SLEP,   KC_WAKE,              KC_MSTP,
  		_________,            _________, _________, _________, KC_WREF,   _________, _________, _________, _________, _________, _________, _________, _________, RESET,
  		_________,            KC_WBAK,   _________, _________, _________, KC_WFWD,   KC_WBAK,   _________, _________, KC_WFWD,   _________, _________, KC_MPLY,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_WFAV,   _________, KC_VOLU,   _________,
  		_________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, KC_MPRV,   KC_VOLD,   KC_MNXT
    ),
    [_SYMB] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,            _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ),
    [_MACR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,            _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ) /*
    [_MACR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      RECSTOP,              PLAY1,     PLAY2,     _________, _________, _________, _________, _________, _________, _________, REC1,      REC2,                 _________,
      _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, _________, _________, _________
    ) */
  };

//Tap Dance   Definitions
  // tap once to turn on FKEYS layer.
  // Makes it easy to get to other layers. with one tap and one/two spaces
  // These KC layer are also MACROS so the toggles should also flash an LED indication as well
qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_L10] = ACTION_TAP_DANCE_DOUBLE(FKEY, QWER),
   [TD_L23] = ACTION_TAP_DANCE_DOUBLE(PNTR, LEDS),
   [TD_L45] = ACTION_TAP_DANCE_DOUBLE(SYMB, MACR),
   [TD_Q_R] = ACTION_TAP_DANCE_DOUBLE(QWER, RESET),
   [TD_TEST] = ACTION_TAP_DANCE_DOUBLE(TO(_QWER),TO(_LEDS)),
  };

void layer_on_override(uint16_t keycode) {
  //dprintf("d  trying switch: %d\n", keycode);
  layer_on(keycode);
  #ifdef BACKLIGHT_BREATHING
      breathing_period_set(2);
      breathing_pulse();
  #endif
};
// Macros and such
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // if (!process_record_dynamic_macro(keycode, record)) {
  //       return false;
  // }
  // TO stop recording macro by using MO(LAYER) after starting a rec
  // uint16_t macro_kc = (keycode == MO(_MACR) ? DYN_REC_STOP : keycode);
  // if (!process_record_dynamic_macro(macro_kc, record)) {
  //   return false;
  // }

  if (record->event.pressed) { // KEY IS DOWN
    switch(keycode) {

      // LAYER SWITCHING
      case BASE:
        layer_clear();

        dprintf("d  going to base\n");
        printf("  going to base\n");
        return false;

      case QWER:
        layer_clear();

        dprintf("trying switch QWER: %d\n", keycode);
        persistent_default_layer_set(1UL<<_QWER);
        return false;
      /*
      case COLE:
        layer_clear();
        persistent_default_layer_set(1UL<<_COLE);
        return false;

      case WORK:
        layer_clear();
        persistent_default_layer_set(1UL<<_WORK);
        return false;

      case DVOR:
        layer_clear();
        persistent_default_layer_set(1UL<<_DVOR);
        return false;
      */
      case FKEY:
        layer_on(_FKEY);

        dprintf("trying switch FKEY: %d\n", keycode);
        #ifdef BACKLIGHT_BREATHING
            breathing_period_set(2);
            breathing_pulse();
        #endif
        return false;

      case PNTR:
        //layer_on_override(_PNTR);
        layer_on(_PNTR);
        #ifdef BACKLIGHT_BREATHING
            breathing_period_set(2);
            breathing_pulse();
        #endif
        return false;

      case LEDS:
        layer_on(_LEDS);
        #ifdef BACKLIGHT_BREATHING
            breathing_period_set(2);
            breathing_pulse();
        #endif
        return false;

      case SYMB:
        layer_on(_SYMB);
        #ifdef BACKLIGHT_BREATHING
            breathing_period_set(2);
            breathing_pulse();
        #endif
        return false;

      case MACR:
        layer_on(_MACR);
        #ifdef BACKLIGHT_BREATHING
            breathing_period_set(2);
            breathing_pulse();
        #endif
        return false;

      case MDIA:
        layer_on(_MDIA);
        #ifdef BACKLIGHT_BREATHING
            breathing_period_set(2);
            breathing_pulse();
        #endif
        return false;

      // MOUSE MOVEMENTS
      #ifdef MOUSEKEY_ENABLE
      case A_MUL:
        mousekey_on(KC_MS_UP);
        mousekey_on(KC_MS_LEFT);
        mousekey_send();
        return false;

      case A_MUR:
        mousekey_on(KC_MS_UP);
        mousekey_on(KC_MS_RIGHT);
        mousekey_send();
        return false;

      case A_MDL:
        mousekey_on(KC_MS_DOWN);
        mousekey_on(KC_MS_LEFT);
        mousekey_send();
        return false;

      case A_MDR:
        mousekey_on(KC_MS_DOWN);
        mousekey_on(KC_MS_RIGHT);
        mousekey_send();
        return false;
      #endif
      // EVERTYIHNG ELSE
      case SPACE_M:
        SEND_STRING (" ");
        return false;

      case VERS:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP ":v" KEYMAP_REV);
        return false;

      case MAKE:
        SEND_STRING ("make " QMK_KEYBOARD ":" QMK_KEYMAP);
        return false;

      case TILSLSH:
        SEND_STRING ("~/.");
        return false;

      case DEREF:
        SEND_STRING ("->");
        return false;

      case EQRIGHT:
        SEND_STRING ("=>");
        return false;

      case EPRM:
        eeconfig_init();
        return false;

    }
  } else { // KEY IS UP (!event.pressed)
    switch(keycode) {
      #ifdef MOUSEKEY_ENABLE
      case A_MUL:
        mousekey_off(KC_MS_UP);
        mousekey_off(KC_MS_LEFT);
        mousekey_send();
        return false;

      case A_MUR:
        mousekey_off(KC_MS_UP);
        mousekey_off(KC_MS_RIGHT);
        mousekey_send();
        return false;

      case A_MDL:
        mousekey_off(KC_MS_DOWN);
        mousekey_off(KC_MS_LEFT);
        mousekey_send();
        return false;

      case A_MDR:
        mousekey_off(KC_MS_DOWN);
        mousekey_off(KC_MS_RIGHT);
        mousekey_send();
        return false;
      #endif

      // DONT KNOW IF I NEED THESE TO SWITCH BUT NOT TOGGLE LAYERS
      // case LOWER:
      //   layer_off(_LOWER);
      //   return false;
      //
      // case RAISE:
      //   layer_off(_RAISE);
      //   return false;
      //
    }
  }
  return true;
};

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case 0:
      dprintf("layer_state_set_user 0: %d\n", layer);
        #ifdef RGBLIGHT_ENABLE
          #ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
          #else
            rgblight_init();
          #endif
        #endif
        break;
      case 1:
      dprintf("layer_state_set_user 1: %d\n", layer);
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
          //rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_1,4);  // Color LED 4 and 5 the color in the config for this layer
          //rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_1,5);  // Color LED 4 and 5 the color in the config for this layer
        #endif
        break;
      case 2:
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_2,0);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_2,8);
         #endif
        break;
      case 3:
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_3,12);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_3,13);
        #endif
        break;
      case 4:
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_4,9);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_4,16);
        #endif
        break;
      case 5:
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_5,1);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_5,7);
        #endif
        break;
      case 6:
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_6,10);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_6,15);
        #endif
        break;
      case 7:
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_7,2);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_7,6);
        #endif
        break;
      case 8:
        #ifdef RGBLIGHT_COLOR_LAYER_8
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_8,11);
          rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_8,14);
        #endif
        break;
      default:
        break;
    }

    return state;
};
