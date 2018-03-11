#include "dz60.h"
#include "divide0.h"
#include "eeconfig.h"
#include "dynamic_macro.h"
#include "version.h"
#ifdef MOUSEKEY_ENABLE
  #include "mousekey.h"
#endif

#define KEYMAP_REV "1.10"
/*
NOTES:
  add ctl+directions/alt+directions/top/bottom/word-del-forward/ to left hand on _FKEY instead of mouse movement?
  actually overlay not clear arrow cluster for temp mouse/pgup.dn/next.prev\top.bottom for sigle FN press cluster switching
      FN(1 tap) for hoome/end 2 tapgs back/forw 3 taps top/bottom? hold to clear?
TODO:
  change LEDS_TAB to only swtich to led layer when no MODS are in pressed
  change layer colors to config dwords so you can save more complete layer configs although they would be reset unless save to eeprom

     *      ,---------------------------------------------------------------------------------------------------------------------.
     *      |       |       |       |       |       |       |       |       |       |       |       |       |       |             |
     *      |---------------------------------------------------------------------------------------------------------------------+
     *      |          |       |       |       |       |       |       |       |       |       |       |       |       |          |
     *      |---------------------------------------------------------------------------------------------------------------------+
     *      |            |       |       |       |       |       |       |       |       |       |       |       |                |
     *      |---------------------------------------------------------------------------------------------------------------------+
     *      |             |       |       |       |       |       |       |       |       |       |       |       |       |       |
     *      |---------------------------------------------------------------------------------------------------------------------+
     *      |         |         |         |               |         |                     |       |       |       |       |       |
     *      `---------------------------------------------------------------------------------------------------------------------'
*/

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // [CALCCOMP] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_MY_COMPUTER),
  // [CALC_PRINTSCREEN] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_PSCR),
  // [ALTF4] = ACTION_TAP_DANCE_DOUBLE(KC_F4,LALT(KC_F4)),
  [TTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ttt_finished, ttt_reset),
  [BTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bt_finished, bt_reset),
  [CMMT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comma_finished, comma_reset),
  [TABT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished, tab_reset),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  // dprintf("STARTING UP ...");
  #ifdef BACKLIGHT_BREATHING
    // dprintf("BACKLIGHT_BREATHING is enabled!\n");
    breathing_period_set(2);
    breathing_pulse();
  #endif
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  #ifdef RGBLIGHT_ENABLE
    // save RGB values so we can switch restore when layer switching
    // dprintf("SAVING RGBLIGHT VALUES");
    // eeconfig_debug_rgblight();
    rgblight_startup_config.raw = eeconfig_read_rgblight();
  #endif
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //                      A          S          D          F          G          H          J          K          L          :          '          ENTER      BSPC
    [_QWER] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
  		KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
  		TD(TABT),             KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   TD(BTT),
  		FKEY_ESC,             KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
  		KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      TD(CMMT),  KC_DOT,    KC_SLSH,   SHFT_BLS,  KC_UP,      BASE,
  		KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPACE,  TD(TTT),   KC_SPACE,                        KC_RCTL,   MO(_FKEY), KC_LEFT,   KC_DOWN,    KC_RIGHT
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
    */
    // LEFT:WORDS + EDITS | RIGHT:FKEYS + MOVEMENTS
    [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_GESC,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_BSPC,
      _________,            _________, _________, _________, _________, KC_WH_U,   MYCOPY,    KC_HOME,   KC_PGUP,   KC_END,    MYPASTE,   _________, _________, TD(TD_Q_R),
      _________,            CSLEFT,    CLEFT,     CRIGHT,    CSRIGHT,   _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _________, _________, KC_ENT,
      _________,            MYUNDO,    MYCUT,     MYCOPY,    MYPASTE,   KC_WH_D,   _________, CLEFT,     KC_PGDN,   CRIGHT,    MYREDO,    _________, KC_PGUP,   _________,
      _________, _________, _________,                       KC_SPACE,  TD(TTT),   KC_SPACE,                        _________, _________, KC_HOME,   KC_PGDN,   KC_END
    ),
    [_PNTR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   KC_BTN1,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________, _________, _________, KC_ACL0,   KC_ACL1,   KC_ACL2,              _________,
  		_________,            KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   _________, _________, _________, _________, _________, _________, _________, _________, RESET,
  		_________,            KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   _________, _________, _________, _________, _________, _________, _________, _________,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_BTN1,   KC_MS_U,   KC_BTN2,
  		_________, _________, _________,                       KC_SPACE,  TD(TTT),   KC_SPACE,                        _________, _________, KC_MS_L,   KC_MS_D,   KC_MS_R
    ),
  	[_LEDS] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,  RGB_M_SN,  RGB_M_K,   RGB_M_X,   RGB_M_G,   _________, _________, RGB_RMOD,  RGB_MOD,              RGB_TOG,
  		_________,            RGB_HUI,   RGB_SAI,   RGB_VAI,   _________, _________, _________, QWER,      COLE,      WORK,      DVOR,      _________, _________, RESET,
  		_________,            RGB_HUD,   RGB_SAD,   RGB_VAD,   _________, _________, _________, FKEY,      PNTR,      LEDS,      MDIA,      MACR,      RGB_DEF,
      _________,            _________, _________, BL_DEC,    BL_TOGG,   BL_INC,    _________, SYMB,      _________, _________, _________, _________, _________, _________,
  		_________, _________, _________,                       KC_SPACE,  TD(TTT),   KC_SPACE,                        _________, _________, _________, _________, _________
    ),
  	[_MDIA] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		KC_GESC,   KC_WSCH,   KC_MAIL,   KC_CALC,   KC_MYCM ,  KC_WREF,   KC_WSTP,   _________, _________, _________, _________, KC_SLEP,   KC_WAKE,              KC_MSTP,
  		_________,            _________, _________, _________, KC_WREF,   _________, _________, _________, _________, _________, _________, _________, _________, RESET,
  		_________,            KC_WBAK,   _________, _________, _________, KC_WFWD,   KC_WBAK,   _________, _________, KC_WFWD,   _________, _________, KC_MPLY,
  		_________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_WFAV,   _________, KC_VOLU,   _________,
  		_________, _________, _________,                       KC_SPACE,  TD(TTT),   KC_SPACE,                        _________, _________, KC_MPRV,   KC_VOLD,   KC_MNXT
    ),
    /* SYMB
     * ,-----------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * | Del |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |  ~  |  `  |  +  |  =  |  |  |  \  |  [  |  ]  |  {  |  }  |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |     |     |     |     |     |     |     |     |
     * `-----------------------------------------------------------------------'
     */
    [_SYMB] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_BSPC,
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
    ),
    /*
    //This layer is intended to be a layer where QWERTY is mirrored without any HOLD keys so any key can be eaisly repeated by holding down the key.

    [_RPET] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      _________,            KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   _________,
      _________,            KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
      _________,            KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   SHFT_BLS,  KC_UP,     _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ),
    */
    /*
    [_MACR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      RECSTOP,              PLAY1,     PLAY2,     _________, _________, _________, _________, _________, _________, _________, REC1,      REC2,                 _________,
      _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________, _________, _________,                       TD(TD_L23),TD(TD_L10),QWER,                            _________, _________, _________, _________, _________
    )
    */
  };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_record_dynamic_macro(keycode, record)) {
        return false;
  }
  //TO stop recording macro by using MO(LAYER) after starting a rec
  uint16_t macro_kc = (keycode == MO(_MACR) ? DYN_REC_STOP : keycode);
  if (!process_record_dynamic_macro(macro_kc, record)) {
    return false;
  }
  // uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
  // uint8_t ctled = get_mods() & (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL));


  if (record->event.pressed) { // KEY IS DOWN
    switch(keycode) {
      // LAYER SWITCHING
      case BASE:
        layer_clear();
        // dprintf("Going to base for clear ...\n");
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
        layer_on(_PNTR);
        return false;
      case LEDS:
        layer_on(_LEDS);
        // if (shifted) ? layer_off(_LEDS) : layer_on(_LEDS);
        return false;
      case SYMB:
        layer_on(_SYMB);
        // if (ctled) ? layer_off(_SYMB) : layer_on(_SYMB);
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

    }
  }
  return true;
};

#ifdef RGBLIGHT_ENABLE
  uint32_t layer_state_set_user(uint32_t state) {

  rgblight_config_t rgblight_entry_config;
  rgblight_entry_config.raw = eeconfig_read_rgblight();

  uint8_t default_layer = eeconfig_read_default_layer();
  uint8_t tobright = 120;

  if (rgblight_entry_config.enable) {
    printf("Lights were on testing need for adjustment .val = %u", rgblight_entry_config.val);
    // set a reasonable brightness increase adjustment as to not shock you with brightness increases (170 = 255, 20 = 30)
    tobright = (rgblight_entry_config.val <= 170) ? ((rgblight_entry_config.val / 2) + rgblight_entry_config.val) : 255;
  }
  printf("Brightness value PRE:CUR %d:%d", rgblight_entry_config.val, tobright);

  // don't change mode if we are currently static or breathing
  uint8_t mode = (rgblight_entry_config.mode <= 2) ? rgblight_entry_config.mode : 1 ;
  printf("Mode value PRE:CUR %d:%d", rgblight_entry_config.mode, mode);

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
        // dprintf("Entering the default layer ...");
        eeconfig_debug_rgblight();
        // dprintf("Setting previous values for default\\ layer ...");
        // reset default layer rgb values from defualts
        rgblight_update_dword(rgblight_startup_config.raw);
      }
      break;
  }
  return state;
}
#endif

#ifdef TAP_DANCE_ENABLE

  // To activate SINGLE_HOLD, you will need to hold for 200ms first.
  // This tap dance favors keys that are used frequently in typing like 'f'
  int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
      //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
      if (state->interrupted) {
        //     if (!state->pressed) return SINGLE_TAP;
        //need "permissive hold" here.
        //     else return SINsGLE_HOLD;
        //If the interrupting key is released before the tap-dance key, then it is a single HOLD
        //However, if the tap-dance key is released first, then it is a single TAP
        //But how to get access to the state of the interrupting key????
        return SINGLE_TAP;
      }
      else {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
      }
    }
    //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
    //with single tap.
    else if (state->count == 2) {
      if (state->interrupted) return DOUBLE_SINGLE_TAP;
      else if (state->pressed) return DOUBLE_HOLD;
      else return DOUBLE_TAP;
    }
    else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
    else if (state->count == 3) return TRIPLE_HOLD;
    else return 8; //magic number. At some point this method will expand to work for more presses
  }

  //This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
  int hold_cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
      if (state->interrupted) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
      }
      else {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
      }
    }
    //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
    //with single tap.
    else if (state->count == 2) {
      if (state->pressed) return DOUBLE_HOLD;
      else return DOUBLE_TAP;
    }
    else if (state->count == 3) {
      if (!state->pressed) return TRIPLE_TAP;
      else return TRIPLE_HOLD;
    }
    else return 8; //magic number. At some point this method will expand to work for more presses
  }

  /* ----------------------------------------------------
  ******************  TAB toggle  ********************
  ---------------------------------------------------- */
  // TAB, ALT + SHIFT, TAB TAB, CTRL + SHIFT

  static xtap tab_state = {
    .is_press_action = true,
    .state = 0
  };

  void tab_finished (qk_tap_dance_state_t *state, void *user_data) {
    tab_state.state = cur_dance(state);
    switch (tab_state.state) {
      case SINGLE_TAP:  register_code(KC_TAB); break;  //send tab on single press
      case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_LCTL); break;
      case DOUBLE_HOLD: register_code(KC_LCTL); register_code(KC_LALT); break; //alt shift on single hold
      case DOUBLE_TAP:  register_code(KC_TAB);  register_code(KC_TAB); register_code(KC_TAB); break; //tab tab
      case TRIPLE_TAP:  break;
      case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LALT); break;
    }
  }

  void tab_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (tab_state.state) {
      case SINGLE_TAP:  unregister_code(KC_TAB); break; //unregister tab
      case SINGLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LCTL); break;
      case DOUBLE_HOLD: unregister_code(KC_LCTL); unregister_code(KC_LALT); break; //let go of alt shift
      case DOUBLE_TAP:  unregister_code(KC_TAB); break;
      case TRIPLE_TAP:  break;
      case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LALT); break;
    }
    tab_state.state = 0;
  }

  /* ----------------------------------------------------
  *****************  Super Comma *********************
  ---------------------------------------------------- */

  // // Assumption: we don't care about trying to hit ,, quickly
  static xtap comma_state = {
    .is_press_action = true,
    .state = 0
  };

  void comma_finished (qk_tap_dance_state_t *state, void *user_data) {
    comma_state.state = hold_cur_dance(state); //Use the dance that favors being held
    switch (comma_state.state) {
      case SINGLE_TAP:  register_code(KC_COMMA); break;
      case SINGLE_HOLD: layer_on(_FKEY); break;
      case DOUBLE_TAP:  layer_invert(_PNTR); break;
      case DOUBLE_HOLD: layer_on(_SYMB); break;
      case TRIPLE_TAP:  register_code(KC_CALCULATOR); break;
      case TRIPLE_HOLD: layer_on(_MACR);
    }
  }

  void comma_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (comma_state.state) {
      case SINGLE_TAP:  unregister_code(KC_COMMA); break; //unregister comma
      case SINGLE_HOLD: layer_off(_FKEY); break;
      case DOUBLE_TAP:  break;
      case DOUBLE_HOLD: layer_off(_SYMB); break;
      case TRIPLE_TAP:  unregister_code(KC_CALCULATOR); break;
      case TRIPLE_HOLD: layer_off(_MACR);
    }
    comma_state.state = 0;
  }

  /* ----------------------------------------------------
  ***************  S1 tap toggle  ********************
  ---------------------------------------------------- */

  //Good example for accessing multiple layers from the same key.
  static xtap S1_state = {
    .is_press_action = true,
    .state = 0
  };

  void bt_finished (qk_tap_dance_state_t *state, void *user_data) {
    S1_state.state = cur_dance(state);
    switch (S1_state.state) {
      case SINGLE_TAP:  register_code(KC_F3); break;
      case SINGLE_HOLD: layer_on(_SYMB); break;
      case DOUBLE_TAP:  layer_invert(_SYMB); break;
      case DOUBLE_HOLD: layer_on(_PNTR); break;
      case DOUBLE_SINGLE_TAP: layer_invert(_PNTR); break;
    }
  }

  void bt_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (S1_state.state) {
      case SINGLE_TAP:  unregister_code(KC_F3); break;
      case SINGLE_HOLD: layer_off(4); break;
      case DOUBLE_TAP:  break; //already inverted. Don't do anything.
      case DOUBLE_HOLD: layer_off(5); break;
      case DOUBLE_SINGLE_TAP: break;
    }
    S1_state.state = 0;
  }

  /* ----------------------------------------------------
  *************** Super tap toggle *******************
  ---------------------------------------------------- */

  static xtap ttt_state = {
    .is_press_action = true,
    .state = 0
  };

  void ttt_finished (qk_tap_dance_state_t *state, void *user_data) {
    ttt_state.state = cur_dance(state);
    switch (ttt_state.state) {
      case SINGLE_TAP:  layer_invert(_FKEY); break;
      case SINGLE_HOLD: layer_on(_FKEY); break;
      case DOUBLE_TAP:  layer_invert(_PNTR); break;
      case DOUBLE_HOLD: layer_on(_PNTR); break;
      case DOUBLE_SINGLE_TAP: layer_invert(_PNTR); break;
      case TRIPLE_TAP:  layer_invert(_SYMB); break;
      case TRIPLE_HOLD: layer_on(_SYMB); break;
    }
  }

  void ttt_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ttt_state.state) {
      case SINGLE_TAP:  break;
      case SINGLE_HOLD: layer_off(_FKEY); break;
      case DOUBLE_TAP:  break;
      case DOUBLE_HOLD: layer_off(_PNTR); break;
      case DOUBLE_SINGLE_TAP:  break;
      case TRIPLE_TAP:  break;
      case TRIPLE_HOLD: layer_off(_SYMB); break;
    }
    ttt_state.state = 0;
  }

#endif
