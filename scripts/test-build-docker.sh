#!/bin/bash
# ZMK Test Build Script - Docker Version
# Waits for Docker and then runs the test build in a container

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

echo -e "${BLUE}ZMK Docker Test Build${NC}"
echo "========================"
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
echo -e "${BLUE}Running test build in Docker container...${NC}"
echo ""

# Test configuration
# In Zephyr 4.1 / HWMv2, boards are referenced by their simple name
TEST_BOARD="nice_nano"
TEST_SHIELD="corne_left"

echo "Test configuration:"
echo "  Board: $TEST_BOARD"
echo "  Shield: $TEST_SHIELD"
echo ""

# Run test build in container
# Using zmk-build-arm:stable which is the current stable build image
docker run --rm \
    -v "$REPO_ROOT:/workspaces/ZMK-tf2" \
    -w /workspaces/ZMK-tf2 \
    docker.io/zmkfirmware/zmk-build-arm:stable \
    bash -c "
        set -e
        
        # Check if west is available
        if ! command -v west &> /dev/null; then
            echo 'ERROR: west is not available in container'
            exit 1
        fi
        
        echo 'Initializing west workspace...'
        if [ ! -d .west ]; then
            west init -l config
            echo '✓ West workspace initialized'
        else
            echo '✓ West workspace already exists'
        fi
        
        echo ''
        echo 'Updating west modules (this may take a while)...'
        west update
        
        echo ''
        echo 'Exporting Zephyr CMake package...'
        west zephyr-export
        
        echo ''
        echo 'Building test keyboard...'
        echo '  Board: $TEST_BOARD'
        echo '  Shield: $TEST_SHIELD'
        echo ''
        west build -d build-test -s zmk/app -b $TEST_BOARD -- -DSHIELD=$TEST_SHIELD
        
        echo ''
        echo '✓ Build successful!'
        echo 'Firmware location: build-test/zephyr'
    "

if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}✓✓✓ ZMK build environment test PASSED! ✓✓✓${NC}"
    echo ""
    echo "The build environment is working correctly."
    echo "You can now build your Tipper TF keyboard."
    exit 0
else
    echo ""
    echo -e "${RED}✗ Build failed${NC}"
    exit 1
fi
