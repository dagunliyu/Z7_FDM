/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Generic Xilinx Zynq-7000 pin assignments
 */

#if NOT_TARGET(__ARM_ARCH_7A__)
  #error "Oops! Select 'ZYNQ7' in your IDE."
#endif

#define BOARD_INFO_NAME "ZYNQ7"

//
// Limit Switches
//
#define X_MIN_PIN          2
#define X_MAX_PIN          3
#define Y_MIN_PIN          4
#define Y_MAX_PIN          5
#define Z_MIN_PIN          6
#define Z_MAX_PIN          7

//
// Steppers
//
#define X_STEP_PIN         8
#define X_DIR_PIN          9
#define X_ENABLE_PIN      10

#define Y_STEP_PIN        11
#define Y_DIR_PIN         12
#define Y_ENABLE_PIN      13

#define Z_STEP_PIN        14
#define Z_DIR_PIN         15
#define Z_ENABLE_PIN      16

#define E0_STEP_PIN       17
#define E0_DIR_PIN        18
#define E0_ENABLE_PIN     19

//
// Temperature Sensors
//
#define TEMP_0_PIN         0  // Analog pin
#define TEMP_BED_PIN       1  // Analog pin

//
// Heaters / Fans
//
#define HEATER_0_PIN      20
#define HEATER_BED_PIN    21
#define FAN_PIN           22

//
// Misc. Functions
//
#define LED_PIN           23

//
// LCD / Controller
//
#if HAS_WIRED_LCD
  #define LCD_PINS_RS     24
  #define LCD_PINS_ENABLE 25
  #define LCD_PINS_D4     26
  #define LCD_PINS_D5     27
  #define LCD_PINS_D6     28
  #define LCD_PINS_D7     29

  #if ENABLED(REPRAP_DISCOUNT_SMART_CONTROLLER)
    #define BEEPER_PIN    30
    #define BTN_EN1       31
    #define BTN_EN2       32
    #define BTN_ENC       33
    #define SD_DETECT_PIN 34
    #define KILL_PIN      35
  #endif
#endif

//
// SD Card
//
#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION LCD
#endif

#if SD_CONNECTION_IS(LCD)
  #define SD_SS_PIN       36
  #define SD_SCK_PIN      37
  #define SD_MISO_PIN     38
  #define SD_MOSI_PIN     39
#endif
