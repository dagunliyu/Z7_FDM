/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * HAL Conditionals for Xilinx Zynq-7000
 */
#pragma once

// Serial ports
#define NUM_SERIAL 1

// CPU frequency  
#ifndef F_CPU
  #define F_CPU 666666666UL  // Zynq-7 Cortex-A9 @ 666MHz
#endif
