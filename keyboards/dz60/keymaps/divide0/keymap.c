#include "dz60.h"
#include "divide0.h"
#include "dynamic_macro.h"
#include "print.h"
#ifdef MOUSEKEY_ENABLE
  #include "mousekey.h"
#endif

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // [CALCCOMP] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_MY_COMPUTER),
  // [CALC_PRINTSCREEN] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_PSCR),
  // [ALTF4] = ACTION_TAP_DANCE_DOUBLE(KC_F4,LALT(KC_F4)),
  [TTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ttt_finished, ttt_reset),
  [BSLHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bslh_finished, bslh_reset),
  [CAPT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cap_finished, cap_reset),
  [ENTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ent_finished, ent_reset),
  [TABT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(tab_every, tab_finished, tab_reset, 600),
  [GUIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_finished, gui_reset),
  [LSFTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_finished, lsft_reset),
//[LCTLT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_finished, lctl_reset),
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
  		TD(TABT),             KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   TD(BSLHT),
  		TD(CAPT),             KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   TD(ENTT),
  		TD(LSFTT),            KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   SHFT_BLS,  KC_UP,      KC_DEL,
  		KC_LCTL,   TD(GUIT),  KC_LALT,                         KC_SPACE,  TD(TTT),   KC_SPACE,                        KC_HOME,   KC_END,    KC_LEFT,   KC_DOWN,    KC_RIGHT
    ),
    #ifdef LAYOUT_COLEMAK
     [_COLE] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      KC_TAB,               KC_Q,      KC_W,      KC_F,      KC_P,      KC_G,      KC_J,      KC_L,      KC_U,      KC_Y,      KC_SCLN,   KC_LBRC,   KC_RBRC,   RESET,
      KC_LCTL,              KC_A,      KC_R,      KC_S,      KC_T,      KC_D,      KC_H,      KC_N,      KC_E,      KC_I,      KC_O,      KC_QUOT,   KC_ENT,
      KC_LSFT,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_K,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     KC_DEL,
  		KC_LCTL,   TD(GUIT),  KC_LALT,                         KC_SPACE,  TD(TTT),   KC_SPACE,                        KC_HOME,   KC_END,    KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    #endif // LAYOUT_COLEMAK
    #ifdef LAYOUT_WORKMAN
    [_WORK] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      KC_TAB,               KC_Q,      KC_D,      KC_R,      KC_W,      KC_B,      KC_J,      KC_F,      KC_U,      KC_P,      KC_SCLN,   KC_LBRC,   KC_RBRC,   RESET,
      KC_LCTL,              KC_A,      KC_S,      KC_H,      KC_T,      KC_G,      KC_Y,      KC_N,      KC_E,      KC_O,      KC_I,      KC_QUOT,   KC_ENT,
      KC_LSFT,              KC_Z,      KC_X,      KC_M,      KC_C,      KC_V,      KC_K,      KC_L,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_BSLS,   KC_UP,     KC_DEL,
  		KC_LCTL,   TD(GUIT),  KC_LALT,                         KC_SPACE,  TD(TTT),   KC_SPACE,                        KC_HOME,   KC_END,    KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    #endif // LAYOUT_WORKMAN
    #ifdef LAYOUT_DVORAK
    [_DVOR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      KC_ESC,    KC_1,      KC_2 ,     KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_LBRC,   KC_RBRC,              KC_BSPC,
      KC_TAB,               KC_QUOT,   KC_COMM,   KC_DOT,    KC_P,      KC_Y,      KC_F,      KC_G,      KC_C,      KC_R,      KC_L,      KC_SLSH,   KC_EQL,    RESET,
      KC_LCTL,              KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,      KC_MINS,   KC_ENT,
      KC_LSFT,              KC_SCLN,   KC_Q,      KC_J,      KC_K,      KC_X,      KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,      KC_BSLS,   KC_UP,     KC_DEL,
      KC_LCTL,   TD(GUIT),  KC_LALT,                         KC_SPACE,  TD(TTT),   KC_SPACE,                        KC_HOME,   KC_END,    KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    #endif // LAYOUT_DVORAK
    // LEFT:WORDS + EDITS | RIGHT:FKEYS + MOVEMENTS
    [_FKEY] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,               KC_BSPC,
      _________,            ASLEFT,    ALEFT,     ARIGHT,    ASRIGHT,   KC_WH_U,   MYCOPY,    KC_HOME,   KC_PGUP,   KC_END,    MYPASTE,   _________, _________, RESET,
      _________,            CSLEFT,    CLEFT,     CRIGHT,    CSRIGHT,   _________, KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _________, _________, _________,
      _________,            MYUNDO,    MYCUT,     MYCOPY,    MYPASTE,   KC_WH_D,   _________, CLEFT,     KC_PGDN,   CRIGHT,    MYREDO,    _________, KC_PGUP,   _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, KC_HOME,   KC_PGDN,   KC_END
    ),
    [_PNTR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		_________, KC_BTN1,   KC_BTN2,   KC_BTN3,   KC_BTN4,   KC_BTN5,   _________, _________, _________, _________, _________, _________, _________,            _________,
  		_________,            _________, KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   KC_WH_U,   KC_BTN1,   KC_MS_U,   KC_BTN2,   _________, _________, _________, RESET,
  		_________,            _________, KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   KC_WH_D,   KC_MS_L,   KC_MS_D,   KC_MS_R,   _________, _________, _________,
  		_________,            _________, KC_ACL0,   KC_ACL1,   KC_ACL2,   _________, _________, KC_ACL0,   KC_ACL1,   KC_ACL2,   _________, _________, _________, _________,
  		_________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ),
  	[_LEDS] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
   		_________, RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,  RGB_M_SN,  RGB_M_K,   RGB_M_X,   RGB_M_G,   _________, _________, RGB_RMOD,  RGB_MOD,              RGB_TOG,
  		_________,            RGB_HUI,   RGB_SAI,   RGB_VAI,   _________, _________, _________, _________, _________, _________, _________, KC_SLEP,   KC_WAKE,   RESET,
  		_________,            RGB_HUD,   RGB_SAD,   RGB_VAD,   _________, _________, _________, _________, _________, _________, KC_MPRV,   KC_MNXT,   RGB_DEF,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, KC_VOLU,   _________,
  		_________, _________, _________,                       _________, _________, _________,                       _________, _________, KC_MSTP,   KC_VOLD,   KC_MPLY
    ),
    //This layer is intended to be a layer where QWERTY is mirrored without any HOLD keys so any key can be eaisly repeated by holding down the key.
  	[_MDIA] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,               KC_BSPC,
      _________,            KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   _________,
      _________,            KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
      _________,            KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   SHFT_BLS,  KC_UP,     _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
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
      RECSTOP,   PLAY1,     PLAY2,     _________, _________, _________, _________, _________, _________, _________, REC1,      REC2,      _________,            _________,
      _________,            TT(_MACR), TT(_LEDS), TT(_MDIA), TT(_PNTR), TT(_FKEY), TT(_FKEY), TT(_PNTR), TT(_MDIA), TT(_LEDS), TT(_MACR), _________, _________, _________,
      _________,            KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,   _________, _________,
      _________,            KC_TILD,   KC_GRV,    KC_PLUS,   KC_EQL,    KC_PIPE,   KC_BSLS,   KC_LBRC,   KC_RBRC,   KC_LCBR,   KC_RCBR,   _________, _________, _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ),
    [_MACR] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
      _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,            _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
      _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    ),
    // [_LOCK] = KEYMAP_2U_SHIFT_BACKSPACE_DIRECTIONAL(
    //   _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,            _________,
    //   _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
    //   _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
    //   _________,            _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________, _________,
    //   _________, _________, _________,                       _________, _________, _________,                       _________, _________, _________, _________, _________
    // ),
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
      case REC1: // Clear the layers so we can start recording
        layer_clear();
        return true;
      case REC2: // Clear the layers so we can start recording
          layer_clear();
          return true;
      case RGB_DEF:
        //dprintf("SAVING NEW DEFAULTS FROM KEYPRESS");
        //eeconfig_debug_rgblight();
        rgblight_startup_config.raw = eeconfig_read_rgblight();
        return false;
      // LAYER SWITCHING
      case BASE:
        layer_clear();
        // dprintf("Going to base for clear ...\n");
        return false;
      case QWER:
        layer_clear();
        //dprintf("trying switch QWER: %d\n", keycode);
        persistent_default_layer_set(1UL<<_QWER);
        return false;
      #ifdef LAYOUT_COLEMAK
        case COLE:
          layer_clear();
          persistent_default_layer_set(1UL<<_COLE);
          return false;
      #endif // LAYOUT_COLEMAK
      #ifdef LAYOUT_WORKMAN
        case WORK:
          layer_clear();
          persistent_default_layer_set(1UL<<_WORK);
          return false;
      #endif // LAYOUT_WORKMAN
      #ifdef LAYOUT_DVORAK
        case DVOR:
          layer_clear();
          persistent_default_layer_set(1UL<<_DVOR);
          return false;
      #endif // LAYOUT_DVORAK
      case FKEY:
        layer_on(_FKEY);
        //dprintf("trying switch FKEY: %d\n", keycode);
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
      // EVERTYIHNG ELSE
      case VERS:
        SEND_VERS;
        return false;
      case TILSLSH:
        SEND_STRING ("~/.");
        return false;
      case EPRM:
        eeconfig_init();
        return false;
      // RGB CHANGES
      // case DEBUG:
      //   debug_enable = true;
      //   print("DEBUG: enabled.\n");
      //   return false;
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
      #endif // MOUSEKEY_ENABLE
    }
  } else { // KEY IS UP (!event.pressed)
    switch(keycode) {
      #ifdef RGBLIGHT_ENABLE
      // These fall through to RGB_TOG
      // which saves the rgb config for the default layer if it is changed.
      // This is neccesary because the RGB layer has its own color and when you
      // change it isn't refelcted on the default layer unless saved to eeconf
      case RGB_MODE_FORWARD:
      case RGB_MODE_REVERSE:
      case RGB_HUI:
      case RGB_HUD:
      case RGB_SAI:
      case RGB_SAD:
      case RGB_VAI:
      case RGB_VAD:
      case RGB_MODE_PLAIN:
      case RGB_MODE_BREATHE:
      case RGB_MODE_RAINBOW:
      case RGB_MODE_SWIRL:
      case RGB_MODE_SNAKE:
      case RGB_MODE_KNIGHT:
      case RGB_MODE_XMAS:
      case RGB_MODE_GRADIENT:
      case RGB_TOG:
        eeconfig_debug_rgblight();
        rgblight_startup_config.raw = eeconfig_read_rgblight();
      #endif // RGBLIGHT_ENABLE
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
      #endif // MOUSEKEY_ENABLE

    }
  }
  return true;
};

#ifdef RGBLIGHT_ENABLE
  uint32_t layer_state_set_user(uint32_t state) {

  rgblight_config_t rgblight_entry_config;
  rgblight_entry_config.raw = eeconfig_read_rgblight();

  //uint8_t default_layer = eeconfig_read_default_layer();
  uint8_t tobright = 120;

  if (rgblight_entry_config.enable) {
    //printf("Lights were on testing need for adjustment .val = %u", rgblight_entry_config.val);
    // set a reasonable brightness increase adjustment as to not shock you with brightness increases (170 = 255, 20 = 30)
    if (rgblight_entry_config.val > 0) {
      tobright = (rgblight_entry_config.val <= 170) ? ((rgblight_entry_config.val / 2) + rgblight_entry_config.val) : 255;
    }
  }
  //printf("Brightness value PRE:CUR %d:%d", rgblight_entry_config.val, tobright);

  // don't change mode if we are currently static or breathing
  uint8_t mode = (rgblight_entry_config.mode <= 2) ? rgblight_entry_config.mode : 1 ;
  //printf("Mode value PRE:CUR %d:%d", rgblight_entry_config.mode, mode);

  switch (biton32(state)) {
    // Case seems to have to check from lowest to highest
    // or at least check layers in orderto use the highest layer color
    case _FKEY:
      rgblight_enable();
      rgblight_mode(mode);
      rgblight_sethsv_noeeprom(240, 255, tobright); // blue
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
      rgblight_sethsv(16, 176, tobright); // coral_red
      break;
    default:

      #ifdef LAYOUT_COLEMAK
      if (default_layer & (1UL << _COLE)) {
        rgblight_sethsv(300, 255, rgblight_entry_config.val); // magenta _COLE/_DVOR/_WORK not yet integrated ...
        break;
      }
      #endif // LAYOUT_COLEMAK

      #ifdef LAYOUT_DVORAK
      if (default_layer & (1UL << _DVOR)) {
        rgblight_sethsv(120, 255, rgblight_entry_config.val); // green _COLE/_DVOR/_WORK not yet integrated ...
        break;
      }
      #endif // LAYOUT_DVORAK

      #ifdef LAYOUT_WORKMAN
      if (default_layer & (1UL << _WORK)) {
        rgblight_sethsv(43, 218, rgblight_entry_config.val); // goldenrod _COLE/_DVOR/_WORK not yet integrated ...
        break;
      }
      #endif // LAYOUT_WORKMAN
      // NO DEFAULT LAYERS MATCHED MUST BE QWERTY ...
      //xprintf("Setting previous values for default layer: %d", default_layer);
      eeconfig_debug_rgblight();
      // reset default layer rgb values from startup or last saved values
      rgblight_update_dword(rgblight_startup_config.raw);
      break;
  }
  return state;
}
#endif // #RGBLIGHT_ENABLE

#ifdef TAP_DANCE_ENABLE

  void send_all_taps(uint16_t keycode, uint8_t multi) {
    if (multi > 0) {
      uint8_t presses = (multi / 2);
      for (uint8_t i = 0; i < presses; i++) {
        //xprintf("presses: %d \r\n", presses);
        register_code(keycode);
        unregister_code(keycode);
        if (i > 15)  { return; } // watch for runaways ...
      }
    }
  }

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
      //  if (state->interrupted) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
      // }
      // else {
      //   if (!state->pressed) return SINGLE_TAP;
      //   else return SINGLE_HOLD;
      // }
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
    .is_press_action = false,
    .state = 0
  };

  void tab_every (qk_tap_dance_state_t *state, void *user_data) {
    uint8_t sfted = get_mods() & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT));
    uint8_t ctled = get_mods() & (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL));
    uint8_t alted = get_mods() & (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT));
    if (sfted || ctled || alted) {
      // xprintf("TAP:1-(%d) TD_TAB WAS modded -> sending <tab> and setting (is_press_action) true.\r\n", state->count);
      register_code(KC_TAB);
      tab_state.is_press_action = true;
      state->finished = true;
    }
  }

  void tab_finished (qk_tap_dance_state_t *state, void *user_data) {
    tab_state.state = hold_cur_dance(state);
    // xprintf("TAP:(%d) tab_state.state: (%d) --> IS PRESS ACTION ->in finished.\r\n", state->count, tab_state.state);
    switch (tab_state.state) {
      case SINGLE_TAP:  register_code(KC_TAB); break;  //send tab on single press
      case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_LCTL); break;
      case DOUBLE_HOLD: register_code(KC_LCTL); register_code(KC_LALT); break; //alt shift on single hold
      case DOUBLE_TAP:  register_code(KC_TAB);  unregister_code(KC_TAB); register_code(KC_TAB); break; //tab tab
      case TRIPLE_TAP:  register_code(KC_TAB);  unregister_code(KC_TAB); register_code(KC_TAB);  unregister_code(KC_TAB); register_code(KC_TAB);  break;
      case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LALT); break;
      default: send_all_taps(KC_TAB, tab_state.state);
    }
  }

  void tab_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (tab_state.is_press_action) {
      // xprintf("TAP:(%d) tab_state.state: (%d) is_press_action: (%d) --> NOT PRESS ACTION -> reseting tab_state.state to 0 -> in reset\r\n", state->count, tab_state.state, tab_state.is_press_action);
      unregister_code(KC_TAB);
      tab_state.is_press_action = false;
    }
    else {
      switch (tab_state.state) {
        //xprintf("TAP:(%d) tab_state.state: (%d) --> IS PRESS ACTION ->in reset.\r\n", state->count, tab_state.state);
        case SINGLE_TAP:  unregister_code(KC_TAB); break; //unregister tab
        case SINGLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LCTL); break;
        case DOUBLE_HOLD: unregister_code(KC_LCTL); unregister_code(KC_LALT); break; //let go of alt shift
        case DOUBLE_TAP:  unregister_code(KC_TAB); break;
        case TRIPLE_TAP:  unregister_code(KC_TAB); break;
        case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LALT); break;
        // default: break; // already sent all keycodes ...
      }
    }
    tab_state.state = 0;
  }

  /* ----------------------------------------------------
  *****************  Enter Tap ***********************
  ---------------------------------------------------- */

  static stap ent_state = { .state = 0 };

  void ent_finished (qk_tap_dance_state_t *state, void *user_data) {
    ent_state.state = cur_dance(state); //Use the dance that favors being held
    switch (ent_state.state) {
      case SINGLE_TAP:  register_code(KC_ENTER); break;
      case SINGLE_HOLD: layer_move(_FKEY); break;
      case DOUBLE_TAP:  layer_invert(_PNTR); break;
      case DOUBLE_HOLD: layer_move(_SYMB); break;
      case TRIPLE_TAP:  register_code(KC_CALCULATOR); break;
      case TRIPLE_HOLD: layer_move(_MACR);
    }
  }

  void ent_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ent_state.state) {
      case SINGLE_TAP:  unregister_code(KC_ENTER); break; //unregister comma
      case SINGLE_HOLD: layer_off(_FKEY); break;
      case DOUBLE_TAP:  break;
      case DOUBLE_HOLD: layer_off(_SYMB); break;
      case TRIPLE_TAP:  unregister_code(KC_CALCULATOR); break;
      case TRIPLE_HOLD: layer_off(_MACR);
    }
    ent_state.state = 0;
  }

  /* ----------------------------------------------------
  ******************  CAPS toggle  ********************
  ---------------------------------------------------- */

  //Good example for accessing multiple layers from the same key.
  static xtap CAP_state = {
    .is_press_action = true,
    .state = 0
  };

  void cap_finished (qk_tap_dance_state_t *state, void *user_data) {
    CAP_state.state = cur_dance(state);
    switch (CAP_state.state) {
      case SINGLE_TAP:  register_code(KC_ESC); break;
      case SINGLE_HOLD: layer_move(_FKEY); break;
      case DOUBLE_TAP:  layer_clear(); break; // Clear layers and return to BASE layer
      case DOUBLE_HOLD: layer_move(_PNTR); break;
      case DOUBLE_SINGLE_TAP: SEND_VERS; break;
    }
  }

  void cap_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (CAP_state.state) {
      case SINGLE_TAP:  unregister_code(KC_ESC); break;
      case SINGLE_HOLD: layer_off(_FKEY); break;
      case DOUBLE_TAP:  break;
      case DOUBLE_HOLD: layer_off(_PNTR); break;
      case DOUBLE_SINGLE_TAP: break;
    }
    CAP_state.state = 0;
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

  /* ----------------------------------------------------
  *************** RCTL tap toggle *******************
  ---------------------------------------------------- */

  //Good example for accessing multiple layers from the same key.
  static xtap RCTL_state = {
    .is_press_action = true,
    .state = 0
  };

  void rctl_finished (qk_tap_dance_state_t *state, void *user_data) {
    RCTL_state.state = cur_dance(state);
    switch (RCTL_state.state) {
      case SINGLE_TAP:  layer_move(_LEDS); break;
      case SINGLE_HOLD: register_code(KC_RCTL); break;
    }
  }

  void rctl_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (RCTL_state.state) {
      case SINGLE_TAP:  break;
      case SINGLE_HOLD: unregister_code(KC_RCTL); break;
    }
    RCTL_state.state = 0;
  }

  /* ----------------------------------------------------
  *****************  TAP TEMPLATE tap  ****************
  ---------------------------------------------------- */

  //Good example for accessing multiple layers from the same key.
  static xtap BSLH_state = {
    .is_press_action = true,
    .state = 0
  };

  void bslh_finished (qk_tap_dance_state_t *state, void *user_data) {
    BSLH_state.state = cur_dance(state);
    switch (BSLH_state.state) {
      case SINGLE_TAP:  reset_keyboard(); break;
      case SINGLE_HOLD: layer_move(_SYMB); break;
    }
  }

  void bslh_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (BSLH_state.state) {
      case SINGLE_TAP:  break;
      case SINGLE_HOLD: layer_off(_SYMB); break;
    }
    BSLH_state.state = 0;
  }

  /* ----------------------------------------------------
  *****************  GUI tap  ****************
  ---------------------------------------------------- */

  //Good example for accessing multiple layers from the same key.
  static xtap GUI_state = {
    .is_press_action = true,
    .state = 0
  };

  void gui_finished (qk_tap_dance_state_t *state, void *user_data) {
    GUI_state.state = cur_dance(state);
    switch (GUI_state.state) {
      case SINGLE_TAP:  register_code(KC_LGUI); break;
      case SINGLE_HOLD: register_code(KC_LGUI); break;
      case DOUBLE_TAP:  SEND_STRING("DOUBLE_TAP"); break;
      case DOUBLE_HOLD: SEND_STRING("DOUBLE_HOLD"); break;
      case DOUBLE_SINGLE_TAP: SEND_STRING("DOUBLE_SINGLE_TAP"); break;
    }
  }

  void gui_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (GUI_state.state) {
      case SINGLE_TAP:  unregister_code(KC_LGUI); break;
      case SINGLE_HOLD: unregister_code(KC_LGUI); break;
      case DOUBLE_TAP:  break;
      case DOUBLE_HOLD: break;
      case DOUBLE_SINGLE_TAP: break;
    }
    GUI_state.state = 0;
  }

  /* ----------------------------------------------------
  *************** LCTL tap toggle *******************
  ---------------------------------------------------- */

  //Good example for accessing multiple layers from the same key.
  static xtap LCTL_state = {
    .is_press_action = true,
    .state = 0
  };

  void lctl_finished (qk_tap_dance_state_t *state, void *user_data) {
    LCTL_state.state = cur_dance(state);
    switch (LCTL_state.state) {
      case SINGLE_TAP:  SEND_STRING("SINGLE_TAP"); break;
      case SINGLE_HOLD: SEND_STRING("SINGLE_HOLD"); break;
      case DOUBLE_TAP:  SEND_STRING("DOUBLE_TAP"); break;
      case DOUBLE_HOLD: SEND_STRING("DOUBLE_HOLD"); break;
      case DOUBLE_SINGLE_TAP: SEND_STRING("DOUBLE_SINGLE_TAP"); break;
    }
  }

  void lctl_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (LCTL_state.state) {
      case SINGLE_TAP:  break;
      case SINGLE_HOLD: break;
      case DOUBLE_TAP:  break;
      case DOUBLE_HOLD: break;
      case DOUBLE_SINGLE_TAP: break;
    }
    LCTL_state.state = 0;
  }

  /* ----------------------------------------------------
  // *************** LSFT tap toggle *******************
  ---------------------------------------------------- */

  static xtap LSFT_state = {
    .is_press_action = true,
    .state = 0
  };

  void lsft_finished (qk_tap_dance_state_t *state, void *user_data) {
    LSFT_state.state = hold_cur_dance(state);
    switch (LSFT_state.state) {
      case SINGLE_TAP: set_oneshot_layer(_SYMB, ONESHOT_START); break;
      case SINGLE_HOLD: register_code(KC_LSFT); break;
      default: register_code(KC_LSFT);
    }
  }

  void lsft_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (LSFT_state.state) {
      case SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
      case SINGLE_HOLD: unregister_code(KC_LSFT); break;
      default: unregister_code(KC_LSFT);
    }
    LSFT_state.state = 0;
  }

  /* ----------------------------------------------------
  *****************  TAP TEMPLATE tap  ****************
  ---------------------------------------------------- */
  /*
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
  */
#endif // #TAP_DANCE_ENABLE
