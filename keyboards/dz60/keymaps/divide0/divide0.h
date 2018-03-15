enum map_layers {
  _QWER = 0,
  #ifdef LAYOUT_COLEMAK
  _COLE = 1,  // 1
  #endif
  #ifdef LAYOUT_WORKMAN
  _WORK = 2,  // 2
  #endif
  #ifdef LAYOUT_DVORAK
  _DVOR = 3,  // 3
  #endif
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
  RPET,
  //SPECIAL KEYS & MACROS
  RGB_DEF, // To save default layer rgb color after init and beyond
  A_MUL,   // Mouse Upper left diagonal
  A_MUR,   // Mouse Upper right diagonal
  A_MDL,   // Mouse Lower left diagonal
  A_MDR,   // Mouse Lower right diagonal
  VERS,
  TILSLSH,
  EPRM,
  DYNAMIC_MACRO_RANGE // Must be last
};

enum map_dances {
  TTT = 0,
  BSLHT,
  CAPT,
  ENTT,
  TABT,
  GUIT,
  LSFTT,
  LCTLT,
};

enum tap_types {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

#ifdef RGBLIGHT_ENABLE
  rgblight_config_t rgblight_startup_config;
#endif

#ifdef TAP_DANCE_ENABLE
  typedef struct {
    bool is_press_action;
    int state;
  } xtap;
#endif

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

#ifdef TAP_DANCE_ENABLE

  void send_all_taps(uint16_t keycode, uint8_t multi);

  int cur_dance (qk_tap_dance_state_t *state);
  int hold_cur_dance (qk_tap_dance_state_t *state);

  void x_finished (qk_tap_dance_state_t *state, void *user_data);
  void x_reset (qk_tap_dance_state_t *state, void *user_data);

  void h_finished (qk_tap_dance_state_t *state, void *user_data);
  void h_reset (qk_tap_dance_state_t *state, void *user_data);

  void tab_finished (qk_tap_dance_state_t *state, void *user_data);
  void tab_reset (qk_tap_dance_state_t *state, void *user_data);

  void comma_finished (qk_tap_dance_state_t *state, void *user_data);
  void comma_reset (qk_tap_dance_state_t *state, void *user_data);

  void bslh_finished (qk_tap_dance_state_t *state, void *user_data);
  void bslh_reset (qk_tap_dance_state_t *state, void *user_data);

  void cap_finished (qk_tap_dance_state_t *state, void *user_data);
  void cap_reset (qk_tap_dance_state_t *state, void *user_data);

  void ttt_finished (qk_tap_dance_state_t *state, void *user_data);
  void ttt_reset (qk_tap_dance_state_t *state, void *user_data);

  void gui_finished (qk_tap_dance_state_t *state, void *user_data);
  void gui_reset (qk_tap_dance_state_t *state, void *user_data);

  void rctl_finished (qk_tap_dance_state_t *state, void *user_data);
  void rctl_reset (qk_tap_dance_state_t *state, void *user_data);

  void lsft_finished (qk_tap_dance_state_t *state, void *user_data);
  void lsft_reset (qk_tap_dance_state_t *state, void *user_data);
#endif

// SHORTEN STUFF
// ----------------------------------------------------------------
#define _________ KC_TRNS
#define ________ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define PRESS(kc)   register_code(kc)
#define RELEASE(kc) unregister_code(kc)
#define SEND_VERS SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP ":v" KEYMAP_VERSION)
// KEY MACROS
#define MYCUT     RCTL(KC_X) // -------------------- Edits x,c,v,z
#define MYCOPY    RCTL(KC_C)
#define MYPASTE   RCTL(KC_V)
#define MYUNDO    RCTL(KC_Z)
#define MYREDO    RCTL(RSFT(KC_Z))
#define ALT_SHFT  LSFT(KC_LALT) // ----- Double Modifier ONLY hold
#define CTR_SHFT  LSFT(KC_LCTL)
#define MYTOP     RCTL(KC_PGUP) // -------------- Navigation other
#define MYBOT     RCTL(KC_PGDN)
#define CLEFT     RCTL(KC_LEFT) // -------- Partial word movements
#define CRIGHT    RCTL(KC_RIGHT)
#define CSLEFT    RCTL(RSFT(KC_LEFT))
#define CSRIGHT   RCTL(RSFT(KC_RIGHT))
#define ALEFT     RALT(KC_LEFT)
#define ARIGHT    RALT(KC_RIGHT)
#define ASLEFT    RALT(RSFT(KC_LEFT))
#define ASRIGHT   RALT(RSFT(KC_RIGHT))
#define WINL      LGUI(KC_LEFT) // --------- Windows/gui movements
#define WINR      LGUI(KC_RIGHT)
#define WINUP     LGUI(KC_UP)
#define WINDN     LGUI(KC_DOWN)
#define PRETAB    LCTL(LSFT(KC_TAB))
#define NXTTAB    LCTL(KC_TAB)
#define VDRIGHT   LCTL(LGUI(KC_RIGHT))
#define VDLEFT    LCTL(LGUI(KC_LEFT))
#define PSCR      KC_PSCREEN // ---------------------------- Misc.
#define CAD       LCTL(LALT(KC_DEL))
#define TASK      LCTL(LSFT(KC_ESC))
#define REC1 DYN_REC_START1 // ------------------------- Macros
#define REC2 DYN_REC_START2
#define PLAY1 DYN_MACRO_PLAY1
#define PLAY2 DYN_MACRO_PLAY2
#define RECSTOP DYN_REC_STOP


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
