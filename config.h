/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#define EE_HANDS

// Force the MCU to wait for a successful USB handshake before sending data,
// preventing desync during KVM switching.
#define WAIT_FOR_USB

// IGNORE_MOD_TAP_INTERRUPT was removed from QMK; its behavior is now the default.
// No replacement define is needed.

// RGB lighting effects are enabled in the keyboard's keyboard.json.
// Only step sizes are customized here.
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
