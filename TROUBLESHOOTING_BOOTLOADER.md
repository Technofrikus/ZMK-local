# Troubleshooting: Keyboard Stuck in Bootloader Mode

## Problem
Keyboard immediately enters bootloader mode (UF2 drive appears) when reset is pressed. Double-pressing reset does nothing. Keyboard does not show up as USB HID or BLE device.

## Root Cause
The `GPREGRET1` register (address `0x4000051C`) has the bootloader magic value `0x57` set. The Adafruit nRF52 bootloader checks this register **BEFORE** launching the firmware. If `GPREGRET1 == 0x57`, it enters bootloader mode immediately, so the firmware never runs.

The double-tap bootloader feature cannot fix this because it's part of the firmware code, which never executes when stuck in bootloader mode.

## Solution

### Option 1: Clear GPREGRET1 via nrfjprog (Requires SWD/JTAG)

**Prerequisites:**
- nRF Command Line Tools installed: https://www.nordicsemi.com/Software-and-Development-Tools/Development-Tools/nRF-Command-Line-Tools
- SWD/JTAG connection to the keyboard (not just USB)
  - Can use an nRF52840-DK as a debugger
  - Or use nRF Connect Desktop App with a compatible debugger

**Steps:**
```bash
# Clear GPREGRET1 register
nrfjprog --memwr 0x4000051C --val 0x00

# Reset the device
nrfjprog --reset
```

**Using the provided script:**
```bash
./scripts/clear-bootloader-mode.sh
```

### Option 2: Use nRF Connect Desktop App
1. Open nRF Connect Desktop
2. Use Programmer tool
3. Connect via SWD/JTAG
4. Read memory at address `0x4000051C`
5. Write `0x00` to that address
6. Reset the device

### Option 3: Temporary Workaround (If SWD Not Available)
If you don't have SWD access, you're temporarily stuck. You'll need to:
1. Obtain SWD/JTAG access (nRF52840-DK, J-Link, or similar)
2. Clear GPREGRET1 as described above
3. Flash the firmware

## Prevention

After clearing GPREGRET1 and flashing firmware:
- The double-tap bootloader feature should work correctly
- On normal boot, firmware will set GPREGRET1 to 0x57, wait 500ms, then clear it
- If reset is pressed twice within 500ms, GPREGRET1 stays at 0x57 and bootloader is entered
- On next boot after bootloader mode, firmware will clear GPREGRET1 on boot

## Why This Happens

The double-tap bootloader works as follows:
1. Firmware boots → Sets GPREGRET1 = 0x57 (bootloader magic value)
2. Waits 500ms
3. If no reset detected → Clears GPREGRET1 = 0x00
4. If reset detected within 500ms → GPREGRET1 stays 0x57
5. Bootloader sees GPREGRET1 = 0x57 → Enters bootloader mode

If something interrupts this flow (firmware crash, power loss, etc.) while GPREGRET1 = 0x57, the keyboard gets stuck in bootloader mode.

## Verification

After clearing GPREGRET1 and resetting:
- Keyboard should boot normally
- Should appear as USB HID device
- Should appear in Bluetooth scans as "Tipper TF"
- Double-press reset should enter bootloader mode
- Single press reset should boot normally
