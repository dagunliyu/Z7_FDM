/**
 * Marlin 3D Printer Firmware
 * Main entry point for Xilinx Zynq-7000 platform
 */

#include "inc/MarlinConfig.h"
#include "MarlinCore.h"

// External function declarations from MarlinCore
extern void setup();
extern void loop();

int main() {
  // Initialize Marlin firmware
  setup();
  
  // Main firmware loop
  for (;;) {
    loop();
  }
  
  return 0;
}
