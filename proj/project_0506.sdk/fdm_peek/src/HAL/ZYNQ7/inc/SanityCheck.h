/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * HAL Sanity Check for Xilinx Zynq-7000
 */
#pragma once

// Sanity checks for ZYNQ7 platform
#if ENABLED(EMERGENCY_PARSER)
  #error "EMERGENCY_PARSER is not yet supported on ZYNQ7."
#endif

#if ENABLED(FAST_PWM_FAN) || ENABLED(FAST_PWM_FAN_TINY)
  #error "FAST_PWM_FAN is not yet supported on ZYNQ7."
#endif

#if ENABLED(USE_WATCHDOG)
  #error "USE_WATCHDOG is not yet supported on ZYNQ7."
#endif
