#!/bin/bash
# ZMK Local Host Setup Script
# This script sets up the local development environment for ZMK

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}ZMK Local Host Setup${NC}"
echo "===================="
echo ""

# Detect OS
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
else
    OS="Unknown"
fi

echo "Detected OS: $OS"
echo ""

# Check if west is installed
if ! command -v west &> /dev/null; then
    echo -e "${YELLOW}⚠ west is not installed${NC}"
    echo ""
    
    if [[ "$OS" == "macOS" ]]; then
        echo "On macOS, we recommend using pipx to install west:"
        echo ""
        
        # Check if pipx is installed
        if ! command -v pipx &> /dev/null; then
            echo -e "${YELLOW}⚠ pipx is not installed${NC}"
            echo "Installing pipx with Homebrew..."
            if command -v brew &> /dev/null; then
                brew install pipx
            else
                echo -e "${RED}✗ Homebrew is not installed${NC}"
                echo "Please install Homebrew first: https://brew.sh"
                echo "Or install pipx manually: https://pipx.pypa.io/stable/installation/"
                exit 1
            fi
        fi
        
        echo "Installing west with pipx..."
        pipx install west
        echo ""
        echo -e "${GREEN}✓ west installed${NC}"
        echo ""
        echo -e "${YELLOW}⚠ Make sure ~/.local/bin is in your PATH${NC}"
        echo "Add to ~/.zshrc or ~/.bashrc:"
        echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
        echo ""
        echo "Then run: source ~/.zshrc  (or source ~/.bashrc)"
        echo ""
    else
        echo "Installing west with pip3..."
        pip3 install --user --upgrade west
        echo ""
        echo -e "${GREEN}✓ west installed${NC}"
        echo ""
        echo -e "${YELLOW}⚠ Make sure ~/.local/bin is in your PATH${NC}"
        echo "Add to ~/.bashrc or ~/.profile:"
        echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
        echo ""
    fi
    
    # Check if west is now available
    if ! command -v west &> /dev/null; then
        echo -e "${RED}✗ west is still not available${NC}"
        echo "Please add ~/.local/bin to your PATH and run this script again."
        exit 1
    fi
else
    echo -e "${GREEN}✓ west is already installed${NC}"
    west --version
fi
echo ""

# Check if Zephyr SDK is installed
if [ -z "$ZEPHYR_SDK_INSTALL_DIR" ]; then
    echo -e "${YELLOW}⚠ ZEPHYR_SDK_INSTALL_DIR is not set${NC}"
    echo ""
    echo "Please install Zephyr SDK from:"
    echo "  https://github.com/zephyrproject-rtos/sdk-ng/releases"
    echo ""
    echo "Then set the environment variable:"
    echo "  export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr-sdk"
    echo ""
    echo "To make it permanent, add to ~/.zshrc or ~/.bashrc:"
    echo "  echo 'export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr-sdk' >> ~/.zshrc"
    echo ""
    echo -e "${YELLOW}⚠ Builds will fail without Zephyr SDK${NC}"
    echo ""
else
    echo -e "${GREEN}✓ ZEPHYR_SDK_INSTALL_DIR is set${NC}"
    echo "  $ZEPHYR_SDK_INSTALL_DIR"
    echo ""
fi

# Get the repository root directory
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CONFIG_DIR="$REPO_ROOT/config"

echo "Repository root: $REPO_ROOT"
echo "Config directory: $CONFIG_DIR"

# Initialize west workspace
if [ ! -d "$REPO_ROOT/.west" ]; then
    echo "Initializing west workspace..."
    cd "$REPO_ROOT"
    west init -l "$CONFIG_DIR"
else
    echo "West workspace already initialized"
fi

# Update west modules (same fetch options as upstream ZMK CI)
echo "Updating west modules (this may take a while)..."
cd "$REPO_ROOT"
west update --fetch-opt=--filter=tree:0

# Export Zephyr CMake package
echo "Exporting Zephyr CMake package..."
west zephyr-export

# Install Python dependencies
if [ -f "$REPO_ROOT/zephyr/scripts/requirements.txt" ]; then
    echo "Installing Python dependencies..."
    if [[ "$OS" == "macOS" ]] && command -v pipx &> /dev/null; then
        # On macOS, try to use pipx if available, otherwise use pip3
        pip3 install --user -r "$REPO_ROOT/zephyr/scripts/requirements.txt" || true
    else
        pip3 install --user -r "$REPO_ROOT/zephyr/scripts/requirements.txt"
    fi
    echo -e "${GREEN}✓ Python dependencies installed${NC}"
    echo ""
fi

echo ""
echo -e "${GREEN}✓✓✓ Setup complete! ✓✓✓${NC}"
echo ""
echo "You can now build ZMK firmware using:"
echo "  ./scripts/build.sh <keyboard> <board>"
echo ""
echo "Or test the environment with:"
echo "  ./scripts/test-build.sh"
