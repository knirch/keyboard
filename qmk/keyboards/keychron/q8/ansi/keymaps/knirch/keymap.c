/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "print.h"

enum layers{
    BASE,
    _BASE_DIP_WIN,
    _FN1,
    _FN2
};

/* Keychron keyboards have a switch to toggle between Windows or Mac keys.
 * A switch change calls default_layer_set, making MAC keys using layer 1
 * and WIN keys on layer 2. This is however not reflected elsewhere, so
 * layer_state_set_user will see the same layer regardless of dipswitch.
 *
 * Track the dipswitch postion via MAC_MODE = true/false.
 */
static bool MAC_MODE = false;

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable = true;
  debug_matrix = true;
  debug_keyboard = true;
  //debug_mouse=true;
}

#define KCH_ENT RALT_T(KC_ENT)
#define KCH_ESC LCTL_T(KC_ESC)
#define KCH_MO1 MO(_FN1)
#define KCH_MO2 MO(_FN2)

/* Keychron Q8 ANSI
   ┌───┬───┬───┬───┬───┬───┬───┐    ┌───┬───┬───┬───┬───┬───┬───────┐  ┌───┐
   │esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │    │ 7 │ 8 │ 9 │ 0 │ - │ = │  <--  │  │Mut│
  ┌┴───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘  ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┴┐ └┬──┴┐
  │ tab │ q │ w │ e │ r │ t │     │ y │ u │ i │ o │ p │ [ │ ] │  \|  │  │Mut│
 ┌┴─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬─┘  └┬──┴┐
 │ ctrl  │ a │ s │ d │ f │ g │      │ h │ j │ k │ l │ ; │ ' │ enter│     │Mut│
┌┴───────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  ┌──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┬─┘     └───┘
│  shift  │ z │ x │ c │ v │ b │  │del│ n │ m │ < │ > │ / │ shift │  ┌───┐
├────┬────┴┬──┼───┴┬──┴───┴┬──┴─┐├───┼───┴───┴─┬─┴──┬┴───┴───────┘  │ ↑ │
│ctrl│ alt │  │code│ space │code││app│ space   │ctrl│           ┌───┼───┼───┐
└────┴─────┘  └────┴───────┴────┘└───┴─────────┴────┘           │ ← │ ↓ │ → │
                                                                └───┴───┴───┘
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_69(
        KC_GRV , KC_1    , KC_2   , KC_3   ,  KC_4  , KC_5   , KC_6   ,               KC_7   , KC_8   , KC_9   ,    KC_0, KC_MINS,  KC_EQL , KC_BSPC,  KC_INS,
        KC_TAB , KC_Q    , KC_W   , KC_E   ,  KC_R  , KC_T   ,               KC_Y   , KC_U   , KC_I   , KC_O   ,    KC_P, KC_LBRC,  KC_RBRC, KC_BSLS,  KC_PGUP,
        KCH_ESC, KC_A    , KC_S   , KC_D   ,  KC_F  , KC_G   ,               KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,  KCH_ENT,           KC_PGDN,
        KC_LSFT, KC_Z    , KC_X   , KC_C   ,  KC_V  , KC_B   ,      KC_DEL , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,             KC_UP,
        KC_GRV , KC_LALT , KCH_MO1,         KC_LWIN , KCH_MO2,      KC_BSPC,          KC_SPC , KC_RCTL,                             KC_LEFT, KC_DOWN, KC_RGHT),

    /* I use the MAC/WIN switch to enable my gaming layer */
    [_BASE_DIP_WIN] = LAYOUT_ansi_69(
        KC_ESC , KC_1    , KC_2   , KC_3   ,  KC_4  , KC_5   , KC_6   ,               KC_7   , KC_8   , KC_9   ,    KC_0, KC_MINS,  KC_EQL , KC_BSPC,  KC_INS,
        KC_TAB , KC_Q    , KC_W   , KC_E   ,  KC_R  , KC_T   ,               KC_Y   , KC_U   , KC_I   , KC_O   ,    KC_P, KC_LBRC,  KC_RBRC, KC_BSLS,  KC_PGUP,
        KC_LCTL, KC_A    , KC_S   , KC_D   ,  KC_F  , KC_G   ,               KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,  KCH_ENT,           KC_PGDN,
        KC_LSFT, KC_Z    , KC_X   , KC_C   ,  KC_V  , KC_B   ,      KC_DEL , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,             KC_UP,
        KC_GRV , KC_LALT , KC_LWIN,           KC_SPC, KCH_MO2,      KC_BSPC,          KC_SPC , KC_RCTL,                             KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN1] = LAYOUT_ansi_69(
        DB_TOGG, KC_BRID , _______, _______, _______, RGB_VAD, RGB_VAI,               KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,  _______,          QK_BOOT,
        RGB_TOG, RGB_MOD , RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI,               _______, _______, _______, _______, _______, _______,  _______,  _______,           EE_CLR,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,               KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,  _______,                    DB_TOGG,
        _______, _______ , _______, _______, _______, _______,      _______, NK_TOGG, _______, _______, _______, _______, _______,            _______,
        _______, _______ , _______,          _______, _______,      _______,          _______, _______,                              _______, _______,  _______),

    [_FN2] = LAYOUT_ansi_69(
        DB_TOGG, KC_F1   , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,               KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,   KC_F12,  _______,          QK_BOOT,
        RGB_TOG, RGB_MOD , RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI,               _______, _______, _______, _______, _______, _______,  _______,  _______,          KC_HOME,
        KC_CAPS, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,               KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,  _______,          KC_END,
        _______, _______ , _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        QK_BOOT, _______ , _______,          _______, _______,      _______,          _______, _______,          _______, _______, _______)
};


// GUI + esc = ~
const key_override_t f1  = ko_make_basic(MOD_MASK_GUI, KC_1   , KC_F1 );
const key_override_t f2  = ko_make_basic(MOD_MASK_GUI, KC_2   , KC_F2 );
const key_override_t f3  = ko_make_basic(MOD_MASK_GUI, KC_3   , KC_F3 );
const key_override_t f4  = ko_make_basic(MOD_MASK_GUI, KC_4   , KC_F4 );
const key_override_t f5  = ko_make_basic(MOD_MASK_GUI, KC_5   , KC_F5 );
const key_override_t f6  = ko_make_basic(MOD_MASK_GUI, KC_6   , KC_F6 );
const key_override_t f7  = ko_make_basic(MOD_MASK_GUI, KC_7   , KC_F7 );
const key_override_t f8  = ko_make_basic(MOD_MASK_GUI, KC_8   , KC_F8 );
const key_override_t f9  = ko_make_basic(MOD_MASK_GUI, KC_9   , KC_F9 );
const key_override_t f10 = ko_make_basic(MOD_MASK_GUI, KC_0   , KC_F10);
const key_override_t f11 = ko_make_basic(MOD_MASK_GUI, KC_MINS, KC_F11);
const key_override_t f12 = ko_make_basic(MOD_MASK_GUI, KC_EQL , KC_F12);

/*
const key_override_t win_h = ko_make_with_layers_and_negmods(MOD_MASK_GUI, KC_H, KC_LEFT, BASE, MOD_MASK_SHIFT);
const key_override_t win_j = ko_make_with_layers_and_negmods(MOD_MASK_GUI, KC_J, KC_DOWN, BASE, MOD_MASK_SHIFT);
const key_override_t win_k = ko_make_with_layers_and_negmods(MOD_MASK_GUI, KC_K, KC_UP,   BASE, MOD_MASK_SHIFT);
const key_override_t win_l = ko_make_with_layers_and_negmods(MOD_MASK_GUI, KC_L, KC_RGHT, BASE, MOD_MASK_SHIFT);
*/

const key_override_t **key_overrides = (const key_override_t *[]) {
    &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9, &f9, &f10, &f11, &f12, NULL
};

void kch_update_rgb(void) {
        if (MAC_MODE) // Normal
            rgb_matrix_reload_from_eeprom();
        else { // Gaming
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BAND_PINWHEEL_VAL);
            rgb_matrix_sethsv_noeeprom(0, 255, 200);
        }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    dprintf("layer: %d\n", get_highest_layer(state));

    switch (get_highest_layer(state)) {
        case BASE:
            kch_update_rgb();
            break;
        case _FN1:
            break;
        case _FN2:
            break;
        default:
            break;
        }
    return state;
}


bool dip_switch_update_user(uint8_t index, bool active) {
    dprintf("dip switch: index: %d, active: %d\n", index, active);

    if (index == 0) { // MAC_MODE switch
        MAC_MODE = !active;
        kch_update_rgb();
    }

    return true;

}

// vim: noai:ts=4:sw=4:et
