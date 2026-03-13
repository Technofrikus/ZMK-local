#!/bin/bash
# ZMK Docker Build Script
# Usage: ./scripts/build.sh <keyboard> [board] [shield]

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Get the repository root directory
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
KEYBOARD_DIR="$REPO_ROOT/keyboards"

# Check arguments
if [ $# -lt 1 ]; then
    echo -e "${RED}Usage: $0 <keyboard> [board] [shield]${NC}"
    echo ""
    echo "Examples:"
    echo "  $0 planckton          (Uses nice_nano and shield=planckton as default)"
    echo "  $0 tipper_tf          (Uses tipper_tf board)"
    exit 1
fi

KEYBOARD=$1
BOARD=$2
SHIELD=$3

# Default Board/Shield Logic
if [ -z "$BOARD" ]; then
    case $KEYBOARD in
        planckton)
            BOARD="nice_nano"
            ;;
        tipper_tf)
            BOARD="tipper_tf"
            ;;
        *)
            echo -e "${YELLOW}No board specified, defaulting to nice_nano${NC}"
            BOARD="nice_nano"
            ;;
    esac
fi

if [ -z "$SHIELD" ]; then
    case $KEYBOARD in
        planckton)
            SHIELD="planckton"
            ;;
        tipper_tf)
            SHIELD="" # Tipper TF is a board, not a shield
            ;;
        *)
            SHIELD=$KEYBOARD
            ;;
    esac
fi

# Check if keyboard directory exists
if [ ! -d "$KEYBOARD_DIR/$KEYBOARD" ]; then
    echo -e "${RED}Error: Keyboard directory not found: $KEYBOARD_DIR/$KEYBOARD${NC}"
    exit 1
fi

echo -e "${GREEN}ZMK Docker Build${NC}"
echo "================"
echo "Keyboard: $KEYBOARD"
echo "Board:    $BOARD"
echo "Shield:   ${SHIELD:-None}"
echo ""

# Construct the internal build command
SHIELD_ARG=""
if [ -n "$SHIELD" ]; then
    SHIELD_ARG="-DSHIELD=$SHIELD"
fi

# The command to run inside the Docker container
DOCKER_CMD="west zephyr-export && west build -p always -s zmk/app -b $BOARD -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/$KEYBOARD -DBOARD_ROOT=/workspaces/ZMK-tf2/config $SHIELD_ARG"

echo -e "${YELLOW}Starting Docker container...${NC}"

docker run --rm \
  -v "$REPO_ROOT:/workspaces/ZMK-tf2" \
  -w /workspaces/ZMK-tf2 \
  docker.io/zmkfirmware/zmk-build-arm:stable \
  bash -c "$DOCKER_CMD"

# Check if build was successful
if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}Build successful!${NC}"
    echo "Firmware location: $REPO_ROOT/build/zephyr"
    
    # Optional: Copy .uf2 to a more accessible place
    if [ -f "$REPO_ROOT/build/zephyr/zmk.uf2" ]; then
        mkdir -p "$REPO_ROOT/output"
        cp "$REPO_ROOT/build/zephyr/zmk.uf2" "$REPO_ROOT/output/${KEYBOARD}_${BOARD}.uf2"
        echo -e "${GREEN}Copied firmware to: output/${KEYBOARD}_${BOARD}.uf2${NC}"
    fi
else
    echo ""
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
