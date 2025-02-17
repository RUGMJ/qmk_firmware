#include QMK_KEYBOARD_H
#include "raw_hid.h"

enum LAYERS {
    _BASE,
    _SYMBOL,
    _NUMBER,
    _NAV,
    _MEDIA,
    _FUNCTION,
};

#define KC_LEFT_THUMB_1 LT(_NAV, KC_SPC)
#define KC_LEFT_THUMB_2 KC_ESC
#define KC_RIGHT_THUMB_1 LT(_SYMBOL, KC_ENTER)
#define KC_RIGHT_THUMB_2 LT(_NUMBER, KC_BSPC)

const uint16_t PROGMEM left_dual_thumb[] = {KC_LEFT_THUMB_1, KC_LEFT_THUMB_2, COMBO_END};
const uint16_t PROGMEM right_dual_thumb[] = {KC_RIGHT_THUMB_1, KC_RIGHT_THUMB_2, COMBO_END};
combo_t key_combos[] = {
    COMBO(left_dual_thumb, LT(_MEDIA, KC_TAB)),
    COMBO(right_dual_thumb, LT(_FUNCTION, KC_NO)), // TODO: decide what I want this to do
};

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);

    uint8_t data[32] = {0};

    data[0] = 0x01; // Type indicator for layer change
    data[1] = current_layer;

    raw_hid_send(data, sizeof(data));

    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────┬───────────┬───────────┬──────────────┬──────────────┐   ┌──────────────┬──────────────┬───────────┬───────────┬───────────┐
//    │     q     │     w     │     e     │      r       │      t       │   │      y       │      u       │     i     │     o     │     p     │
//    ├───────────┼───────────┼───────────┼──────────────┼──────────────┤   ├──────────────┼──────────────┼───────────┼───────────┼───────────┤
//    │ LGUI_T(a) │ LALT_T(s) │ LCTL_T(d) │  LSFT_T(f)   │      g       │   │      h       │  LSFT_T(j)   │ LCTL_T(k) │ LALT_T(l) │ LGUI_T(') │
//    ├───────────┼───────────┼───────────┼──────────────┼──────────────┤   ├──────────────┼──────────────┼───────────┼───────────┼───────────┤
//    │     z     │     x     │     c     │      v       │      b       │   │      n       │      m       │     ,     │     .     │     /     │
//    └───────────┴───────────┴───────────┼──────────────┼──────────────┤   ├──────────────┼──────────────┼───────────┴───────────┴───────────┘
//                                        │ left_THUMB_1 │ left_THUMB_2 │   │ rght_THUMB_1 │ rght_THUMB_2 │
//                                        └──────────────┴──────────────┘   └──────────────┴──────────────┘
[_BASE] = LAYOUT_split_3x5_2(
  KC_Q         , KC_W         , KC_E         , KC_R            , KC_T            ,     KC_Y             , KC_U             , KC_I         , KC_O         , KC_P            ,
  LGUI_T(KC_A) , LALT_T(KC_S) , LCTL_T(KC_D) , LSFT_T(KC_F)    , KC_G            ,     KC_H             , LSFT_T(KC_J)     , LCTL_T(KC_K) , LALT_T(KC_L) , LGUI_T(KC_QUOTE),
  KC_Z         , KC_X         , KC_C         , KC_V            , KC_B            ,     KC_N             , KC_M             , KC_COMM      , KC_DOT       , KC_SLSH         ,
                                               KC_LEFT_THUMB_1 , KC_LEFT_THUMB_2 ,     KC_RIGHT_THUMB_1 , KC_RIGHT_THUMB_2
),

//    ┌───┬───┬───┬───┬───┐   ┌─────┬─────┬─────┬─────┬───────────────┐
//    │ { │ & │ * │ ( │ } │   │     │     │     │     │ QK_LAYER_LOCK │
//    ├───┼───┼───┼───┼───┤   ├─────┼─────┼─────┼─────┼───────────────┤
//    │ : │ $ │ % │ ^ │ + │   │     │     │     │     │               │
//    ├───┼───┼───┼───┼───┤   ├─────┼─────┼─────┼─────┼───────────────┤
//    │ ~ │ ! │ @ │ # │ | │   │     │     │     │     │               │
//    └───┴───┴───┼───┼───┤   ├─────┼─────┼─────┴─────┴───────────────┘
//                │ ) │ _ │   │     │     │
//                └───┴───┘   └─────┴─────┘
[_SYMBOL] = LAYOUT_split_3x5_2(
  KC_LEFT_CURLY_BRACE , KC_AMPERSAND , KC_ASTERISK , KC_LEFT_PAREN  , KC_RIGHT_CURLY_BRACE ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , QK_LAYER_LOCK,
  KC_COLON            , KC_DOLLAR    , KC_PERCENT  , KC_CIRCUMFLEX  , KC_PLUS              ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,
  KC_TILDE            , KC_EXCLAIM   , KC_AT       , KC_HASH        , KC_PIPE              ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,
                                                     KC_RIGHT_PAREN , KC_UNDERSCORE        ,     KC_TRNS , KC_TRNS
),

//    ┌───┬───┬───┬───┬───┐   ┌─────┬─────┬─────┬─────┬───────────────┐
//    │ [ │ 7 │ 8 │ 9 │ ] │   │     │     │     │     │ QK_LAYER_LOCK │
//    ├───┼───┼───┼───┼───┤   ├─────┼─────┼─────┼─────┼───────────────┤
//    │ ; │ 4 │ 5 │ 6 │ = │   │     │     │     │     │               │
//    ├───┼───┼───┼───┼───┤   ├─────┼─────┼─────┼─────┼───────────────┤
//    │ ` │ 1 │ 2 │ 3 │ \ │   │     │     │     │     │               │
//    └───┴───┴───┼───┼───┤   ├─────┼─────┼─────┴─────┴───────────────┘
//                │ 0 │ - │   │     │     │
//                └───┴───┘   └─────┴─────┘
[_NUMBER] = LAYOUT_split_3x5_2(
  KC_LEFT_BRACKET , KC_7 , KC_8 , KC_9 , KC_RIGHT_BRACKET ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , QK_LAYER_LOCK,
  KC_SCLN         , KC_4 , KC_5 , KC_6 , KC_EQUAL         ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,
  KC_GRAVE        , KC_1 , KC_2 , KC_3 , KC_BACKSLASH     ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,
                                  KC_0 , KC_MINUS         ,     KC_TRNS , KC_TRNS
),

//    ┌───────────────┬─────┬─────┬─────┬─────┐   ┌─────┬──────┬──────┬──────┬──────┐
//    │ QK_LAYER_LOCK │     │     │     │     │   │     │      │      │      │      │
//    ├───────────────┼─────┼─────┼─────┼─────┤   ├─────┼──────┼──────┼──────┼──────┤
//    │               │     │     │     │     │   │     │ left │ down │  up  │ rght │
//    ├───────────────┼─────┼─────┼─────┼─────┤   ├─────┼──────┼──────┼──────┼──────┤
//    │               │     │     │     │     │   │     │      │ pgdn │ pgup │      │
//    └───────────────┴─────┴─────┼─────┼─────┤   ├─────┼──────┼──────┴──────┴──────┘
//                                │     │     │   │     │      │
//                                └─────┴─────┘   └─────┴──────┘
[_NAV] = LAYOUT_split_3x5_2(
  QK_LAYER_LOCK , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS   , KC_TRNS , KC_TRNS ,
  KC_TRNS       , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_LEFT , KC_DOWN   , KC_UP   , KC_RIGHT,
  KC_TRNS       , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_PGDN , KC_PGUP , KC_TRNS ,
                                      KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS
),

//    ┌───────────────┬─────┬─────┬─────┬─────┐   ┌──────┬──────┬──────┬──────┬──────┐
//    │ QK_LAYER_LOCK │     │     │     │     │   │      │      │      │      │      │
//    ├───────────────┼─────┼─────┼─────┼─────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │               │     │     │     │     │   │      │ mprv │ vold │ volu │ mnxt │
//    ├───────────────┼─────┼─────┼─────┼─────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │               │     │     │     │     │   │      │      │      │      │      │
//    └───────────────┴─────┴─────┼─────┼─────┤   ├──────┼──────┼──────┴──────┴──────┘
//                                │     │     │   │ mute │ mply │
//                                └─────┴─────┘   └──────┴──────┘
[_MEDIA] = LAYOUT_split_3x5_2(
  QK_LAYER_LOCK , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS       , KC_TRNS             , KC_TRNS           , KC_TRNS         , KC_TRNS            ,
  KC_TRNS       , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS       , KC_MEDIA_PREV_TRACK , KC_AUDIO_VOL_DOWN , KC_AUDIO_VOL_UP , KC_MEDIA_NEXT_TRACK,
  KC_TRNS       , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS       , KC_TRNS             , KC_TRNS           , KC_TRNS         , KC_TRNS            ,
                                      KC_TRNS , KC_TRNS ,     KC_AUDIO_MUTE , KC_MEDIA_PLAY_PAUSE
),

//    ┌─────┬────┬────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬───────────────┐
//    │ f12 │ f7 │ f8 │ f9  │ f15 │   │     │     │     │     │ QK_LAYER_LOCK │
//    ├─────┼────┼────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼───────────────┤
//    │ f11 │ f4 │ f5 │ f6  │ f14 │   │     │     │     │     │               │
//    ├─────┼────┼────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼───────────────┤
//    │ f10 │ f1 │ f2 │ f3  │ f13 │   │     │     │     │     │               │
//    └─────┴────┴────┼─────┼─────┤   ├─────┼─────┼─────┴─────┴───────────────┘
//                    │ f16 │ f17 │   │     │     │
//                    └─────┴─────┘   └─────┴─────┘
[_FUNCTION] = LAYOUT_split_3x5_2(
  KC_F12 , KC_F7 , KC_F8 , KC_F9  , KC_F15 ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , QK_LAYER_LOCK,
  KC_F11 , KC_F4 , KC_F5 , KC_F6  , KC_F14 ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,
  KC_F10 , KC_F1 , KC_F2 , KC_F3  , KC_F13 ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS      ,
                           KC_F16 , KC_F17 ,     KC_TRNS , KC_TRNS
)
};
