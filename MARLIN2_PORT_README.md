# Marlin 2 Port to Xilinx Zynq-7000 Platform

## Overview

This repository contains a port of [Marlin 2.x firmware](https://github.com/MarlinFirmware/Marlin) to the Xilinx Zynq-7000 platform. The Zynq-7000 is a System-on-Chip (SoC) that combines a dual-core ARM Cortex-A9 processor with FPGA fabric, making it suitable for advanced 3D printer control applications.

## What Has Been Done

### 1. Marlin 2 Core Integration (✅ Complete)
- **Source Code**: All Marlin 2.x source files from the official repository have been copied to `proj/project_0506.sdk/fdm_peek/src/`
- **Directory Structure**: Maintained Marlin 2's organized structure:
  - `core/` - Core data types and utilities
  - `gcode/` - G-code parser and commands
  - `module/` - Motion control, temperature management, etc.
  - `lcd/` - Display and UI support
  - `feature/` - Optional features
  - `sd/` - SD card support
  - `HAL/` - Hardware Abstraction Layer
  - `pins/` - Board-specific pin definitions
  - `inc/` - Configuration headers

### 2. ZYNQ7 Hardware Abstraction Layer (✅ Complete)
Created a new HAL at `proj/project_0506.sdk/fdm_peek/src/HAL/ZYNQ7/`:
- **HAL.h/HAL.cpp**: Core HAL functions including initialization, ADC, and memory management
- **fastio.h**: Fast GPIO operations (READ, WRITE, SET_OUTPUT, etc.)
- **timers.h/timers.cpp**: Timer management for stepper control and temperature regulation
- **spi_pins.h**: SPI pin definitions for SD card and peripherals
- **inc/**: Platform-specific conditionals and sanity checks
  - `Conditionals_LCD.h`
  - `Conditionals_post.h`
  - `Conditionals_adv.h`
  - `SanityCheck.h`

### 3. Board Configuration (✅ Complete)
- **Board Definition**: Added `BOARD_ZYNQ7` (7200) to `core/boards.h`
- **Platform Support**: Added ARM Cortex-A9 detection (`__ARM_ARCH_7A__`) to `HAL/platforms.h`
- **Pin Definitions**: Created `pins/zynq7/pins_ZYNQ7.h` with default pin assignments
- **Configuration**: Updated `config/Configuration.h` to use `BOARD_ZYNQ7` as default motherboard

### 4. Application Entry Point (✅ Complete)
- Updated `main.cc` to call Marlin's `setup()` and `loop()` functions
- Provides the standard embedded firmware execution model

## What Needs to Be Done

### 1. Hardware Driver Implementation (❌ TODO)
The current HAL provides placeholder functions. These need to be connected to actual Xilinx drivers:

#### GPIO (fastio.h)
```cpp
// Current: Placeholder functions
// TODO: Implement using Xilinx GPIO driver (xgpio.h)
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
```

#### Timers (timers.cpp)
```cpp
// Current: Software simulation
// TODO: Implement using Xilinx TTC (Triple Timer Counter)
// - Stepper motor timing (high precision required)
// - Temperature sensor polling
// - PWM generation for heaters
```

#### ADC (HAL.cpp)
```cpp
// Current: Returns dummy values
// TODO: Implement using XADC (Xilinx Analog-to-Digital Converter)
// - Temperature sensor readings
// - Analog endstop support
```

#### UART (Missing)
```cpp
// TODO: Create MarlinSerial.h/cpp using Xilinx UART drivers
// - Serial communication for G-code commands
// - Debug output
```

### 2. Build System Integration (❌ TODO)

#### Xilinx SDK Project Configuration
The code needs to be properly integrated into the Xilinx SDK build system:

1. **Update .cproject**: Add all new source files to the build
2. **Include Paths**: Ensure all Marlin 2 directories are in the include path
3. **Compiler Flags**: 
   - Add `-D__ARM_ARCH_7A__` to define the platform
   - Configure optimization flags
   - Enable C++11 or later features

4. **Linker Script**: Verify memory layout in `lscript.ld` accommodates larger firmware

#### Example Build Steps
```bash
# In Xilinx SDK:
1. Right-click on fdm_peek project → Properties
2. C/C++ Build → Settings
3. Add include paths:
   - src/
   - src/HAL/ZYNQ7
   - src/core
   - src/module
   - etc.
4. Add preprocessor defines:
   - __ARM_ARCH_7A__
   - F_CPU=666666666UL
```

### 3. Hardware-Specific Configuration (❌ TODO)

#### Pin Mapping (pins/zynq7/pins_ZYNQ7.h)
The current pin definitions are placeholders. Update based on your hardware:
```cpp
// Example: Update to match your actual hardware connections
#define X_STEP_PIN         /* Your GPIO pin */
#define X_DIR_PIN          /* Your GPIO pin */
#define HEATER_0_PIN       /* Your PWM-capable pin */
// etc.
```

#### Clock Configuration
Update `HAL/ZYNQ7/inc/Conditionals_post.h`:
```cpp
#ifndef F_CPU
  #define F_CPU 666666666UL  // Adjust to your actual CPU frequency
#endif
```

### 4. Testing and Validation (❌ TODO)

1. **Compilation Test**: Ensure the project builds without errors
2. **Basic Initialization**: Verify HAL_init() executes correctly
3. **Timer Functionality**: Test stepper motor timing accuracy
4. **GPIO Operations**: Verify pin control works correctly
5. **Serial Communication**: Test G-code command reception
6. **Motion Control**: Validate stepper motor movements
7. **Temperature Control**: Test heater and sensor functionality

### 5. Optional Enhancements (⚠️ Future)

- **FPGA Integration**: Leverage FPGA fabric for:
  - Hardware-accelerated stepper pulse generation
  - Parallel sensor reading
  - Advanced motion planning
  
- **Performance Optimization**: 
  - Use dual-core capabilities for parallel processing
  - Implement real-time operating system (RTOS) support

- **Additional Features**:
  - Network connectivity (Ethernet)
  - Advanced LCD support
  - Camera integration

## Directory Structure

```
proj/project_0506.sdk/fdm_peek/src/
├── HAL/                    # Hardware Abstraction Layer
│   ├── ZYNQ7/             # Zynq-7 specific HAL (NEW)
│   ├── AVR/               # Other platforms (reference)
│   ├── STM32/
│   └── ...
├── pins/
│   ├── zynq7/             # Zynq-7 pin definitions (NEW)
│   └── ...
├── core/                   # Core types and utilities
├── gcode/                  # G-code parser
├── module/                 # Motion, temperature, etc.
├── lcd/                    # Display support
├── feature/                # Optional features
├── sd/                     # SD card support
├── inc/                    # Configuration headers
├── config/                 # User configuration files
│   ├── Configuration.h
│   └── Configuration_adv.h
├── MarlinCore.cpp         # Main firmware core
├── MarlinCore.h
└── main.cc                # Application entry point (UPDATED)
```

## Building and Deployment

### Prerequisites
- Xilinx Vivado (for FPGA design)
- Xilinx SDK (for software development)
- ARM cross-compiler toolchain
- Zynq-7000 development board

### Build Steps
1. Open the project in Xilinx SDK
2. Configure build settings (see "Build System Integration" above)
3. Build the project
4. Program the FPGA with the hardware design
5. Deploy and debug the firmware

## Configuration

The firmware can be configured by editing:
- `config/Configuration.h` - Basic printer configuration
- `config/Configuration_adv.h` - Advanced features
- `pins/zynq7/pins_ZYNQ7.h` - Hardware pin assignments

## Known Limitations

1. **HAL Functions**: Currently placeholders that need hardware driver implementation
2. **Build System**: Not yet integrated with Xilinx SDK project files
3. **Testing**: No validation has been performed on actual hardware
4. **Documentation**: Hardware setup guide needs to be created

## Contributing

When implementing the TODO items, please:
1. Test thoroughly on actual hardware
2. Document any hardware-specific quirks
3. Update this README with your findings
4. Consider submitting improvements back to the community

## References

- [Marlin Firmware Official Repository](https://github.com/MarlinFirmware/Marlin)
- [Xilinx Zynq-7000 Documentation](https://www.xilinx.com/products/silicon-devices/soc/zynq-7000.html)
- [Marlin HAL Development Guide](https://marlinfw.org/docs/development/hardware.html)

## License

This port maintains compatibility with Marlin's GPL 3.0 license. See LICENSE file for details.

---

## Quick Start Checklist

- [x] Clone Marlin 2 source code
- [x] Create ZYNQ7 HAL skeleton
- [x] Configure build system (board definitions)
- [x] Update main entry point
- [ ] Implement GPIO drivers
- [ ] Implement timer drivers
- [ ] Implement ADC drivers
- [ ] Implement UART drivers
- [ ] Configure build system (SDK project)
- [ ] Test compilation
- [ ] Test on hardware
- [ ] Validate basic motion control
- [ ] Validate temperature control
- [ ] Full system integration test

---

*Last updated: 2026-01-12*
*Port based on Marlin 2.1.x branch*
