#include QMK_KEYBOARD_H

#ifdef SELECT_WORD_ENABLE
#    include "../../../../../features/select_word.h"
#endif // SELECT_WORD_ENABLE
#ifdef KEYCODE_STRING_ENABLE
#    include "../../../../../features/keycode_string.h"
#endif
#ifndef NO_DEBUG
#    include "print.h"
#endif // NO_DEBUG

enum layers { BASE, NAV, MOUSE, NUM, MEDIA, SYM, FUN, GAME, LAYER_COUNT };
enum {
    TD_BOOT,
    TD_BASE,
    TD_NUM,
    TD_NAV,
    TD_MOUSE,
    TD_MEDIA,
    TD_SYM,
    TD_FUN,
    TD_GAME,
    TD_COUNT, // keep last
};

// Helper to compute the current effective layer.
static inline uint8_t effective_layer_state(layer_state_t st) {
    return get_highest_layer(st | default_layer_state);
}
static inline uint8_t effective_layer_now(void) {
    return effective_layer_state(layer_state);
}

// Replace the per-layer tap-dance functions with a single macro.
#define TD_SET_DEF_FN(fname, target_layer)                  \
    void fname(tap_dance_state_t* state, void* user_data) { \
        if (state->count == 2) {                            \
            default_layer_set(1UL << (target_layer));       \
        }                                                   \
    }

void u_td_fn_boot(tap_dance_state_t* state, void* user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
}

// Generate all layer-switch TD handlers.
TD_SET_DEF_FN(u_td_fn_U_BASE, BASE)
TD_SET_DEF_FN(u_td_fn_U_NAV, NAV)
TD_SET_DEF_FN(u_td_fn_U_MOUSE, MOUSE)
TD_SET_DEF_FN(u_td_fn_U_MEDIA, MEDIA)
TD_SET_DEF_FN(u_td_fn_U_NUM, NUM)
TD_SET_DEF_FN(u_td_fn_U_SYM, SYM)
TD_SET_DEF_FN(u_td_fn_U_FUN, FUN)
TD_SET_DEF_FN(u_td_fn_U_GAME, GAME)

enum custom_keycodes {
    ALT_MOD = SAFE_RANGE,
// Macros invoked through the Magic key.
#ifdef SELECT_WORD_ENABLE
    SELLINE,
    SELWBAK,
    SELWFWD,
#endif // SELECT_WORD_ENABLE
};

bool alt_mod_active = false;

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // key is not assigned
#define U_NU KC_NO // key is not used

#define U_RDO C(S(KC_Z))
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// Define the mod-tap keys for the home row
#define HRM_A LALT_T(KC_A)
#define HRM_R LGUI_T(KC_R)
#define HRM_S LSFT_T(KC_S)
#define HRM_T LCTL_T(KC_T)

#define HRM_N LCTL_T(KC_N)
#define HRM_E RSFT_T(KC_E)
#define HRM_I LGUI_T(KC_I)
#define HRM_O LALT_T(KC_O)

#define TME_ESC LT(MEDIA, KC_ESC)
#define TN_SPC LT(NAV, KC_SPC)
#define TMO_TAB LT(MOUSE, KC_TAB)

#define TS_ENT LT(SYM, KC_ENT)
#define TN_BSP LT(NUM, KC_BSPC)
#define TF_DEL LT(FUN, KC_DEL)

// clang-format off
#ifdef KEYCODE_STRING_ENABLE
KEYCODE_STRING_NAMES_USER(
        KEYCODE_STRING_NAME(ALT_MOD),
#    ifdef SELECT_WORD_ENABLE
        KEYCODE_STRING_NAME(SELLINE),
        KEYCODE_STRING_NAME(SELWBAK),
        KEYCODE_STRING_NAME(SELWFWD),
#    endif // SELECT_WORD_ENABLE
        KEYCODE_STRING_NAME(HRM_A),
        KEYCODE_STRING_NAME(HRM_R),
        KEYCODE_STRING_NAME(HRM_S),
        KEYCODE_STRING_NAME(HRM_T),
        KEYCODE_STRING_NAME(HRM_N),
        KEYCODE_STRING_NAME(HRM_E),
        KEYCODE_STRING_NAME(HRM_I),
        KEYCODE_STRING_NAME(HRM_O),
        KEYCODE_STRING_NAME(TME_ESC),
        KEYCODE_STRING_NAME(TN_SPC),
        KEYCODE_STRING_NAME(TMO_TAB),
        KEYCODE_STRING_NAME(TS_ENT),
        KEYCODE_STRING_NAME(TN_BSP),
        KEYCODE_STRING_NAME(TF_DEL));
#endif // KEYCODE_STRING_ENABLE
// clang-format on

#ifndef NO_DEBUG
static const char* const LAYER_NAMES[LAYER_COUNT] = {"BASE", "NAV", "MOUSE", "MEDIA", "NUM", "SYM", "FUN", "GAME"};
_Static_assert(LAYER_COUNT == (sizeof(LAYER_NAMES) / sizeof(LAYER_NAMES[0])), "Update LAYER_NAMES when layers change.");
#endif // NO_DEBUG

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT,    U_NA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    HRM_A,   HRM_R,   HRM_S,   HRM_T,   KC_D,                         KC_H,   HRM_N,   HRM_E,   HRM_I,   HRM_O,    U_NA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_X,    KC_C,    KC_V,    KC_B,    KC_Z,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,    U_NA,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        TME_ESC,  TN_SPC,  TMO_TAB,      TS_ENT,  TN_BSP,   TF_DEL
                                      //`--------------------------'  `--------------------------'

  ),

    [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TAB,TD(TD_BOOT), TD(TD_NAV), TD(TD_GAME), TD(TD_BASE), U_NA,            U_RDO,   U_PST,   U_CPY,   U_CUT,  U_UND,    U_NA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_LCTL,    U_NA,                    CW_TOGG, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,  U_NA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, U_NA, KC_ALGR, TD(TD_NUM), TD(TD_NAV), U_NA,                    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  U_NA,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            U_NA,     U_NA,    U_NA,     KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

    [MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TAB,TD(TD_BOOT), TD(TD_NAV), TD(TD_GAME), TD(TD_BASE), U_NA,            U_RDO, U_PST,   U_CPY,   U_CUT,  U_UND,   U_NA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_LCTL,    U_NA,                      U_NA, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, U_NA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT, U_NA, KC_ALGR, TD(TD_SYM), TD(TD_MOUSE), U_NA,                    U_NA, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, U_NA,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            U_NA,     U_NA,    U_NA,   MS_BTN2, MS_BTN1, MS_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

    [MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        U_NA,     TD(TD_BOOT), TD(TD_NAV),  TD(TD_GAME), TD(TD_BASE), U_NA,         UG_TOGG, U_NU,     U_NU,     U_NU,     U_NU,     U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+---------+---------+---------+---------+--------|
        U_NA,     KC_LALT,    KC_LGUI,     KC_LSFT,    KC_LCTL,    U_NA,            U_NU,    KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+---------+---------+---------+---------+--------|
        U_NA,     DB_TOGG,    KC_ALGR,     TD(TD_FUN), TD(TD_MEDIA), U_NA,          OU_AUTO, U_NU,     U_NU,     U_NU,     U_NU,     U_NA,
  //|--------+------------+-----------+-----------+-----------+--------+--------|  |-----------+---------+---------+---------+---------+--------|
                                            U_NA,     U_NA,     U_NA,      KC_MSTP, KC_MPLY, KC_MUTE
                                      //`--------------------------'  `--------------------------'
    ),

    // Added: NUM layer (mirrors LAYOUT_60_ansi rules)
    [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        U_NA,     KC_LBRC,    KC_7,        KC_8,        KC_9,        KC_RBRC,       U_NA,    TD(TD_BASE), TD(TD_GAME), TD(TD_NAV), TD(TD_BOOT), U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+------------+------------+------------+------------+--------|
        U_NA,     KC_SCLN,    KC_4,        KC_5,        KC_6,        KC_EQL,        U_NA,    KC_LCTL,     KC_LSFT,     KC_LGUI,     KC_LALT,     U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+------------+------------+------------+------------+--------|
        U_NA,     KC_GRV,     KC_1,        KC_2,        KC_3,        KC_BSLS,       U_NA,    TD(TD_NUM),  TD(TD_NAV),  KC_ALGR,     U_NA,        U_NA,
  //|--------+------------+-----------+-----------+-----------+--------+--------|  |-----------+------------+------------+------------+------------+--------|
                                            KC_DOT,    KC_0,     KC_MINS,    U_NA,    U_NA,       U_NA
                                      //`--------------------------'  `--------------------------'
    ),

    // Added: SYM layer (mirrors LAYOUT_60_ansi rules)
    [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        U_NA,     KC_LCBR,    KC_AMPR,     KC_ASTR,     KC_LPRN,     KC_RCBR,       U_NA,    TD(TD_BASE), TD(TD_GAME), TD(TD_NAV), TD(TD_BOOT), U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+------------+------------+------------+------------+--------|
        U_NA,     KC_COLN,    KC_DLR,      KC_PERC,     KC_CIRC,     KC_PLUS,       U_NA,    KC_LCTL,     KC_LSFT,     KC_LGUI,     KC_LALT,     U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+------------+------------+------------+------------+--------|
        U_NA,     KC_TILD,    KC_EXLM,     KC_AT,       KC_HASH,     KC_PIPE,       U_NA,    TD(TD_NUM),  TD(TD_NAV),  KC_ALGR,     U_NA,        U_NA,
  //|--------+------------+-----------+-----------+-----------+--------+--------|  |-----------+------------+------------+------------+------------+--------|
                                            KC_LPRN,   KC_RPRN,  KC_UNDS,    U_NA,    U_NA,       U_NA
                                      //`--------------------------'  `--------------------------'
    ),

    // Added: FUN layer (mirrors LAYOUT_60_ansi rules)
    [FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        U_NA,     KC_F12,     KC_F7,       KC_F8,       KC_F9,       KC_PSCR,       U_NA,    TD(TD_BASE), TD(TD_GAME), TD(TD_NAV), TD(TD_BOOT), U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+------------+------------+------------+------------+--------|
        U_NA,     KC_F11,     KC_F4,       KC_F5,       KC_F6,       KC_SCRL,       U_NA,    KC_LCTL,     KC_LSFT,     KC_LGUI,     KC_LALT,     U_NA,
  //|--------+------------+-----------+-----------+-----------+--------|      |-----------+------------+------------+------------+------------+--------|
        U_NA,     KC_F10,     KC_F1,       KC_F2,       KC_F3,       KC_PAUS,       U_NA,    TD(TD_FUN),  TD(TD_MEDIA), KC_ALGR,     U_NA,        U_NA,
  //|--------+------------+-----------+-----------+-----------+--------+--------|  |-----------+------------+------------+------------+------------+--------|
                                            KC_APP,    KC_SPC,   KC_TAB,     U_NA,    U_NA,       U_NA
                                      //`--------------------------'  `--------------------------'
    )
};

// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [1] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [2] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [3] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
};
#endif

///////////////////////////////////////////////////////////////////////////////
// Combos (https://docs.qmk.fm/features/combo)
///////////////////////////////////////////////////////////////////////////////
enum combo_events {
    CB_TNBSP_TFDEL_BASE,
    COMBO_EVENTS_COUNT, // keep last
};

const uint16_t PROGMEM thumbcombos_base_right[] = {LT(SYM, KC_ENT), LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[]  = {LT(NAV, KC_SPC), LT(MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_G_r[]   = {TN_BSP, TF_DEL, COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[]        = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[]      = {MS_BTN2, MS_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[]      = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[]        = {KC_0, KC_MINS, COMBO_END};
const uint16_t PROGMEM thumbcombos_sym[]        = {KC_RPRN, KC_UNDS, COMBO_END};
const uint16_t PROGMEM thumbcombos_fun[]        = {KC_SPC, KC_TAB, COMBO_END};
combo_t                key_combos[]             = {
    [CB_TNBSP_TFDEL_BASE] = COMBO_ACTION(thumbcombos_base_G_r), COMBO(thumbcombos_base_right, LT(FUN, KC_DEL)), COMBO(thumbcombos_base_left, LT(MEDIA, KC_ESC)), COMBO(thumbcombos_nav, KC_DEL), COMBO(thumbcombos_mouse, MS_BTN3), COMBO(thumbcombos_media, KC_MUTE), COMBO(thumbcombos_num, KC_DOT), COMBO(thumbcombos_sym, KC_LPRN), COMBO(thumbcombos_fun, KC_APP),
};
_Static_assert(COMBO_EVENTS_COUNT <= ARRAY_SIZE(key_combos), "key_combos[] missing COMBO_ACTION entries for some combo events.");

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CB_TNBSP_TFDEL_BASE:
            if (pressed) {
                default_layer_set((layer_state_t)1 << BASE);
            }
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/tap_hold)
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case HRM_S:
        case HRM_E:
            return TAPPING_TERM - 35;
        default:
            return TAPPING_TERM;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Caps word (https://docs.qmk.fm/features/caps_word)
///////////////////////////////////////////////////////////////////////////////
#ifdef CAPS_WORD_ENABLE
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT_LSHIFT);
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_COLN:
            return true;
        default:
            return false;
    }
}
#endif // CAPS_WORD_ENABLE

///////////////////////////////////////////////////////////////////////////////
// RGB Matrix Lighting (https://docs.qmk.fm/features/rgb_matrix)
///////////////////////////////////////////////////////////////////////////////
#if RGB_MATRIX_ENABLE
static void set_layer_color(uint8_t led_min, uint8_t led_max, uint8_t layer, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index == NO_LED || index < led_min || index >= led_max) {
                continue;
            }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (kc > KC_TRNS) {
                rgb_matrix_set_color(index, red, green, blue);
            } else {
                rgb_matrix_set_color(index, RGB_OFF);
            }
        }
    }
}

static const uint8_t LAYER_RGB[LAYER_COUNT][3] = {
    {RGB_WHITE},  // BASE
    {RGB_BLUE},   // NAV
    {RGB_YELLOW}, // MOUSE
    {RGB_PURPLE}, // MEDIA
    {RGB_PINK},   // NUM
    {RGB_GREEN},  // SYM
    {RGB_RED},    // FUN
    {RGB_OFF},    // GAME
};
_Static_assert(LAYER_COUNT == (sizeof(LAYER_RGB) / sizeof(LAYER_RGB[0])), "Update LAYER_RGB when layers change.");

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = effective_layer_now();
    uint8_t idx   = (layer < LAYER_COUNT) ? layer : BASE;
    set_layer_color(led_min, led_max, layer, LAYER_RGB[idx][0], LAYER_RGB[idx][1], LAYER_RGB[idx][2]);
    return false;
}
#endif // RGB_MATRIX_ENABLE

#ifndef NO_DEBUG
// Log effective (momentary | default) layer in callbacks.
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t     layer = effective_layer_state(state);
    const char* name  = (layer < LAYER_COUNT) ? LAYER_NAMES[layer] : "?";
    dprintf("Layer changed: %u (%s)\n", layer, name);
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    uint8_t     layer = effective_layer_state(state);
    const char* name  = (layer < LAYER_COUNT) ? LAYER_NAMES[layer] : "?";
    dprintf("Default layer changed: %u (%s)\n", layer, name);
    return state;
}
#endif // NO_DEBUG

///////////////////////////////////////////////////////////////////////////////
// User functions
///////////////////////////////////////////////////////////////////////////////
void keyboard_post_init_user(void) {
#ifndef NO_DEBUG
    debug_enable   = true;
    debug_keyboard = true;
#endif // NO_DEBUG
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef SELECT_WORD_ENABLE
    if (!process_select_word(keycode, record)) {
        return false;
    }
#endif // SELECT_WORD_ENABLE
#ifndef NO_DEBUG
    if (record->event.pressed) {
        uint8_t     layer = effective_layer_now();
        const char* name  = (layer < LAYER_COUNT) ? LAYER_NAMES[layer] : "?";
        dprintf("Layer: %u (%s)\n", layer, name);
#    ifdef KEYCODE_STRING_ENABLE
        dprintf("kc: %s\n", get_keycode_string(keycode));
#    else
        dprintf("kc: 0x%04X\n", keycode);
#    endif
    }
#endif // NO_DEBUG

    switch (keycode) {
        case ALT_MOD:
            if (record->event.pressed) {
                alt_mod_active = true;
                register_mods(MOD_BIT_LALT);
            } else {
                alt_mod_active = false;
                unregister_mods(MOD_BIT_LALT);
            }
            return false;

        case KC_COMM:
            if (alt_mod_active && record->event.pressed) {
                tap_code(KC_TAB); // Alt+Tab
                return false;
            }
            break;

        case KC_M:
            if (alt_mod_active && record->event.pressed) {
                register_mods(MOD_BIT_LSHIFT);
                tap_code(KC_TAB); // Shift+Alt+Tab
                unregister_mods(MOD_BIT_LSHIFT);
                return false;
            }
            break;

#ifdef SELECT_WORD_ENABLE
        case SELWBAK:
            if (record->event.pressed)
                select_word_register('B');
            else
                select_word_unregister();
            break;
        case SELWFWD:
            if (record->event.pressed)
                select_word_register('W');
            else
                select_word_unregister();
            break;
        case SELLINE:
            if (record->event.pressed)
                select_word_register('L');
            else
                select_word_unregister();
            break;
#endif // SELECT_WORD_ENABLE
    }
    return true;
}
// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
    [TD_BASE] = ACTION_TAP_DANCE_FN(u_td_fn_U_BASE),
    [TD_NUM] = ACTION_TAP_DANCE_FN(u_td_fn_U_NUM),
    [TD_MOUSE] = ACTION_TAP_DANCE_FN(u_td_fn_U_MOUSE),
    [TD_MEDIA] = ACTION_TAP_DANCE_FN(u_td_fn_U_MEDIA),
    [TD_SYM] = ACTION_TAP_DANCE_FN(u_td_fn_U_SYM),
    [TD_FUN] = ACTION_TAP_DANCE_FN(u_td_fn_U_FUN),
    [TD_GAME] = ACTION_TAP_DANCE_FN(u_td_fn_U_GAME),
    [TD_NAV] = ACTION_TAP_DANCE_FN(u_td_fn_U_NAV),
};
// clang-format on
_Static_assert(TD_COUNT == ARRAY_SIZE(tap_dance_actions), "Add tap_dance_actions entries for all TD_* IDs.");

void housekeeping_task_user(void) {
#ifdef SELECT_WORD_ENABLE
    select_word_task();
#endif // SELECT_WORD_ENABLE
}
