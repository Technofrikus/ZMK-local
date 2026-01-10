#!/bin/bash
# Clear the display debug log file without deleting it
# Works even if the file is open in an editor or by another process

LOG_FILE="${1:-zmk-display-debug.log}"

# Resolve absolute path if relative
if [[ "$LOG_FILE" != /* ]]; then
    LOG_FILE="$(pwd)/$LOG_FILE"
fi

if [ ! -f "$LOG_FILE" ]; then
    echo "✗ Log file not found: $LOG_FILE"
    exit 1
fi

# Method 1: Try truncate (works on macOS)
if command -v truncate &> /dev/null; then
    truncate -s 0 "$LOG_FILE" 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "✓ Log file cleared (using truncate): $LOG_FILE"
        exit 0
    fi
fi

# Method 2: Try redirect (works if file is not locked)
> "$LOG_FILE" 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✓ Log file cleared: $LOG_FILE"
    exit 0
fi

# Method 3: Try with sudo if permissions are the issue
sudo truncate -s 0 "$LOG_FILE" 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✓ Log file cleared (with sudo): $LOG_FILE"
    exit 0
fi

# Method 4: Try to use /dev/null trick (works even if file is open)
cat /dev/null > "$LOG_FILE" 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✓ Log file cleared (using /dev/null): $LOG_FILE"
    exit 0
fi

echo "✗ Failed to clear log file. File may be locked by another process."
echo "  Try: 1) Close the file in Cursor/any editor"
echo "       2) Stop any process using the file (e.g., tio)"
echo "       3) Or use: sudo truncate -s 0 $LOG_FILE"
exit 1
