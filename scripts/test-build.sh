#!/bin/bash
# ZMK Test Build Script
# Tests the ZMK build environment with a standard keyboard

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get the repository root directory
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CONFIG_DIR="$REPO_ROOT/config"

echo -e "${BLUE}ZMK Build Environment Test${NC}"
echo "=============================="
echo ""

# Check if we're in a Docker container
if [ -f /.dockerenv ] || [ -n "$DOCKER_CONTAINER" ]; then
    echo -e "${GREEN}✓ Running in Docker container${NC}"
    IN_CONTAINER=true
else
    echo -e "${YELLOW}⚠ Running on host system${NC}"
    IN_CONTAINER=false
fi

# Check for west
if ! command -v west &> /dev/null; then
    echo -e "${RED}✗ west is not installed${NC}"
    echo ""
    if [ "$IN_CONTAINER" = false ]; then
        echo "Please either:"
        echo "  1. Use VS Code Dev Container (recommended)"
        echo "  2. Install west with pipx: pipx install west"
        echo "     (On macOS, use pipx instead of pip3 install --user)"
        echo "  3. Run: ./scripts/setup-local.sh"
    else
        echo "west should be available in the container. Please check the container setup."
    fi
    exit 1
else
    echo -e "${GREEN}✓ west is installed${NC}"
    west --version
fi

# Check for Zephyr SDK (only on host, not in container)
if [ "$IN_CONTAINER" = false ] && [ -z "$ZEPHYR_SDK_INSTALL_DIR" ]; then
    echo -e "${YELLOW}⚠ ZEPHYR_SDK_INSTALL_DIR is not set${NC}"
    echo "  This is required for local host builds."
    echo "  Install from: https://github.com/zephyrproject-rtos/sdk-ng/releases"
    echo "  Then set: export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr-sdk"
    echo ""
    echo "  Continuing anyway, but build may fail..."
    echo ""
fi

# Check if west workspace is initialized
if [ ! -d "$REPO_ROOT/.west" ]; then
    echo -e "${YELLOW}⚠ West workspace not initialized${NC}"
    echo "Initializing west workspace..."
    cd "$REPO_ROOT"
    west init -l "$CONFIG_DIR"
    echo -e "${GREEN}✓ West workspace initialized${NC}"
else
    echo -e "${GREEN}✓ West workspace already initialized${NC}"
fi

# Same as upstream CI: west update before every build
echo "Updating west modules (this may take a while)..."
cd "$REPO_ROOT"
west update --fetch-opt=--filter=tree:0

# Export Zephyr CMake package
echo "Exporting Zephyr CMake package..."
cd "$REPO_ROOT"
west zephyr-export
echo -e "${GREEN}✓ Zephyr exported${NC}"

echo ""
echo -e "${BLUE}Testing build with standard keyboard...${NC}"
echo ""

# Test build options
# Option 1: nice_nano with corne_left (very common)
# In Zephyr 4.1 / HWMv2, boards are referenced by their simple name
TEST_BOARD="nice_nano"
TEST_SHIELD="corne_left"

echo "Test configuration:"
echo "  Board: $TEST_BOARD"
echo "  Shield: $TEST_SHIELD"
echo ""

# Check if board exists (HWMv2 structure)
# In HWMv2, boards are in zmk/app/boards/<vendor>/<board> or zmk/app/boards/<board>
BOARD_DIR=""
if [ -d "$REPO_ROOT/zmk/app/boards/nicekeyboards/nice_nano" ]; then
    BOARD_DIR="$REPO_ROOT/zmk/app/boards/nicekeyboards/nice_nano"
    echo -e "${GREEN}✓ Board found at: $BOARD_DIR${NC}"
elif [ -d "$REPO_ROOT/zmk/app/boards/arm/nice_nano" ]; then
    BOARD_DIR="$REPO_ROOT/zmk/app/boards/arm/nice_nano"
    echo -e "${GREEN}✓ Board found at: $BOARD_DIR${NC}"
else
    echo -e "${YELLOW}⚠ Board directory not found, but will try build anyway (west will find it)${NC}"
fi

# Check if shield exists
if [ ! -d "$REPO_ROOT/zmk/app/boards/shields/$TEST_SHIELD" ]; then
    echo -e "${RED}✗ Shield $TEST_SHIELD not found in ZMK${NC}"
    echo "Available shields:"
    ls -1 "$REPO_ROOT/zmk/app/boards/shields/" 2>/dev/null | head -10 || echo "Cannot list shields"
    exit 1
fi

echo -e "${GREEN}✓ Board and shield found${NC}"
echo ""

# Build command
BUILD_DIR="$REPO_ROOT/build-test"
BUILD_CMD="west build -d $BUILD_DIR -s zmk/app -p -b $TEST_BOARD -- -DSHIELD=$TEST_SHIELD"

echo -e "${BLUE}Building...${NC}"
echo "Command: $BUILD_CMD"
echo ""

# Run build
if $BUILD_CMD; then
    echo ""
    echo -e "${GREEN}✓ Build successful!${NC}"
    echo ""
    echo "Firmware location: $BUILD_DIR/zephyr"
    echo ""
    echo -e "${GREEN}ZMK build environment is working correctly!${NC}"
    echo ""
    echo "You can now build your Tipper TF keyboard with:"
    echo "  west build -s zmk/app -p -b tipper_tf -- -DZMK_CONFIG=$REPO_ROOT/keyboards/tipper_tf"
    exit 0
else
    echo ""
    echo -e "${RED}✗ Build failed!${NC}"
    echo ""
    echo "Please check the error messages above."
    exit 1
fi
