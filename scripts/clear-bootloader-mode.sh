#!/bin/bash
# Script to clear bootloader mode from GPREGRET1 register
# This fixes the issue where the keyboard stays in bootloader mode

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Clear Bootloader Mode${NC}"
echo "======================"
echo ""

# Check if nrfjprog is installed
if ! command -v nrfjprog &> /dev/null; then
    echo -e "${RED}✗ nrfjprog is not installed${NC}"
    echo ""
    echo "Please install nRF Command Line Tools from:"
    echo "  https://www.nordicsemi.com/Software-and-Development-Tools/Development-Tools/nRF-Command-Line-Tools"
    echo ""
    echo "Or use Option 2: Flash a special firmware that clears the retention memory"
    exit 1
fi

echo -e "${GREEN}✓ nrfjprog found${NC}"
echo ""

# GPREGRET1 register address for nRF52840
GPREGRET1_ADDR=0x4000051C

echo "Clearing GPREGRET1 register (bootloader mode flag)..."
echo "Address: $GPREGRET1_ADDR"
echo ""
echo -e "${YELLOW}Note: nrfjprog requires SWD/JTAG connection (not USB).${NC}"
echo "If you only have USB access, you'll need to:"
echo "  1. Connect via SWD/JTAG (e.g., using an nRF52840-DK as a debugger)"
echo "  2. OR temporarily disable double-tap bootloader, flash firmware, then re-enable"
echo ""

# Try to read current value (this works even in bootloader mode if SWD is connected)
echo "Reading current GPREGRET1 value..."
if nrfjprog --memrd $GPREGRET1_ADDR --n 1 2>/dev/null; then
    echo -e "${GREEN}✓ Successfully read GPREGRET1${NC}"
else
    echo -e "${YELLOW}⚠ Could not read GPREGRET1 via nrfjprog${NC}"
    echo ""
    echo "This usually means:"
    echo "  - Device is only connected via USB (nrfjprog needs SWD/JTAG)"
    echo "  - nRF Connect Programmer is not running"
    echo "  - SWD/JTAG pins are not connected"
    echo ""
    echo "Trying to write anyway (may fail)..."
fi

# Write 0 to clear bootloader mode
echo ""
echo "Clearing bootloader mode (writing 0x00)..."
if nrfjprog --memwr $GPREGRET1_ADDR --val 0x00 2>/dev/null; then
    echo -e "${GREEN}✓ Successfully cleared GPREGRET1${NC}"
else
    echo -e "${RED}✗ Failed to write GPREGRET1${NC}"
    echo ""
    echo -e "${YELLOW}Alternative solutions:${NC}"
    echo ""
    echo "1. Connect via SWD/JTAG and try again"
    echo "2. Temporarily disable double-tap bootloader:"
    echo "   - Set CONFIG_ZMK_DBL_TAP_BOOTLOADER=n in tipper_tf.conf"
    echo "   - Rebuild and flash firmware"
    echo "   - Firmware will boot normally and clear GPREGRET1"
    echo "   - Then re-enable double-tap bootloader"
    echo ""
    echo "3. Use nRF Connect Desktop App to clear GPREGRET1 via SWD"
    exit 1
fi

# Verify
echo ""
echo "Verifying (should be 0x00):"
nrfjprog --memrd $GPREGRET1_ADDR --n 1

echo ""
echo -e "${GREEN}✓ Bootloader mode cleared!${NC}"
echo ""
echo "Now reset the keyboard (press Reset button once) and it should boot normally."
echo ""
