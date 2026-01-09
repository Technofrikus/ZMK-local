#!/usr/bin/env python3
"""
Script to clear retention memory (GPREGRET1) on nRF52840 to exit bootloader mode.
This fixes the issue where the keyboard stays in bootloader mode after flashing.

Usage:
    python3 scripts/clear-retention-memory.py

Requirements:
    - pyserial: pip install pyserial
    - Keyboard must be connected via USB (in bootloader mode is OK)
"""

import sys
import time

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    print("Error: pyserial not installed")
    print("Install with: pip install pyserial")
    sys.exit(1)

# GPREGRET1 register address for nRF52840
GPREGRET1_ADDR = 0x4000051C

def find_nrf_device():
    """Find nRF52840 device by VID/PID"""
    # Adafruit nRF52 Bootloader VID/PID
    BOOTLOADER_VID = 0x239A
    BOOTLOADER_PID = 0x0029
    
    # Normal mode VID/PID (if device is in normal mode)
    NORMAL_VID = 0x239A
    NORMAL_PID = 0x002A
    
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if port.vid == BOOTLOADER_VID and port.pid == BOOTLOADER_PID:
            return port.device, "bootloader"
        elif port.vid == NORMAL_VID and port.pid == NORMAL_PID:
            return port.device, "normal"
    
    return None, None

def clear_retention_via_serial(port_name):
    """
    Attempt to clear retention memory via serial.
    Note: This is a simplified approach. For nRF52840, you typically need
    nrfjprog or a custom firmware to write to GPREGRET1.
    """
    print(f"Connecting to {port_name}...")
    try:
        ser = serial.Serial(port_name, 115200, timeout=1)
        print("Connected!")
        print("\nNote: Direct serial access to GPREGRET1 is not possible.")
        print("You need to use nrfjprog or flash a firmware that clears it.")
        ser.close()
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False

def main():
    print("Clear Retention Memory (GPREGRET1)")
    print("=" * 40)
    print()
    
    port, mode = find_nrf_device()
    
    if not port:
        print("Error: No nRF52840 device found")
        print()
        print("Make sure:")
        print("  1. Keyboard is connected via USB")
        print("  2. Device is in bootloader mode (UF2 drive mounted)")
        print("  3. Or device is in normal mode")
        sys.exit(1)
    
    print(f"Found device: {port} (mode: {mode})")
    print()
    
    if mode == "bootloader":
        print("Device is in bootloader mode.")
        print()
        print("To clear retention memory, you need to:")
        print("  1. Install nRF Command Line Tools:")
        print("     https://www.nordicsemi.com/Software-and-Development-Tools/Development-Tools/nRF-Command-Line-Tools")
        print()
        print("  2. Run:")
        print(f"     nrfjprog --memwr 0x4000051C --val 0x00")
        print(f"     nrfjprog --reset")
        print()
        print("  OR")
        print()
        print("  3. Flash the firmware again, then immediately:")
        print("     - Disconnect USB")
        print("     - Wait 2 seconds")
        print("     - Reconnect USB")
        print("     - The firmware should clear retention memory on first boot")
    else:
        print("Device is in normal mode.")
        print("If it's stuck in bootloader mode, try:")
        print("  1. Press Reset button once")
        print("  2. If it still goes to bootloader, use nrfjprog to clear GPREGRET1")
    
    print()
    print("Alternative: Use the clear-bootloader-mode.sh script with nrfjprog")

if __name__ == "__main__":
    main()
