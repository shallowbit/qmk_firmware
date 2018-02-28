#include "dz60.h"
#include "action_layer.h"
//#include "dynamic_macro.h"
#include "mousekey.h"
#include "version.h"
#include "eeconfig.h"
//#include "rgblight.h"

#define KEYMAP_REV "1.03 rough lighting"
/*
NOTES:

  add ctl+directions/alt+directions/top/bottom/word-del-forward/ to left hand on _FKEY instead of mouse movement?
  actually overlay not clear arrow cluster for temp mouse/pgup.dn/next.prev\top.bottom for sigle FN press cluster switching
    FN(1 tap) for hoome/end 2 taps back/forw 3 taps top/bottom? hold to clear?

TODO:
  change LEDS_TAB to only swtich to led layer when no MODS are in pressed
  change layer colors to config dwords so you can save more complete layer configs although they would be reset unless save to eeprom

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
#ifdef RGBLIGHT_ENABLE
rgblight_config_t rgblight_startup_config;
#endif

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
  RGB_DEF, // To save default layer rgb color after init and beyond
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
#define MYCUT     RCTL(KC_X) // KC_CUT??
#define MYCOPY    RCTL(KC_C)
#define MYPASTE   RCTL(KC_V)
#define MYUNDO    RCTL(KC_Z)
#define MYREDO    RCTL(RSFT(KC_Z))
// Double Modifier ONLY hold
#define ALT_SHFT LSFT(KC_LALT)
#define CTR_SHFT LSFT(KC_LCTL)
// Navigation other
#define MYTOP     RCTL(KC_PGUP)
#define MYBOT     RCTL(KC_PGDN)
// Partial word movements
#define CSLEFT   RCTL(KC_LEFT)
#define CSRIGHT  RCTL(KC_RIGHT)
#define CLEFT   RCTL(LSFT(KC_LEFT))
#define CRIGHT  RCTL(LSFT(KC_RIGHT))
#define ALEFT   RALT(KC_LEFT)
#define ARIGHT  RALT(KC_RIGHT)
// Windows/gui movements
#define WINL    LGUI(KC_LEFT)
#define WINR    LGUI(KC_RIGHT)
#define WINUP   LGUI(KC_UP)
#define WINDN   LGUI(KC_DOWN)
#define PRETAB  LCTL(LSFT(KC_TAB))
#define NXTTAB  LCTL(KC_TAB)
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
  // Save these for reference. Maybe use names instead of hard coding below
  // #define rgblight_set_white       rgblight_sethsv(0,   0x00, 255);
  // #define rgblight_set_red         rgblight_sethsv(0,   255, 255);
  // #define rgblight_set_coral       rgblight_sethsv(16,  176, 255);
  // #define rgblight_set_orange      rgblight_sethsv(39,  255, 255);
  // #define rgblight_set_goldenrod   rgblight_sethsv(43,  218, 218);
  // #define rgblight_set_gold        rgblight_sethsv(51,  255, 255);
  // #define rgblight_set_yellow      rgblight_sethsv(60,  255, 255);
  // #define rgblight_set_chartreuse  rgblight_sethsv(90,  255, 255);
  // #define rgblight_set_green       rgblight_sethsv(120, 255, 255);
  // #define rgblight_set_springgreen rgblight_sethsv(150, 255, 255);
  // #define rgblight_set_turquoise   rgblight_sethsv(174, 90,  112);
  // #define rgblight_set_teal        rgblight_sethsv(180, 255, 128);
  // #define rgblight_set_cyan        rgblight_sethsv(180, 255, 255);
  // #define rgblight_set_azure       rgblight_sethsv(186, 102, 255);
  // #define rgblight_set_blue        rgblight_sethsv(240, 255, 255);
  // #define rgblight_set_purple      rgblight_sethsv(270, 255, 255);
  // #define rgblight_set_magenta     rgblight_sethsv(300, 255, 255);
  // #define rgblight_set_pink        rgblight_sethsv(330, 128, 255);
  #ifdef RGBLIGHT_ANIMATIONS
    // const uint16_t RGBLED_GRADIENT_RANGES[] PROGMEM = {360, 240, 180, 120, 90}; // These control which colors are selected for the gradient mode
    // const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {16, 8, 4, 2};       // How long (in ms) to wait between animation steps for the breathing mode
    // const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};      // How long (in ms) to wait between animation steps for the rainbow mode
    // const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};     // How long (in ms) to wait between animation steps for the swirl mode
    // const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};             // How long (in ms) to wait between animation steps for the snake mode
    // const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {127, 63, 31};            // How long (in ms) to wait between animation steps for the knight modes
  #endif
#endif

//SPECIAL<
//SHORTEN SOME FUNCTION CALLS
#define FKEY_ESC LT(MO(_FKEY),KC_ESC)         // fkey(HELD)          esc(TAPPED)
//#define FKEY_CTL LT(MO(_FKEY),OSM(KC_LCTL)) // fkey(HELD)          control(TAPPED)
//#define FKEY_HME LT(MO(_FKEY),KC_HOME) // WORKS fkey(HELD)    home(TAPPED)
#define FKEY_HME LT(TG(_FKEY),KC_HOME) // WORKS fkey(HELD)    home(TAPPED)
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
    //                      A          S          D          F          G          H          J          K          L          :          '          ENTER      BSPC
  	[_QWER] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
  		KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
  		LEDS_TAB,             KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   RESET,
  		FKEY_ESC,             KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
  		KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   SHFT_BLS,  KC_UP,     BASE,
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPACE,  TD(TD_TEST),KC_SPACE,                       FKEY_HME,  PNTR_END,  KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    /*
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
    // LEFT:MOUSE + EDITS | RIGHT:FKEYS + MOVEMENTS
    [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_GESC,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_DEL,
      _________,            KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   FKEY,      MYCOPY,    KC_HOME,   KC_PGUP,   KC_END,    MYPASTE,   _________, _________, TD(TD_Q_R),
      _________,            KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _________, _________, KC_ENT,
      _________,            MYUNDO,    MYCUT,     MYCOPY,    MYPASTE,   KC_BTN1,   KC_BTN2,   KC_INS,    KC_PGDN,   KC_DEL,    MYREDO,    _________, KC_PGUP,   _________,
      _________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, KC_HOME,   KC_PGDN,   KC_END
    ),
    */
    // LEFT:WORDS + EDITS | RIGHT:FKEYS + MOVEMENTS
    [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_GESC,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_DEL,
      _________,            _________, _________, _________, _________, KC_WH_U,   MYCOPY,    KC_HOME,   KC_PGUP,   KC_END,    MYPASTE,   _________, _________, TD(TD_Q_R),
      _________,            CSLEFT,    CSRIGHT,   CLEFT,     CRIGHT,    _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _________, _________, KC_ENT,
      _________,            MYUNDO,    MYCUT,     MYCOPY,    MYPASTE,   KC_WH_D,   _________, CLEFT,     KC_PGDN,   CRIGHT,    MYREDO,    _________, KC_PGUP,   _________,
      _________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, KC_HOME,   KC_PGDN,   KC_END
    ),
    [_PNTR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   KC_BTN1,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________, _________, _________, KC_ACL0,   KC_ACL1,   KC_ACL2,              _________,
  		_________,            KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   PNTR,      _________, _________, _________, _________, _________, _________, _________, RESET,
  		_________,            KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   KC_ACL0,   KC_ACL2,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_BTN1,   KC_MS_U,   KC_BTN2,
  		_________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, KC_MS_L,   KC_MS_D,   KC_MS_R
    ),
  	[_LEDS] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,  RGB_M_SN,  RGB_M_K,   RGB_M_X,   RGB_M_G,   _________, _________, RGB_RMOD,  RGB_MOD,              RGB_TOG,
  		_________,            RGB_HUI,   RGB_SAI,   RGB_VAI,   _________, _________, _________, QWER,      COLE,      WORK,      DVOR,      _________, _________, RESET,
  		_________,            RGB_HUD,   RGB_SAD,   RGB_VAD,   _________, _________, _________, FKEY,      PNTR,      LEDS,      MDIA,      MACR,      RGB_DEF,
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
  // tap once to turn on FKEY layer.
  // Makes it easy to get to other layers. with one tap and one/two spaces
  // These KC layer are also MACROS so the toggles should also flash an LED indication as well
qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_L10] = ACTION_TAP_DANCE_DOUBLE(FKEY, QWER),
   [TD_L23] = ACTION_TAP_DANCE_DOUBLE(PNTR, LEDS),
   [TD_L45] = ACTION_TAP_DANCE_DOUBLE(SYMB, MACR),
   [TD_Q_R] = ACTION_TAP_DANCE_DOUBLE(QWER, RESET),
   [TD_TEST] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  };

/*
void layer_on_override(uint16_t keycode) {
  //dprintf("d  trying switch: %d\n", keycode);
  layer_on(keycode);
  #ifdef BACKLIGHT_BREATHING
      breathing_period_set(2);
      breathing_pulse();
  #endif
};
*/

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
        dprintf("Going to base for clear ...\n");
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
        return false;
      case PNTR:
        //layer_on_override(_PNTR);
        layer_on(_PNTR);
        return false;
      case LEDS:
        layer_on(_LEDS);
        return false;
      case SYMB:
        layer_on(_SYMB);
        return false;
      case MACR:
        layer_on(_MACR);
        return false;
      case MDIA:
        layer_on(_MDIA);
        return false;
      case RGB_DEF:
        dprintf("SAVING NEW DEFAULTS FROM KEYPRESS");
        eeconfig_debug_rgblight();
        rgblight_startup_config.raw = eeconfig_read_rgblight();
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

#ifdef RGBLIGHT_ENABLE
uint32_t layer_state_set_user(uint32_t state) {

  #ifdef CONSOLE_ENABLE
    xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
    //eeconfig_debug_rgblight();
  #endif

  rgblight_config_t rgblight_entry_config;
  rgblight_entry_config.raw = eeconfig_read_rgblight();

  uint8_t default_layer = eeconfig_read_default_layer();
  uint8_t tobright = 120;

  if (rgblight_entry_config.enable) {
    dprintf("Lights were on testing need for adjustment .val = %d", rgblight_entry_config.val);
    // set a reasonable brightness increase adjustment as to not shock you with brightness increases (170 = 255, 20 = 30)
    tobright = (rgblight_entry_config.val <= 170) ? ((rgblight_entry_config.val / 2) + rgblight_entry_config.val) : 255;
  }
  dprintf("Brightness value PRE:CUR %d:%d", rgblight_entry_config.val, tobright);

  // don't change mode if we are currently static or breathing
  uint8_t mode = (rgblight_entry_config.mode <= 2) ? rgblight_entry_config.mode : 1 ;
  dprintf("Mode value PRE:CUR %d:%d", rgblight_entry_config.mode, mode);

  switch (biton32(state)) {
    // Case seems to have to check from lowest to highest
    // or at least check layers in orderto use the highest layer color
    case _FKEY:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv(240, 255, tobright); // blue
      break;
    case _PNTR:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv(90, 255, tobright); // chartreuse
      break;
    case _LEDS:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv(150, 255, tobright); // springgreen
      break;
    case _SYMB:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv(60, 255, tobright); // yellow
      break;
    case _MDIA:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv(43, 218, tobright); // goldenrod
      break;
    case _MACR:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv(16, 176, tobright); // springgreen
      break;
    default:
      if (default_layer & (1UL << _COLE)) {
        //set color values but dont change brightness .. not tested
        rgblight_sethsv(300, 255, rgblight_entry_config.val); // magenta _COLE/_DVOR/_WORK not yet integrated ...
      }
      else if (default_layer & (1UL << _DVOR)) {
        rgblight_sethsv(120, 255, rgblight_entry_config.val); // green _COLE/_DVOR/_WORK not yet integrated ...
      }
      else if (default_layer & (1UL << _WORK)) {
        rgblight_sethsv(43, 218, rgblight_entry_config.val); // goldenrod _COLE/_DVOR/_WORK not yet integrated ...
      }
      else {
        //rgblight_set_teal;
        dprintf("Entering the default layer ...");
        eeconfig_debug_rgblight();
        dprintf("Setting previous values for default\\ layer ...");
        // reset default layer rgb values from defualts
        rgblight_update_dword(rgblight_startup_config.raw);
      }
      break;
  }
  return state;
}
#endif

void matrix_init_user(void) {
  dprintf("STARTING UP ...");
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  #ifdef RGBLIGHT_ENABLE
    // save RGB values so we can switch restore when layer switching
    dprintf("SAVING RGBLIGHT VALUES");
    eeconfig_debug_rgblight();
    rgblight_startup_config.raw = eeconfig_read_rgblight();
  #endif
};
