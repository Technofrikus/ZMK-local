#!/bin/bash
# ZMK Build Script for Tipper TF - Docker Version
# Builds the Tipper TF keyboard firmware using Docker

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
# shellcheck source=zmk-ci-env.sh
source "$REPO_ROOT/scripts/zmk-ci-env.sh"

echo -e "${BLUE}ZMK Tipper TF Build (Docker)${NC}"
echo "===================================="
echo ""

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo -e "${RED}✗ Docker is not installed${NC}"
    echo "Please install Docker Desktop from: https://www.docker.com/products/docker-desktop"
    exit 1
fi

echo -e "${GREEN}✓ Docker is installed${NC}"

# Wait for Docker daemon
echo "Waiting for Docker daemon to start..."
MAX_WAIT=60
WAITED=0
while [ $WAITED -lt $MAX_WAIT ]; do
    if docker ps >/dev/null 2>&1; then
        echo -e "${GREEN}✓ Docker daemon is running${NC}"
        break
    fi
    echo -n "."
    sleep 2
    WAITED=$((WAITED + 2))
done

if ! docker ps >/dev/null 2>&1; then
    echo ""
    echo -e "${RED}✗ Docker daemon is not running${NC}"
    echo ""
    echo "Please start Docker Desktop manually:"
    echo "  1. Open Docker Desktop application"
    echo "  2. Wait until it's fully started (whale icon in menu bar)"
    echo "  3. Run this script again"
    exit 1
fi

echo ""
echo -e "${BLUE}Building Tipper TF firmware...${NC}"
echo ""

# Run build in container (same image + west update + pristine build as upstream ZMK CI)
docker run --rm \
    -v "$REPO_ROOT:/workspaces/ZMK-tf2" \
    -w /workspaces/ZMK-tf2 \
    "$ZMK_BUILD_IMAGE" \
    bash -c "
        set -e
        cd /workspaces/ZMK-tf2
        if [ ! -d .west ]; then
            west init -l config
        fi
        west update --fetch-opt=--filter=tree:0
        west zephyr-export
        west build -s zmk/app -p -b tipper_tf -- \
            -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf \
            -DBOARD_ROOT=/workspaces/ZMK-tf2/config
        
        echo ''
        echo '✓ Build successful!'
        echo 'Firmware location: build/zephyr'
        echo ''
        echo 'Firmware files:'
        ls -lh build/zephyr/*.hex build/zephyr/*.uf2 2>/dev/null || echo 'No .hex or .uf2 files found'
    "

if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}✓✓✓ Tipper TF firmware build completed successfully! ✓✓✓${NC}"
    echo ""
    echo "Firmware files are in: $REPO_ROOT/build/zephyr"
    echo ""
    echo "To flash the firmware:"
    echo "  - UF2: Copy .uf2 file to the keyboard's bootloader"
    echo "  - nrfjprog: nrfjprog -f nrf52 --program build/zephyr/zephyr.hex --chiperase --reset"
    exit 0
else
    echo ""
    echo -e "${RED}✗ Build failed${NC}"
    exit 1
fi
