#ifndef CONFIG_H
#define CONFIG_H

#include "config.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2260
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDFans
#define PRODUCT         DZ60
#define DESCRIPTION     DZ60 Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { F0, F1, E6, C7, C6, B7, D4, B1, B0, B5, B4, D7, D6, B3, F4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 5

/* Set 0 if debou#46e4e4ncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#define RGB_DI_PIN E2
#define RGBLED_NUM 16

#ifdef RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_EFFECT_BREATHE_CENTER 	1.85     	// Used to calculate the curve for the breathing animation. Valid values 1.0-2.7.
  #define RGBLIGHT_EFFECT_BREATHE_MAX 	  255      	// The maximum brightness for the breathing mode. Valid values 1-255.
  #define RGBLIGHT_EFFECT_SNAKE_LENGTH 	  3         // The number of LEDs to light up for the "snake" animation.
  #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 	4        	// The number of LEDs to light up for the "knight" animation.
  #define RGBLIGHT_EFFECT_KNIGHT_OFFSET 	4       	// Start the knight animation this many LEDs from the start of the strip.
  #define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 	4 	      // The number of LEDs to have the "knight" animation travel.
  #define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 	1000 	// How long to wait between light changes for the "christmas" animation. Specified in ms.
  #define RGBLIGHT_EFFECT_CHRISTMAS_STEP 	1 	      // How many LED's to group the red/green colors by for the christmas mode.
#endif

#ifdef AUTO_SHIFT_ENABLE
  /* sets 'Auto Shift' timeouts */
  #define AUTO_SHIFT_TIMEOUT 150
  #define NO_AUTO_SHIFT_SPECIAL
#endif

#if TAP_DANCE_ENABLE
  /* tap Dance timeout */
  #define TAPPING_TERM 200
  #define TAPPING_TOGGLE  1
#endif

#if MOUSEKEY_ENABLE
  #define MOUSEKEY_INTERVAL 10          //  how long to wait between each movement report
  #define MOUSEKEY_DELAY 100            // delay between button press and the cursor moving
  #define MOUSEKEY_TIME_TO_MAX 40       // how quickly your cursor will accelerate to max
  #define MOUSEKEY_MAX_SPEED 8          // overall speed
  #define MOUSEKEY_WHEEL_DELAY 0        // like above but for the wheel movement
  #define MOUSEKEY_WHEEL_MAX_SPEED 8    // like above but for the wheel movement
  #define MOUSEKEY_WHEEL_TIME_TO_MAX 40 // how quickly scrolling will accelerate to max
#endif

//GAVE_ESC
// #define GRAVE_ESC_ALT_OVERRIDE   // if ALT is pressed, ESC is always sent
// #define GRAVE_ESC_CTRL_OVERRIDE  // if CTRL is pressed, ESC is always sent
// #define GRAVE_ESC_GUI_OVERRIDE   // if GUI is pressed, ESC is always sent
// #define GRAVE_ESC_SHIFT_OVERRIDE // if SHIFT is pressed, ESC is always sent

#define NO_DEBUG
#define NO_PRINT
#define USER_PRINT

// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION

#undef RGBLIGHT_ANIMATIONS
#define PREVENT_STUCK_MODIFIERS
#define DYNAMIC_MACRO_SIZE 128
#define TAPPING_TERM 300
// #define RETRO_TAPPING // tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
#define TAPPING_TOGGLE 1
// #define PERMISSIVE_HOLD
#define LEADER_TIMEOUT 300
#define ONESHOT_TIMEOUT 1000
// #define ONESHOT_TAP_TOGGLE 2
// #define IGNORE_MOD_TAP_INTERRUPT // makes it possible to do rolling combos (zx) with keys that convert to other keys on hold
// #define QMK_KEYS_PER_SCAN 4

#endif
