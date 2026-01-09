#!/bin/bash
# ZMK Build Script
# Usage: ./scripts/build.sh <keyboard> <board> [shield]

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Get the repository root directory
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CONFIG_DIR="$REPO_ROOT/config"
KEYBOARD_DIR="$REPO_ROOT/keyboards"

# Check arguments
if [ $# -lt 2 ]; then
    echo -e "${RED}Usage: $0 <keyboard> <board> [shield]${NC}"
    echo ""
    echo "Examples:"
    echo "  $0 tipper_tf tipper_tf"
    echo "  $0 corne nice_nano -- -DSHIELD=corne_left"
    exit 1
fi

KEYBOARD=$1
BOARD=$2
SHIFT=2
SHIELD_ARG=""

# Check for shield argument
if [ $# -gt 2 ]; then
    SHIELD_ARG="-DSHIELD=$3"
    SHIFT=3
fi

# Additional CMake arguments
CMAKE_ARGS="${@:$((SHIFT+1))}"

# Check if keyboard directory exists
if [ ! -d "$KEYBOARD_DIR/$KEYBOARD" ]; then
    echo -e "${RED}Error: Keyboard directory not found: $KEYBOARD_DIR/$KEYBOARD${NC}"
    exit 1
fi

# Set ZMK_CONFIG path
ZMK_CONFIG="$KEYBOARD_DIR/$KEYBOARD"

echo -e "${GREEN}ZMK Build${NC}"
echo "=========="
echo "Keyboard: $KEYBOARD"
echo "Board: $BOARD"
if [ -n "$SHIELD_ARG" ]; then
    echo "Shield: $3"
fi
echo "Config: $ZMK_CONFIG"
echo ""

# Check if west is installed
if ! command -v west &> /dev/null; then
    echo -e "${RED}✗ west is not installed${NC}"
    echo ""
    echo "Please install west first:"
    echo "  ./scripts/setup-local.sh"
    echo "  or"
    echo "  pipx install west  (on macOS)"
    exit 1
fi

# Check if west workspace is initialized
if [ ! -d "$REPO_ROOT/.west" ]; then
    echo -e "${YELLOW}⚠ West workspace not initialized. Running setup...${NC}"
    "$REPO_ROOT/scripts/setup-local.sh"
fi

# Check if ZMK is cloned
if [ ! -d "$REPO_ROOT/zmk" ]; then
    echo -e "${YELLOW}⚠ ZMK not cloned yet. Updating west modules...${NC}"
    cd "$REPO_ROOT"
    west update
    west zephyr-export
fi

# Ensure we're in the repo root
cd "$REPO_ROOT"

# Build command
# Add config directory to BOARD_ROOT so Zephyr can find our custom board
BUILD_CMD="west build -s zmk/app -b $BOARD -- -DZMK_CONFIG=$ZMK_CONFIG -DBOARD_ROOT=$REPO_ROOT/config $SHIELD_ARG $CMAKE_ARGS"

echo -e "${GREEN}Building...${NC}"
echo "Command: $BUILD_CMD"
echo ""

# Run build
$BUILD_CMD

# Check if build was successful
if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}Build successful!${NC}"
    echo "Firmware location: $REPO_ROOT/build/zephyr"
    echo ""
    echo "To flash the firmware, use:"
    echo "  west flash"
    echo "  or"
    echo "  nrfjprog -f nrf52 --program build/zephyr/zephyr.hex --chiperase --reset"
else
    echo ""
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
