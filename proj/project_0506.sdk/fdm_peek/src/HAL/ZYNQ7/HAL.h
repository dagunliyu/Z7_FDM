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
 * HAL for Xilinx Zynq-7000 (Cortex-A9)
 */

#define CPU_32_BIT

#include "fastio.h"

#include <stdint.h>

// ------------------------
// Defines
// ------------------------

#define _MSERIAL(X) MSerial##X
#define MSERIAL(X) _MSERIAL(X)
#define MSerial0 MSerial

#ifndef SERIAL_PORT
  #define SERIAL_PORT 0
#endif

#define NUM_SERIAL 1

// ------------------------
// Types
// ------------------------

typedef int8_t pin_t;

#define HAL_SERVO_LIB Servo

// ------------------------
// Public Variables
// ------------------------

/** result of last ADC conversion */
extern uint16_t HAL_adc_result;

// ------------------------
// Public functions
// ------------------------

// Memory related
#define __bss_end __bss_end__

/** clear reset reason */
void HAL_clear_reset_source();

/** reset reason */
uint8_t HAL_get_reset_source();

inline void HAL_reboot() {}  // reboot the board or restart the bootloader

void HAL_init();

// ADC
#define HAL_ANALOG_SELECT(pin) pinMode(pin, INPUT)

inline void HAL_adc_init() {}
void HAL_adc_start_conversion(const uint8_t ch);

#define HAL_ADC_VREF         3.3
#define HAL_ADC_RESOLUTION   10
#define HAL_START_ADC(pin)   HAL_adc_start_conversion(pin)
#define HAL_READ_ADC()       HAL_adc_result
#define HAL_ADC_READY()      true

void HAL_pwm_init();
void HAL_timer_start(const uint8_t timer_num, const uint32_t frequency);

#define HAL_PWM_WRITE(P,V)   analogWrite(P, V)

#endif // HAL_ZYNQ7_HAL_H
