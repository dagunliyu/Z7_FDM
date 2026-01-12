#!/bin/bash

# Marlin 2 Port Verification Script for Zynq-7
# This script verifies the basic structure of the Marlin 2 port

echo "=========================================="
echo "Marlin 2 Port to Zynq-7 Verification"
echo "=========================================="
echo ""

# Check project directory
PROJECT_DIR="proj/project_0506.sdk/fdm_peek/src"
if [ ! -d "$PROJECT_DIR" ]; then
    echo "❌ ERROR: Project directory not found: $PROJECT_DIR"
    exit 1
fi
echo "✓ Project directory found: $PROJECT_DIR"

# Check ZYNQ7 HAL directory
ZYNQ7_HAL="$PROJECT_DIR/HAL/ZYNQ7"
if [ ! -d "$ZYNQ7_HAL" ]; then
    echo "❌ ERROR: ZYNQ7 HAL directory not found"
    exit 1
fi
echo "✓ ZYNQ7 HAL directory found"

# Check critical HAL files
echo ""
echo "Checking ZYNQ7 HAL files:"
HAL_FILES=("HAL.h" "HAL.cpp" "fastio.h" "timers.h" "timers.cpp" "spi_pins.h")
for file in "${HAL_FILES[@]}"; do
    if [ -f "$ZYNQ7_HAL/$file" ]; then
        echo "  ✓ $file"
    else
        echo "  ❌ Missing: $file"
    fi
done

# Check ZYNQ7 pins directory
ZYNQ7_PINS="$PROJECT_DIR/pins/zynq7"
if [ ! -d "$ZYNQ7_PINS" ]; then
    echo "❌ ERROR: ZYNQ7 pins directory not found"
    exit 1
fi
echo "✓ ZYNQ7 pins directory found"

if [ -f "$ZYNQ7_PINS/pins_ZYNQ7.h" ]; then
    echo "  ✓ pins_ZYNQ7.h"
else
    echo "  ❌ Missing: pins_ZYNQ7.h"
fi

# Check configuration files
echo ""
echo "Checking configuration files:"
CONFIG_DIR="$PROJECT_DIR/config"
if [ -f "$CONFIG_DIR/Configuration.h" ]; then
    echo "  ✓ Configuration.h"
    # Check if BOARD_ZYNQ7 is set
    if grep -q "BOARD_ZYNQ7" "$CONFIG_DIR/Configuration.h"; then
        echo "    ✓ BOARD_ZYNQ7 configured"
    else
        echo "    ⚠ BOARD_ZYNQ7 not set in Configuration.h"
    fi
else
    echo "  ❌ Missing: Configuration.h"
fi

if [ -f "$CONFIG_DIR/Configuration_adv.h" ]; then
    echo "  ✓ Configuration_adv.h"
else
    echo "  ❌ Missing: Configuration_adv.h"
fi

# Check main entry point
echo ""
echo "Checking main entry point:"
if [ -f "$PROJECT_DIR/main.cc" ]; then
    echo "  ✓ main.cc found"
    if grep -q "MarlinCore.h" "$PROJECT_DIR/main.cc"; then
        echo "    ✓ MarlinCore.h included"
    fi
    if grep -q "setup()" "$PROJECT_DIR/main.cc"; then
        echo "    ✓ setup() called"
    fi
    if grep -q "loop()" "$PROJECT_DIR/main.cc"; then
        echo "    ✓ loop() called"
    fi
else
    echo "  ❌ Missing: main.cc"
fi

# Check MarlinCore
echo ""
echo "Checking Marlin core files:"
if [ -f "$PROJECT_DIR/MarlinCore.cpp" ]; then
    echo "  ✓ MarlinCore.cpp"
else
    echo "  ❌ Missing: MarlinCore.cpp"
fi

if [ -f "$PROJECT_DIR/MarlinCore.h" ]; then
    echo "  ✓ MarlinCore.h"
else
    echo "  ❌ Missing: MarlinCore.h"
fi

# Count source files
echo ""
echo "Source file statistics:"
CPP_COUNT=$(find "$PROJECT_DIR" -name "*.cpp" -o -name "*.cc" 2>/dev/null | wc -l)
H_COUNT=$(find "$PROJECT_DIR" -name "*.h" 2>/dev/null | wc -l)
echo "  Source files (.cpp/.cc): $CPP_COUNT"
echo "  Header files (.h): $H_COUNT"
echo "  Total: $((CPP_COUNT + H_COUNT))"

# Check critical Marlin 2 directories
echo ""
echo "Checking Marlin 2 directory structure:"
MARLIN_DIRS=("core" "gcode" "module" "lcd" "feature" "sd" "HAL" "pins" "inc")
for dir in "${MARLIN_DIRS[@]}"; do
    if [ -d "$PROJECT_DIR/$dir" ]; then
        echo "  ✓ $dir/"
    else
        echo "  ❌ Missing: $dir/"
    fi
done

echo ""
echo "=========================================="
echo "Verification Complete!"
echo "=========================================="
echo ""
echo "Next steps:"
echo "1. Review MARLIN2_PORT_README.md for implementation details"
echo "2. Implement hardware drivers in HAL/ZYNQ7/"
echo "3. Configure Xilinx SDK build settings"
echo "4. Test compilation"
echo "5. Deploy to hardware and validate"
echo ""
