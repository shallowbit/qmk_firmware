NOTES FOR DIVIDE0 KEYMAP

need ctrl+home and ctrl+end for top page and bottom page


#define CTL_ESC CTL_T(KC_ESC)  // Tap for Escape, hold for Control
#define HPR_TAB ALL_T(KC_TAB)  // Tap for Tab, hold for Hyper (Super+Ctrl+Alt+Shift)
#define MEH_GRV MEH_T(KC_GRV)  // Tap for Backtick, hold for Meh (Ctrl+Alt+Shift)
#define SFT_BSP SFT_T(KC_BSPC) // Tap for Backspace, hold for Shift
#define SFT_ENT SFT_T(KC_ENT)  // Tap for Enter, hold for Shift
#define SFT_SPC SFT_T(KC_SPC)  // Tap for Space, hold for Shift
#define UMLAUT  RALT(KC_U)     // Combine Alt and U

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)


  MACRO IDEA

  LCA(KC_TAB) (opens thumnails of apps
  LT(_NAV) (toggle nav layer) with arrows and hjkl
  jump back to default after select?

  LED IDEAS

  use below functions to show a light meter for volume and other stuff on bottom row
  rgblight_setrgb(r, g, b);  // where r/g/b is a number from 0..255.  Turns all the LEDs to this color
  rgblight_sethsv(h, s, v);  // HSV color control
  rgblight_setrgb_at(r,g,b, LED);  // control a single LED.  0 <= LED < RGBLED_NUM
  rgblight_sethsv_at(h,s,v, LED);  // control a single LED.  0 <= LED < RGBLED_NUM
gg

  case CPYPST:                                    // One key copy/paste
          if(record->event.pressed){
              key_timer = timer_read();
          } else {
              if (timer_elapsed(key_timer) > 152) {   // Hold, copy
                  register_code(KC_LCTL);
                  tap(KC_C);
                  unregister_code(KC_LCTL);
                  #ifdef AUDIO_ENABLE
                      PLAY_SONG(tone_copy);
                  #endif
              } else {                                // Tap, paste
                  register_code(KC_LCTL);
                  tap(KC_V);
                  unregister_code(KC_LCTL);
                  #ifdef AUDIO_ENABLE
                      PLAY_SONG(tone_paste);
                  #endif
              }
          }
  return false;



from clueboard magicmonty

void clueboard_set_led(uint8_t id, uint8_t val) {
  switch (id) {
    case LAYER_BASE:
      rgblight_sethsv_noeeprom(190, 255, val);
      break;
    case LAYER_FUNCTION:
      rgblight_sethsv_noeeprom(46, 255, val);
      break;
    case LAYER_MEDIA:
      rgblight_sethsv_noeeprom(86, 255, val);
      break;
    case LAYER_CONTROL:
      rgblight_sethsv_noeeprom(346, 255, val);
      break;
    case LAYER_MOUSE:
      rgblight_sethsv_noeeprom(206, 255, val);
      break;
#if defined(MIDI_ENABLE)
    case LAYER_MIDI:
      rgblight_sethsv_noeeprom(316, 255, val);
      break;
#endif
  }
};





const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {

      case KC_MAKE: {
       if (!record->event.pressed) {
         SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
         #if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
           ":dfu"
         #endif
       }
       return false; break;
      }

      case VERS: {
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP ":v" KEYMAP_REV " @ " QMK_VERSION);
        }
        return false; break;
      }

      case TIL_SLASH: {
        if (record->event.pressed) {
          SEND_STRING ("~/.");
        }
        return false; break;
      }

      case DEREF: {
        if (record->event.pressed) {
          SEND_STRING ("->");
        }
        return false; break;
      }

      case EQRIGHT: {
        if (record->event.pressed) {
          SEND_STRING ("=>");
        }
        return false; break;
      }

      case EPRM: {
        if (record->event.pressed) {
          eeconfig_init();
        }
        return false; break;
      }
    return MACRO_NONE;
};




#define RGBLIGHT_ANIMATIONS

#ifdef RGBLIGHT_ANIMATIONS



  ifdef RGBLIGHT_LAYERS
    #define RGBLIGHT_COLOR_LAYER_0 0x00, 0x00, 0xFF
    #define RGBLIGHT_COLOR_LAYER_1 0x00, 0x00, 0xFF
    #define RGBLIGHT_COLOR_LAYER_2 0xFF, 0x00, 0x00
    #define RGBLIGHT_COLOR_LAYER_3 0x00, 0xFF, 0x00
    #define RGBLIGHT_COLOR_LAYER_4 0xFF, 0xFF, 0x00
    #define RGBLIGHT_COLOR_LAYER_5 0x00, 0xFF, 0xFF
    #define RGBLIGHT_COLOR_LAYER_6 0xFF, 0x00, 0xFF
    #define RGBLIGHT_COLOR_LAYER_7 0xFF, 0xFF, 0xFF
  #endif
#endif


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



-------------------------------------------- FROM GORDON



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


static xtap htap_state = {
  .is_press_action = true,
  .state = 0
};

void h_finished (qk_tap_dance_state_t *state, void *user_data) {
  htap_state.state = cur_dance(state);
  switch (htap_state.state) {
    case SINGLE_TAP: register_code(KC_H); break;
    case SINGLE_HOLD: layer_on(8); register_code(KC_LALT); break;
    case DOUBLE_TAP: layer_invert(8); register_code(KC_LALT); break;
    // case DOUBLE_HOLD: register_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: register_code(KC_H);unregister_code(KC_H);register_code(KC_H);
  }
}

void h_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (htap_state.state) {
    case SINGLE_TAP: unregister_code(KC_H); break;
    case SINGLE_HOLD: layer_off(8); unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_LALT);break;
    // case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_H);
  }
  htap_state.state = 0;
}


/**************** QUAD FUNCTION FOR TAB ****************/
// TAB, ALT + SHIFT, TAB TAB, CTRL + SHIFT
static xtap tab_state = {
  .is_press_action = true,
  .state = 0
 };

void tab_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_TAB); break;  //send tab on single press
    case SINGLE_HOLD: register_ctrl_shift(); break;
    case DOUBLE_HOLD: register_alt_shift(); break; //alt shift on single hold
    case DOUBLE_TAP: register_code(KC_TAB); unregister_code(KC_TAB); register_code(KC_TAB); break; //tab tab
    case TRIPLE_TAP: register_code(KC_LSHIFT) ;register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSHIFT); register_code(KC_LGUI); break;
  }
}

void tab_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_TAB); break; //unregister tab
    case DOUBLE_HOLD: unregister_alt_shift(); break; //let go of alt shift
    case DOUBLE_TAP: unregister_code(KC_TAB); break;
    case SINGLE_HOLD: unregister_ctrl_shift(); break;
    case TRIPLE_TAP: unregister_code(KC_LSHIFT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSHIFT); unregister_code(KC_LGUI); break;
  }
  tab_state.state = 0;
}
/**************** QUAD FUNCTION FOR TAB ****************/

//*************** SUPER COMMA *******************//
// Assumption: we don't care about trying to hit ,, quickly
//*************** SUPER COMMA *******************//
static xtap comma_state = {
  .is_press_action = true,
  .state = 0
};

void comma_finished (qk_tap_dance_state_t *state, void *user_data) {
  comma_state.state = hold_cur_dance(state); //Use the dance that favors being held
  switch (comma_state.state) {
    case SINGLE_TAP: register_code(KC_COMMA); break;
    case SINGLE_HOLD: layer_on(1); break; //turn on symbols layer
    case DOUBLE_TAP: layer_invert(4); break; //toggle numbers layer
    case DOUBLE_HOLD: layer_on(2); break;
    case TRIPLE_TAP: register_code(KC_CALCULATOR); break;
    case TRIPLE_HOLD: layer_on(3);
  }
}

void comma_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (comma_state.state) {
    case SINGLE_TAP: unregister_code(KC_COMMA); break; //unregister comma
    case SINGLE_HOLD: layer_off(1); break;
    case DOUBLE_TAP: ;break;
    case DOUBLE_HOLD: layer_off(2); break;
    case TRIPLE_TAP: unregister_code(KC_CALCULATOR); break;
    case TRIPLE_HOLD: layer_off(3);
  }
  comma_state.state = 0;
}
//*************** SUPER COMMA *******************//P
//*************** SUPER COMMA *******************//


//*************** F3 TAP DANCE *******************//
//Good example for accessing multiple layers from the same key.
static xtap S1_state = {
  .is_press_action = true,
  .state = 0
};

void bt_finished (qk_tap_dance_state_t *state, void *user_data) {
  S1_state.state = cur_dance(state);
  switch (S1_state.state) {
    case SINGLE_TAP: register_code(KC_F3); break;
    case SINGLE_HOLD: layer_on(4); break;
    case DOUBLE_TAP: layer_invert(4); break;
    case DOUBLE_HOLD: layer_on(5); break;
    case DOUBLE_SINGLE_TAP: layer_invert(4); break;
  }
}

void bt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (S1_state.state) {
    case SINGLE_TAP: unregister_code(KC_F3); break;
    case SINGLE_HOLD: layer_off(4); break;
    case DOUBLE_TAP: break; //already inverted. Don't do anything.
    case DOUBLE_HOLD: layer_off(5); break;
    case DOUBLE_SINGLE_TAP: break;
  }
  S1_state.state = 0;
}

_______________________________________________________________________
